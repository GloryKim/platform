import { useHelper } from '@react-three/drei';
import { useEffect, useRef, useMemo } from 'react'; // 240711_1510_glory : 조명을 세팅하고 조명정보만 변동할때에만 로그를 보내고 싶어서 시작한 추가 작업인 useMemo 추가 진행
import * as THREE from 'three';
import { Vector3 } from 'three';

interface LightProps {
  isSelected: boolean;
  isVisible: boolean;
  brightness: number;
  target?: Vector3; //옵션으로 만들기
  position?: Vector3; //옵션으로 만들기
  color: string;
  onUpdate: (lightData: any) => void; //240711_1140_glory : light 정보가 변화될때 마다 log를 송신하기 위한 기능 구현
  type: 'ambient' | 'directional' | 'spot'; // 240711_1515_glory : 조명 타입 추가 
}

export const Lights: React.FC<LightProps> = ({
  isSelected,
  isVisible,
  brightness,
  target,
  position,
  color,
  onUpdate, //240711_1324_glory : onUpdate기능 신규 추가
  type, // 240711_1515_glory : 조명 타입 추가
}) => {
  const lightRef: any = useRef(null);
  const targetObject = useRef<THREE.Object3D>(new THREE.Object3D());
  const prevPropsRef = useRef<LightProps>({ 
    isSelected, 
    isVisible, 
    brightness, 
    target, 
    position, 
    color, 
    type, 
    onUpdate 
  }); // 240711_1510_glory : 조명을 세팅하고 조명정보만 변동할때에만 로그를 보내고 싶어서 시작한 추가 작업 + 240711_1525_glory : 방금 이 구문에서 type을 추가했다. 이거 빼먹으면 아래에서 선언이 안되어있어 작동이 안되는 오류가 있다.

  // 선택된 경우에 DirectionalLightHelper를 사용하여 조명 시각화
  useHelper(isSelected && type === 'directional' && lightRef, THREE.DirectionalLightHelper, 3, color);

  // 240711_1510_glory : 조명을 세팅하고 조명정보만 변동할때에만 로그를 보내고 싶어서 시작한 추가 작업
  const lightData = useMemo(() => ({
    type, // 240711_1536_glory : 조명 타입 추가
    isVisible,
    brightness: type === 'ambient' ? Math.min(brightness) : brightness,
    ...(type !== 'ambient' && { // 240711_1536_glory : ambient 조명일때는 예외처리
      target: target?.toArray(), // 240711_1536_glory : ambient 조명일때는 예외처리
      position: position?.toArray(), // 240711_1536_glory : ambient 조명일때는 예외처리
    }), // 240711_1536_glory : ambient 조명일때는 예외처리, 왜? 전역 조명이니깐 위치를 왜 보내냐 ㅋㅋㄹㅃㅃ
    color,
  }), [type, isVisible, brightness, target, position, color]);

  // 조명 정보가 변경될 때마다 업데이트
  useEffect(() => {
    if (type !== 'ambient' && target) {
      targetObject.current.position.copy(target);
    }
  
    const prevProps = prevPropsRef.current;
    if (
      prevProps.type !== type ||
      prevProps.isVisible !== isVisible ||
      prevProps.brightness !== brightness ||
      (type !== 'ambient' && (
        (target && !prevProps.target?.equals(target)) || 
        (position && !prevProps.position?.equals(position))
      )) ||
      prevProps.color !== color ||
      prevProps.isSelected !== isSelected // isSelected 비교 추가
    ) {
      console.log('Light data updated:', lightData);
      onUpdate(lightData);
      prevPropsRef.current = { 
        isVisible, 
        brightness, 
        target, 
        position, 
        color, 
        type,
        isSelected,  // isSelected 추가
        onUpdate     // onUpdate 추가
      };
    }
  }, [type, isVisible, brightness, target, position, color, onUpdate, lightData, isSelected]); // isSelected 의존성 추가
  //240711_1512_glory : 여기까지 코드작성을 완료하였고, 이 작업까지 수행하면, 조명을 세팅하고 조명정보만 변동할때에만 로그가 보내짐

  //240711_1535_glory : type에 따라 보내는 로그 정보 다르게 하기
  switch (type) {
    case 'ambient':
      return (
        <ambientLight
          color={color}
          intensity={brightness}
          visible={isVisible}
        />
      );
    case 'directional':
      return (
        <directionalLight
          ref={lightRef}
          color={color}
          intensity={brightness}
          visible={isVisible}
          target={target ? targetObject.current : undefined}
          position={position || new THREE.Vector3()}
          castShadow
        />
      );
    case 'spot':
      return (
        <spotLight
          ref={lightRef}
          color={color}
          intensity={brightness}
          visible={isVisible}
          target={target ? targetObject.current : undefined}
          position={position || new THREE.Vector3()}
          castShadow
          angle={Math.PI / 4}
          penumbra={0.5}
        />
      );
    default:
      return null;
  }
};