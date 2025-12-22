"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.ImageService = void 0;
const common_1 = require("@nestjs/common");
const axios_1 = require("@nestjs/axios");
const fs = require("fs");
const sharp = require("sharp");
const path_1 = require("path");
let ImageService = class ImageService {
    constructor(httpService) {
        this.httpService = httpService;
    }
    async fetchImage() {
        const imageUrl = 'https://localhost:10874/processed-image';
        const imagePath = (0, path_1.join)(__dirname, '../../downloads/image.jpg');
        const response = await this.httpService.axiosRef({
            url: imageUrl,
            method: 'GET',
            responseType: 'arraybuffer',
            httpsAgent: new (require('https')).Agent({ rejectUnauthorized: false }),
        });
        fs.writeFileSync(imagePath, response.data);
        return imagePath;
    }
    async processImage(imagePath) {
        const processedImage = await sharp(imagePath)
            .grayscale()
            .toBuffer();
        return processedImage;
    }
};
exports.ImageService = ImageService;
exports.ImageService = ImageService = __decorate([
    (0, common_1.Injectable)(),
    __metadata("design:paramtypes", [axios_1.HttpService])
], ImageService);
//# sourceMappingURL=image.service.js.map