import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as fs from 'fs';  // fs 모듈을 import

async function bootstrap() {
  const app = await NestFactory.create(AppModule, {
    httpsOptions: {
      key: fs.readFileSync('server.key'),   // SSL 인증서 키 파일 읽기
      cert: fs.readFileSync('server.cert'), // SSL 인증서 파일 읽기
    }
  });

  // CORS 활성화 (필요 시)
  app.enableCors({
    origin: '*',  // 또는 허용할 도메인 지정
  });

  await app.listen(10874);
}
bootstrap();
