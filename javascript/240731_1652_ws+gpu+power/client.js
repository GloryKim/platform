const WebSocket = require('ws');

const ws = new WebSocket('ws://192.168.0.12:8080'); //240731_1653_glory : 현재는 같은 공유기에 연결된 PC를 세팅했습니다. 이 안에 들어갈 주소는 server 측 주소입니다.

ws.on('open', () => {
  console.log('Connected to server');
});

ws.on('message', (data) => {
  console.log(`Received: ${data}`);
});

ws.on('error', (error) => {
  console.error(`WebSocket error: ${error}`);
});

ws.on('close', () => {
  console.log('Disconnected from server');
});
