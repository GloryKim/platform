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
    const cylinders = {}; // ID별 원기둥 객체를 저장

    // ID에 따른 색상 매핑
    const colors = {
      A: 0xff0000, // 빨간색
      B: 0x00ff00, // 초록색
      C: 0x0000ff, // 파란색
      D: 0xffff00, // 노란색
      E: 0xff00ff, // 분홍색
    };

    // 회전/이동 속도 설정
    const cameraSpeed = 0.6;
    const arrowRotateStep = 0.03; // 좌우 화살표 모델 회전 속도
    const dragRotateSpeed = 0.01; // 마우스 드래그 모델 회전 속도

    const init = () => {
      // 렌더러/씬/카메라 초기화
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

      // 라이트
      const light = new THREE.DirectionalLight(0xffffff, 1);
      light.position.set(0, 10, 10).normalize();
      scene.add(light);

      // FBX 로더
      const loader = new FBXLoader();
      loader.load("/models/sample.fbx", (object) => {
        model = object;
        // 스케일 조정
        model.scale.set(0.01, 0.01, 0.01);
        scene.add(model);
        animate();
      });

      // WebSocket 연결
      connectWebSocket();

      // 이벤트 리스너 등록
      window.addEventListener("resize", onWindowResize, false);
      window.addEventListener("keydown", onKeyDown, false);
      window.addEventListener("keyup", onKeyUp, false);
      renderer.domElement.addEventListener("mousedown", onMouseDown, false);
      renderer.domElement.addEventListener("mousemove", onMouseMove, false);
      renderer.domElement.addEventListener("mouseup", onMouseUp, false);
    };

    // WebSocket 연결 함수
    const connectWebSocket = () => {
      const ws = new WebSocket("ws://localhost:11111/ws"); // WebSocket 서버 주소

      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data); // 데이터 파싱
          const { id, x, y, z } = data;
          addOrMoveCylinder(id, x, y, z); // ID별 원기둥 추가 또는 이동
        } catch (err) {
          console.error("수신 데이터 오류:", err);
        }
      };

      ws.onerror = (err) => {
        console.error("WebSocket 오류:", err);
      };

      ws.onclose = () => {
        console.warn("WebSocket 연결 종료. 재연결 시도...");
        setTimeout(connectWebSocket, 3000); // 3초 후 재연결
      };
    };

    // 원기둥 추가 또는 이동 함수
    const addOrMoveCylinder = (id, x, y, z) => {
      const targetPosition = new THREE.Vector3(x, y, z);

      if (!cylinders[id]) {
        // 새로운 원기둥 추가
        const geometry = new THREE.CylinderGeometry(0.1, 0.1, 1, 50);
        const material = new THREE.MeshStandardMaterial({
          color: colors[id] || 0xffffff, // ID에 따른 색상
          transparent: true,
          opacity: 0.7, // 살짝 투명
        });
        const cylinder = new THREE.Mesh(geometry, material);
        cylinder.position.copy(targetPosition);
        scene.add(cylinder);
        cylinders[id] = cylinder;
      } else {
        // 기존 원기둥 이동
        const cylinder = cylinders[id];
        const startPosition = cylinder.position.clone();
        const duration = 30; // 이동 프레임 수
        let frame = 0;

        const move = () => {
          frame++;
          const t = frame / duration;
          cylinder.position.lerpVectors(startPosition, targetPosition, t);

          if (frame < duration) {
            requestAnimationFrame(move);
          } else {
            cylinder.position.copy(targetPosition); // 최종 위치 고정
          }
        };

        move();
      }
    };

    // 창 크기 변경 시
    const onWindowResize = () => {
      camera.aspect = window.innerWidth / window.innerHeight;
      camera.updateProjectionMatrix();
      renderer.setSize(window.innerWidth, window.innerHeight);
    };

    // 마우스 드래그 시작
    const onMouseDown = (e) => {
      isMouseDown = true;
      prevMouseX = e.clientX;
    };

    // 마우스 드래그 중: 모델 Y축 회전
    const onMouseMove = (e) => {
      if (!isMouseDown || !model) return;
      const deltaX = e.clientX - prevMouseX;
      model.rotateY(deltaX * dragRotateSpeed);
      prevMouseX = e.clientX;
    };

    // 마우스 드래그 종료
    const onMouseUp = () => {
      isMouseDown = false;
    };

    // 키보드 입력 상태 관리
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
