import { Module } from '@nestjs/common';
import { AppController } from './app.controller';

@Module({
  imports: [],
  controllers: [AppController], // AppController 등록
  providers: [],
})
export class AppModule {}
