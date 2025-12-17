/*
실행하기 앞서 포트 허가에 대한 내용을 작성해줘야함
node@fasts-MacBook-Pro ~ % sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setglobalstate off

Firewall is disabled. (State = 0)
node@fasts-MacBook-Pro ~ % sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setglobalstate on 
Password:
Firewall is enabled. (State = 1) 
node@fasts-MacBook-Pro ~ % 
*/

"use client";

import { useEffect, useRef } from "react";
import * as THREE from "three";
import { FBXLoader } from "three-stdlib";

export default function Page() {
  const containerRef = useRef(null);

  useEffect(() => {
    let renderer, scene, camera, model;
    let isMouseDown = false;
    let prevMouseX = 0;
    const keyState = {};
    const cylinders = {}; // object_id별 원기둥을 저장

    // object_id에 따른 색상 매핑
    const colors = {
      "0": 0xff0000, // 빨간색
      "1": 0x00ff00, // 초록색
      "2": 0x0000ff, // 파란색
      "3": 0xffff00, // 노란색
      "4": 0xff00ff, // 분홍색
      "5": 0x00ffff, // 시안색 (예시로 추가)
      // 필요하다면 계속 추가 가능
    };

    // 카메라 / 회전 설정
    const cameraSpeed = 0.6;
    const arrowRotateStep = 0.03;
    const dragRotateSpeed = 0.01;

    const init = () => {
      // 렌더러와 씬, 카메라 초기화
      renderer = new THREE.WebGLRenderer({ antialias: true });
      renderer.setSize(window.innerWidth, window.innerHeight);
      containerRef.current.appendChild(renderer.domElement);

      scene = new THREE.Scene();
      scene.background = new THREE.Color(0xeeeeee);

      camera = new THREE.PerspectiveCamera(
        75,
        window.innerWidth / window.innerHeight,
        0.1,
        1000
      );
      camera.position.set(0, 2, 5);

      // 조명
      const light = new THREE.DirectionalLight(0xffffff, 1);
      light.position.set(0, 10, 10).normalize();
      scene.add(light);

      // FBX 모델 로드
      const loader = new FBXLoader();
      loader.load("/models/sample.fbx", (object) => {
        model = object;
        model.scale.set(0.01, 0.01, 0.01);
        scene.add(model);
        animate();
      });

      // WebSocket 연결
      connectWebSocket();

      // 이벤트 등록
      window.addEventListener("resize", onWindowResize, false);
      window.addEventListener("keydown", onKeyDown, false);
      window.addEventListener("keyup", onKeyUp, false);
      renderer.domElement.addEventListener("mousedown", onMouseDown, false);
      renderer.domElement.addEventListener("mousemove", onMouseMove, false);
      renderer.domElement.addEventListener("mouseup", onMouseUp, false);
    };

    // WebSocket 연결 함수
    const connectWebSocket = () => {
      // 여기서는 예시로 Go 브릿지 서버 혹은 직접 Tornado 서버로 연결
      // 'ws://localhost:9999/ws' 또는 'ws://192.168.0.34:1234' 등
      const ws = new WebSocket("ws://localhost:9999/ws");

      ws.onmessage = (event) => {
        try {
          // 수신 데이터 형태:
          // {"object_id": 0, "x": -3.38, "y": -3.30, "z": 1.0}
          const data = JSON.parse(event.data);
          
          // 변경된 부분: object_id를 받아옴
          const { object_id, x, y, z } = data;
          
          // object_id를 문자열화하여 Key로 사용
          addOrMoveCylinder(String(object_id), x, y, z);
        } catch (err) {
          console.error("수신 데이터 오류:", err);
        }
      };

      ws.onerror = (err) => {
        console.error("WebSocket 오류:", err);
      };

      ws.onclose = () => {
        console.warn("WebSocket 연결 종료. 재연결 시도...");
        setTimeout(connectWebSocket, 3000);
      };
    };

    // 원기둥 생성/이동 함수
    const addOrMoveCylinder = (id, x, y, z) => {
      const targetPos = new THREE.Vector3(x, y, z);

      // 아직 cylinders에 없는 ID라면 새 원기둥 생성
      if (!cylinders[id]) {
        const geometry = new THREE.CylinderGeometry(0.1, 0.1, 1, 50);
        const material = new THREE.MeshStandardMaterial({
          color: colors[id] || 0xffffff,
          transparent: true,
          opacity: 0.7,
        });
        const cylinder = new THREE.Mesh(geometry, material);
        cylinder.position.copy(targetPos);
        scene.add(cylinder);

        // 관리용 객체에 등록
        cylinders[id] = cylinder;
      } else {
        // 기존 원기둥 이동 (부드러운 이동)
        const cylinder = cylinders[id];
        const startPosition = cylinder.position.clone();
        const duration = 30; // 이동 프레임 수
        let frame = 0;

        const move = () => {
          frame++;
          const t = frame / duration;
          cylinder.position.lerpVectors(startPosition, targetPos, t);

          if (frame < duration) {
            requestAnimationFrame(move);
          } else {
            cylinder.position.copy(targetPos);
          }
        };

        move();
      }
    };

    // 창 크기 조절
    const onWindowResize = () => {
      camera.aspect = window.innerWidth / window.innerHeight;
      camera.updateProjectionMatrix();
      renderer.setSize(window.innerWidth, window.innerHeight);
    };

    // 마우스 드래그
    const onMouseDown = (e) => {
      isMouseDown = true;
      prevMouseX = e.clientX;
    };

    const onMouseMove = (e) => {
      if (!isMouseDown || !model) return;
      const deltaX = e.clientX - prevMouseX;
      model.rotateY(deltaX * dragRotateSpeed);
      prevMouseX = e.clientX;
    };

    const onMouseUp = () => {
      isMouseDown = false;
    };

    // 키보드 입력
    const onKeyDown = (e) => {
      keyState[e.key] = true;
    };

    const onKeyUp = (e) => {
      keyState[e.key] = false;
    };

    // 애니메이션 루프
    const animate = () => {
      requestAnimationFrame(animate);

      // 카메라 이동 (WASD)
      if (keyState["w"]) {
        const forward = new THREE.Vector3();
        camera.getWorldDirection(forward);
        forward.y = 0;
        forward.normalize();
        camera.position.addScaledVector(forward, cameraSpeed);
      }
      if (keyState["s"]) {
        const forward = new THREE.Vector3();
        camera.getWorldDirection(forward);
        forward.y = 0;
        forward.normalize();
        camera.position.addScaledVector(forward, -cameraSpeed);
      }
      if (keyState["a"]) {
        const right = new THREE.Vector3();
        const forward = new THREE.Vector3();
        camera.getWorldDirection(forward);
        forward.y = 0;
        forward.normalize();
        right.crossVectors(forward, camera.up);
        camera.position.addScaledVector(right, -cameraSpeed);
      }
      if (keyState["d"]) {
        const right = new THREE.Vector3();
        const forward = new THREE.Vector3();
        camera.getWorldDirection(forward);
        forward.y = 0;
        forward.normalize();
        right.crossVectors(forward, camera.up);
        camera.position.addScaledVector(right, cameraSpeed);
      }

      // 카메라 위아래 이동 (ArrowUp/ArrowDown)
      if (keyState["ArrowUp"]) {
        camera.position.y += cameraSpeed;
      }
      if (keyState["ArrowDown"]) {
        camera.position.y -= cameraSpeed;
      }

      // 카메라 시점 기준 좌우 회전 (ArrowLeft/ArrowRight)
      if (keyState["ArrowLeft"]) {
        camera.rotation.y += arrowRotateStep;
      }
      if (keyState["ArrowRight"]) {
        camera.rotation.y -= arrowRotateStep;
      }

      renderer.render(scene, camera);
    };

    // 초기화
    init();

    // 언마운트 시 이벤트 해제
    return () => {
      window.removeEventListener("resize", onWindowResize);
      window.removeEventListener("keydown", onKeyDown);
      window.removeEventListener("keyup", onKeyUp);
      if (renderer) {
        renderer.domElement.removeEventListener("mousedown", onMouseDown);
        renderer.domElement.removeEventListener("mousemove", onMouseMove);
        renderer.domElement.removeEventListener("mouseup", onMouseUp);
      }
    };
  }, []);

  return (
    <div
      ref={containerRef}
      style={{
        width: "100vw",
        height: "100vh",
        overflow: "hidden",
        margin: 0,
        padding: 0,
      }}
    />
  );
}
