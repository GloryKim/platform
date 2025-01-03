import { Controller, Get, Res } from '@nestjs/common';
import { Response } from 'express';
import { ImageService } from './image.service';

@Controller('image')
export class ImageController {
  constructor(private readonly imageService: ImageService) {}

  @Get('/fetch-and-process')
  async fetchAndProcessImage(@Res() res: Response) {
    try {
      // 1. Node.js 서버에서 이미지 가져오기
      const imagePath = await this.imageService.fetchImage();

      // 2. 이미지를 처리하고 버퍼로 변환
      const processedImage = await this.imageService.processImage(imagePath);

      // 3. 변환된 이미지를 클라이언트로 응답
      res.writeHead(200, { 'Content-Type': 'image/jpeg' });
      res.end(processedImage); // 처리된 이미지 전송
    } catch (error) {
      console.error('이미지 처리 오류:', error);
      res.status(500).send('이미지 처리 중 오류 발생');
    }
  }
}
