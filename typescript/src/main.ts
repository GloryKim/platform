import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as fs from 'fs';
import axios from 'axios';

async function bootstrap() {
  const app = await NestFactory.create(AppModule, {
    httpsOptions: {
      key: fs.readFileSync('server.key'),
      cert: fs.readFileSync('server.cert'),
    }
  });

  app.enableCors({
    origin: '*',
  });
  // 241022_1106_glory : 실행명령어 npm run start:dev
  // 241022_1108_glory : /Users/mac/_github/glory/1/index.js 여기랑 상호작용하는 코드
  // 자체 서명된 인증서 허용하는 axios 설정
  const httpsAgent = new (require('https').Agent)({  
    rejectUnauthorized: false  // SSL 인증서 검증 비활성화
  });

  async function sendSignal() {
    try {
      const response = await axios.post('https://localhost:10873/signal', { data: 'some data' }, { httpsAgent }); //241022_1108_glory : 해당 경로에 원하는 데이터와 더불어, 경로를 설정해주면 됨, 비동기로 쏴줌
      console.log('Signal sent successfully:', response.data);
      console.log('result1 연산 결과:', result2);
    } catch (error) {
      console.error('Failed to send signal:', error.message);
      console.log('result1 연산 결과:', result1); //241022_1421_glory : 아래 plus_glory 함수를 통한 규칙으로 나온 값들을 console.log에 찍음
      
    }
  }

  setInterval(sendSignal, 5000);

  await app.listen(10874);
}

function plus_glory(x: number, y: number): number { //241022_1451_glory : 이 구문에서 맨 오른쪽 number 제거해도 됨
  return x+y;
}
const result1: number = plus_glory(1,2);//241022_1420_glory : number1에 명시적으로 : number라고 타입을 부여함
const result2 = plus_glory(1,3); //241022_1419_glory :명시적으로 타입을 부여하지 않아도 타입 스크립트는 result2 타입을 number라고 알고있다. , 다만 매개변수에는 타입을 부여해주어야 한다.



bootstrap();

