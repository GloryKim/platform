import { Controller, Post, Req, Res } from '@nestjs/common';
import { Request, Response } from 'express';
import * as fs from 'fs';
import * as path from 'path';

@Controller()
export class AppController {
  getHello(): any {
    throw new Error('Method not implemented.');
  }
  @Post('/upload')
  async handleUpload(@Req() req: Request, @Res() res: Response) {
    const chunks: any[] = [];

    console.log('이미지 전송 요청을 받았습니다.');

    // 데이터가 스트리밍으로 들어올 때 로그 출력
    req.on('data', (chunk) => {
      console.log(`받은 데이터 크기: ${chunk.length} bytes`);
      chunks.push(chunk);
    });

    // 데이터 수신이 완료되면 처리
    req.on('end', () => {
      const imageBuffer = Buffer.concat(chunks);
      console.log(`총 데이터 크기: ${imageBuffer.length} bytes`);

      // 저장할 파일 경로 설정
      const filePath = path.join(__dirname, '../uploads/received_image.jpg');

      // 이미지 파일로 저장
      fs.writeFile(filePath, imageBuffer, (err) => {
        if (err) {
          console.error('nest : 이미지 저장 중 오류 발생:', err);
          return res.status(500).send('node야 나 nest인데 이미지 저장 실패');
        }

        console.log('nest : 이미지 저장 성공:', filePath);
        res.status(200).send('node야 나 nest인데 이미지 저장 성공');
      });
    });
  }
}
