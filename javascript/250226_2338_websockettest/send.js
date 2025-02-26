const WebSocket = require('ws');

const ws = new WebSocket('ws://1.2.3.4:5');

ws.on('open', () => {
  console.log('서버에 연결됨');
  ws.send('클라이언트 메시지: 안녕하세요');
});

ws.on('message', (data) => {
  console.log('서버 응답:', data.toString()); //data라고만 하면 버퍼가 옴
});

ws.on('close', () => {
  console.log('서버와의 연결 종료');
});

ws.on('error', (error) => {
  console.error('오류 발생:', error);
});
