import { HttpService } from '@nestjs/axios';
export declare class ImageService {
    private readonly httpService;
    constructor(httpService: HttpService);
    fetchImage(): Promise<string>;
    processImage(imagePath: string): Promise<Buffer>;
}
