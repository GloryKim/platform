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
var __param = (this && this.__param) || function (paramIndex, decorator) {
    return function (target, key) { decorator(target, key, paramIndex); }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.AppController = void 0;
const common_1 = require("@nestjs/common");
const fs = require("fs");
const path = require("path");
let AppController = class AppController {
    getHello() {
        throw new Error('Method not implemented.');
    }
    async handleUpload(req, res) {
        const chunks = [];
        console.log('이미지 전송 요청을 받았습니다.');
        req.on('data', (chunk) => {
            console.log(`받은 데이터 크기: ${chunk.length} bytes`);
            chunks.push(chunk);
        });
        req.on('end', () => {
            const imageBuffer = Buffer.concat(chunks);
            console.log(`총 데이터 크기: ${imageBuffer.length} bytes`);
            const filePath = path.join(__dirname, '../uploads/received_image.jpg');
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
};
exports.AppController = AppController;
__decorate([
    (0, common_1.Post)('/upload'),
    __param(0, (0, common_1.Req)()),
    __param(1, (0, common_1.Res)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, Object]),
    __metadata("design:returntype", Promise)
], AppController.prototype, "handleUpload", null);
exports.AppController = AppController = __decorate([
    (0, common_1.Controller)()
], AppController);
//# sourceMappingURL=app.controller.js.map