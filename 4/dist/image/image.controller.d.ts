import { Response } from 'express';
import { ImageService } from './image.service';
export declare class ImageController {
    private readonly imageService;
    constructor(imageService: ImageService);
    fetchAndProcessImage(res: Response): Promise<void>;
}
