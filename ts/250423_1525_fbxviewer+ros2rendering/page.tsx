/*
- 실행하기 앞서 포트 허가:
  sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setglobalstate off
  Firewall is disabled.
  
  sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setglobalstate on 
  Firewall is enabled.
*/

"use client";

import { useEffect, useRef } from "react";
import * as THREE from "three";
import { FBXLoader } from "three-stdlib";

export default function Page() {
  const containerRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    // 렌더러, 씬, 카메라, 모델, 이벤트 관련 변수 선언
    let renderer: THREE.WebGLRenderer,
      scene: THREE.Scene,
      camera: THREE.PerspectiveCamera,
      model: THREE.Group;
    let isMouseDown = false;
    let prevMouseX = 0;
    const keyState: { [key: string]: boolean } = {};
    const cylinders: { [key: string]: THREE.Mesh } = {};

    // object_id별 색상 매핑
    const colors: { [key: string]: number } = {
      "0": 0xff0000,
      "1": 0x00ff00,
      "2": 0x0000ff,
      "3": 0xffff00,
      "4": 0xff00ff,
      "5": 0x00ffff,
    };

    // 카메라, 회전 및 드래그 속도 설정
    const cameraSpeed = 0.6;
    const arrowRotateStep = 0.03;
    const dragRotateSpeed = 0.01;

    // 초기화 함수
    const init = () => {
      // 렌더러 및 사이즈 설정
      renderer = new THREE.WebGLRenderer({ antialias: true });
      renderer.setSize(window.innerWidth, window.innerHeight);
      containerRef.current!.appendChild(renderer.domElement);

      // 씬 생성 및 배경색 설정
      scene = new THREE.Scene();
      scene.background = new THREE.Color(0xeeeeee);

      // 카메라 생성 및 위치 설정
      camera = new THREE.PerspectiveCamera(
        75,
        window.innerWidth / window.innerHeight,
        0.1,
        1000
      );
      camera.position.set(0, 2, 5);

      // 조명 추가
      const light = new THREE.DirectionalLight(0xffffff, 5);
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

      // 웹소켓 연결
      connectWebSocket();

      // 이벤트 등록
      window.addEventListener("resize", onWindowResize, false);
      window.addEventListener("keydown", onKeyDown, false);
      window.addEventListener("keyup", onKeyUp, false);
      renderer.domElement.addEventListener("mousedown", onMouseDown, false);
      renderer.domElement.addEventListener("mousemove", onMouseMove, false);
      renderer.domElement.addEventListener("mouseup", onMouseUp, false);
    };

    // 웹소켓 연결 함수
    const connectWebSocket = () => {
      const ws = new WebSocket("ws://localhost:8888/ws");

      ws.onmessage = (event) => {
        try {
          // 예시 데이터: {"object_id": 0, "x": -3.38, "y": -3.30, "z": 1.0}
          const data = JSON.parse(event.data);
          const { object_id, x, y, z } = data;
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

    // 원기둥 생성 또는 이동 함수
    const addOrMoveCylinder = (id: string, x: number, y: number, z: number) => {
      const targetPos = new THREE.Vector3(x, y, z);

      // cylinders에 해당 ID가 없으면 생성
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
        cylinders[id] = cylinder;
      } else {
        // 기존 원기둥의 부드러운 이동
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

    // 창 크기 변경 시 카메라 및 렌더러 사이즈 업데이트
    const onWindowResize = () => {
      camera.aspect = window.innerWidth / window.innerHeight;
      camera.updateProjectionMatrix();
      renderer.setSize(window.innerWidth, window.innerHeight);
    };

    // 마우스 이벤트 처리
    const onMouseDown = (e: MouseEvent) => {
      isMouseDown = true;
      prevMouseX = e.clientX;
    };

    const onMouseMove = (e: MouseEvent) => {
      if (!isMouseDown || !model) return;
      const deltaX = e.clientX - prevMouseX;
      model.rotateY(deltaX * dragRotateSpeed);
      prevMouseX = e.clientX;
    };

    const onMouseUp = () => {
      isMouseDown = false;
    };

    // 키보드 이벤트 처리
    const onKeyDown = (e: KeyboardEvent) => {
      keyState[e.key] = true;
    };

    const onKeyUp = (e: KeyboardEvent) => {
      keyState[e.key] = false;
    };

    // 애니메이션 루프
    const animate = () => {
      requestAnimationFrame(animate);

      // WASD 키에 따른 카메라 이동
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

      // 화살표 키에 따른 카메라 수직 이동 및 회전
      if (keyState["ArrowUp"]) {
        camera.position.y += cameraSpeed;
      }
      if (keyState["ArrowDown"]) {
        camera.position.y -= cameraSpeed;
      }
      if (keyState["ArrowLeft"]) {
        camera.rotation.y += arrowRotateStep;
      }
      if (keyState["ArrowRight"]) {
        camera.rotation.y -= arrowRotateStep;
      }

      renderer.render(scene, camera);
    };

    // 초기화 함수 호출
    init();

    // 언마운트 시 이벤트 제거
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

  // 전체 화면 렌더링을 위한 div 반환
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
