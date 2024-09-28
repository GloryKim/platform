import { Injectable } from '@nestjs/common';
import { HttpService } from '@nestjs/axios'; // HttpService를 @nestjs/axios에서 가져오기
import * as fs from 'fs';
import * as sharp from 'sharp';
import { join } from 'path';

@Injectable()
export class ImageService {
  constructor(private readonly httpService: HttpService) {}

  // Node.js 서버에서 이미지 가져오기
  async fetchImage(): Promise<string> {
    const imageUrl = 'https://localhost:10874/processed-image';
    const imagePath = join(__dirname, '../../downloads/image.jpg');

    const response = await this.httpService.axiosRef({
      url: imageUrl,
      method: 'GET',
      responseType: 'arraybuffer',
      httpsAgent: new (require('https')).Agent({ rejectUnauthorized: false }), // SSL 인증서 무시 설정
    });

    // 이미지 파일을 로컬에 저장
    fs.writeFileSync(imagePath, response.data);

    return imagePath; // 저장된 파일 경로 반환
  }

  // 이미지 처리 후 클라이언트에게 반환
  async processImage(imagePath: string): Promise<Buffer> {
    const processedImage = await sharp(imagePath)
      .grayscale() // 예시: 이미지 그레이스케일 처리
      .toBuffer();

    return processedImage; // 변환된 이미지 데이터를 반환
  }
}
