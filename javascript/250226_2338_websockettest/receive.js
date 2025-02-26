const WebSocket = require('ws');

const server = new WebSocket.Server({ host: '0.0.0.0', port: 7880 });

server.on('connection', (ws, req) => {
  console.log('클라이언트 연결:', req.connection.remoteAddress);

  ws.on('message', (message) => {
    console.log('수신 메시지:', message.toString()); //message라고만 하면 버퍼만 옴
    ws.send('서버 응답: 메시지 수신 완료');
  });

  ws.on('close', () => {
    console.log('연결 종료');
  });
});

server.on('listening', () => {
  console.log('웹소켓 서버 실행 중: ws://12.23.34.56:7880');
});
