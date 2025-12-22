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

      // 이벤트 리스너 등록
      window.addEventListener("resize", onWindowResize, false);
      window.addEventListener("keydown", onKeyDown, false);
      window.addEventListener("keyup", onKeyUp, false);
      renderer.domElement.addEventListener("mousedown", onMouseDown, false);
      renderer.domElement.addEventListener("mousemove", onMouseMove, false);
      renderer.domElement.addEventListener("mouseup", onMouseUp, false);
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
