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

    const cameraSpeed = 0.3;       // 키보드로 카메라 이동 속도
    const cameraRotateSpeed = 0.01; // 마우스 휠로 카메라 회전 속도

    const init = () => {
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

      const light = new THREE.DirectionalLight(0xffffff, 1);
      light.position.set(0, 10, 10).normalize();
      scene.add(light);

      const loader = new FBXLoader();
      loader.load("/models/sample.fbx", (object) => {
        model = object;
        model.scale.set(0.01, 0.01, 0.01);
        scene.add(model);
        animate();
      });

      window.addEventListener("resize", onWindowResize, false);

      renderer.domElement.addEventListener("mousedown", onMouseDown, false);
      renderer.domElement.addEventListener("mousemove", onMouseMove, false);
      renderer.domElement.addEventListener("mouseup", onMouseUp, false);
      window.addEventListener("keydown", onKeyDown, false);

      // 마우스 휠 이벤트 리스너 추가
      renderer.domElement.addEventListener("wheel", onWheel, false);
    };

    const onWindowResize = () => {
      camera.aspect = window.innerWidth / window.innerHeight;
      camera.updateProjectionMatrix();
      renderer.setSize(window.innerWidth, window.innerHeight);
    };

    const onMouseDown = (e) => {
      isMouseDown = true;
      prevMouseX = e.clientX;
    };

    const onMouseMove = (e) => {
      if (!isMouseDown || !model) return;
      const deltaX = e.clientX - prevMouseX;
      model.rotation.y += deltaX * 0.01;
      prevMouseX = e.clientX;
    };

    const onMouseUp = () => {
      isMouseDown = false;
    };

    const onKeyDown = (e) => {
      switch (e.key) {
        case "w":
          camera.position.z -= cameraSpeed;
          break;
        case "s":
          camera.position.z += cameraSpeed;
          break;
        case "a":
          camera.position.x -= cameraSpeed;
          break;
        case "d":
          camera.position.x += cameraSpeed;
          break;
        case "q":
          camera.position.y -= cameraSpeed;
          break;
        case "e":
          camera.position.y += cameraSpeed;
          break;
        default:
          break;
      }
    };

    // 마우스 휠 이벤트 (카메라 위/아래 회전)
    const onWheel = (e) => {
      // deltaY > 0 -> 아래로 스크롤(카메라 아래쪽 회전)
      // deltaY < 0 -> 위로 스크롤(카메라 위쪽 회전)
      camera.rotation.x += e.deltaY * cameraRotateSpeed;
    };

    const animate = () => {
      requestAnimationFrame(animate);
      renderer.render(scene, camera);
    };

    init();

    return () => {
      window.removeEventListener("resize", onWindowResize);
      window.removeEventListener("keydown", onKeyDown);
      if (renderer) {
        renderer.domElement.removeEventListener("mousedown", onMouseDown);
        renderer.domElement.removeEventListener("mousemove", onMouseMove);
        renderer.domElement.removeEventListener("mouseup", onMouseUp);
        renderer.domElement.removeEventListener("wheel", onWheel);
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
