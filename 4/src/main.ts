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
    } catch (error) {
      console.error('Failed to send signal:', error.message);
    }
  }

  setInterval(sendSignal, 5000);

  await app.listen(10874);
}
bootstrap();
