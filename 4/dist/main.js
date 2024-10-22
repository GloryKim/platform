"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const core_1 = require("@nestjs/core");
const app_module_1 = require("./app.module");
const fs = require("fs");
const axios_1 = require("axios");
async function bootstrap() {
    const app = await core_1.NestFactory.create(app_module_1.AppModule, {
        httpsOptions: {
            key: fs.readFileSync('server.key'),
            cert: fs.readFileSync('server.cert'),
        }
    });
    app.enableCors({
        origin: '*',
    });
    const httpsAgent = new (require('https').Agent)({
        rejectUnauthorized: false
    });
    async function sendSignal() {
        try {
            const response = await axios_1.default.post('https://localhost:10873/signal', { data: 'some data' }, { httpsAgent });
            console.log('Signal sent successfully:', response.data);
        }
        catch (error) {
            console.error('Failed to send signal:', error.message);
        }
    }
    setInterval(sendSignal, 5000);
    await app.listen(10874);
}
bootstrap();
//# sourceMappingURL=main.js.map