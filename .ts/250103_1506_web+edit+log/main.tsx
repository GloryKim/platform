// 필수 라이브러리 및 컴포넌트 가져오기
import { Box, DragControls, Grid } from '@react-three/drei';
import { Canvas } from '@react-three/fiber';
import { Color, Euler, Quaternion } from 'three';
import { Lights } from './Lights';
import { GLBModel } from './GLBModel';
import { OBJModel } from './OBJModel';
import { FBXModel } from './FBXModel';
import { CameraControl, setCamera } from './CameraControl';
import React, { useState, useEffect } from 'react';
import * as THREE from 'three';
import { Vector3, MeshBasicMaterial } from 'three';
import { CameraItem } from '../App';
import { formatEnum, itemEnum, lightEnum } from '../App';
import {
  RecoilAtom,
  SaveFileNameAtom,
  AssetTypesAtom,
  saveFlagAtom,
  StatusAtom,
} from './RecoilAtom';
import { useRecoilState } from 'recoil';
import { useThree } from '@react-three/fiber';
import { OBJExporter } from 'three/examples/jsm/exporters/OBJExporter';
import { GLTFExporter } from 'three/examples/jsm/exporters/GLTFExporter';
import { saveAs } from 'file-saver';
import axios from 'axios';

// MainCanvasProps 인터페이스 정의
interface MainCanvasProps {
  selectedIndex: number;
  setSelectedIndex: React.Dispatch<React.SetStateAction<number>>;
  setSidebarCamera: React.Dispatch<React.SetStateAction<any>>;
}

/*코드 생략*/

// 조명 데이터를 서버로 전송하는 함수
const sendLightDataToServer = async (lightData: any) => {
  console.log('Sending light data:', lightData); // 240711_1334_glory : 로그가 발생
  try {
    const response = await axios.post('http://localhost:5001/api/light', lightData);
    console.log('Light data sent to server:', response.data);
  } catch (error) {
    console.error('Error sending light data to server:', error);
  }
};

//240712_1018_glory : 코드 생략

  // Ambient 조명 설정 함수
  function setLightAmbient(index: number, data: any) {
    return (
      <Lights
        key={index}
        isSelected={selectedIndex === index}
        isVisible={data.visible}
        brightness={data.brightness} //240711_1613_밝기 고정 풀자
        color={data.color}
        onUpdate={(lightData) => sendLightDataToServer(lightData)}
        type="ambient"
      />
    );
  }

  // Directional 조명 설정 함수
  function setLightDirectional(index: number, data: any, isSelected: boolean) {
    return (
      <React.Fragment key={`directional_${index}`}>
        <DragControls
          key={`target_${index}`}
          matrix={data.matrixTarget.clone()}
          onDragStart={() => setPivotHovered(true)}
          onDragEnd={() => setPivotHovered(false)}
          onDrag={(local) => {
            isSelected && onDragUpdateTarget(local);
          }}
        >
          <mesh visible={isSelected}>
            <Box args={[0.25, 0.25, 0.25]} />
          </mesh>
        </DragControls>
        <DragControls
          key={`position_${index}`}
          matrix={data.matrix.clone()}
          onDragStart={() => setPivotHovered(true)}
          onDragEnd={() => setPivotHovered(false)}
          onDrag={(local) => {
            isSelected && onDragUpdate(local);
          }}
        >
          <mesh visible={isSelected}>
            <Box
              args={[0.5, 0.5, 0.5]}
              material={new MeshBasicMaterial({ color: 'yellow' })}
            />
          </mesh>
        </DragControls>
          <Lights
          isSelected={isSelected}
          isVisible={data.visible}
          key={`light_${index}`}
          brightness={data.brightness}
          target={data.target}
          position={data.position}
          color={data.color}
          onUpdate={(lightData) => sendLightDataToServer(lightData)}
          type="directional"  // 이 줄을 추가
        />
      </React.Fragment>
    );
  }

  // Spot 조명 설정 함수
  function setLightSpot(index: number, data: any) {
    return (
      <React.Fragment key={`spot_${index}`}>
        <DragControls
          key={index}
          matrix={data.matrix.clone()}
          autoTransform={selectedIndex === index}
          onDragStart={() => setPivotHovered(true)}
          onDragEnd={() => setPivotHovered(false)}
          onDrag={(local) => {
            onDragUpdate(local);
          }}
        >
          <mesh visible={selectedIndex === index}>
            <boxGeometry args={[0.5, 0.5, 0.5]} />
            <meshBasicMaterial color="yellow" />
          </mesh>
        </DragControls>
        <Lights
          isSelected={selectedIndex === index}
          isVisible={data.visible}
          key={`light_${index}`}
          brightness={data.brightness}
          target={data.target}
          position={data.position}
          color={data.color}
          onUpdate={(lightData) => sendLightDataToServer(lightData)}
          type="spot"  // 이 줄을 추가
        />
      </React.Fragment>
    );
  }

  // 조명 설정 함수
  function SetLight() {
    return (
      <>
        {sidebarData.map((data, index) => {
          const isSelected = selectedIndex === index;

          if (data.item !== itemEnum.light) {
            return;
          }
          if (data.type === lightEnum.ambient) {
            return setLightAmbient(index, data);
          } else if (data.type === lightEnum.directional) {
            return setLightDirectional(index, data, isSelected);
          } else if (data.type === lightEnum.spot) {
            return setLightSpot(index, data);
          }
          return null;
        })}
      </>
    );
  }
};



/*
/server.js

const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 5001;

app.use(cors());
app.use(bodyParser.json());

// 240711_1437_glory : React 앱의 정적 파일 제공
app.use(express.static(path.join(__dirname, 'build')));

// 240711_1437_glory : API 라우트
app.get('/api', (req, res) => {
  res.json({ message: 'Welcome to the API' });
});

// 240711_1437_glory : 새로운 라우트: Light 데이터 수신
app.post('/api/light', (req, res) => {
  const lightData = req.body;
  console.log('Received light data:', JSON.stringify(lightData, null, 2)); // 240711_1438_glory : 여기에서 lightData를 처리하거나 저장할 수 있습니다.
  res.json({ message: 'Light data received successfully' });
});

// 240711_1438_glory : 그 외 모든 요청은 React 앱으로 전달
app.get('*', (req, res) => {
  res.sendFile(path.join(__dirname, 'build', 'index.html'));
});

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});

*/