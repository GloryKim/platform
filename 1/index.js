const express = require('express'); //240921_2238_glory : Node.js에서 Express는 웹 애플리케이션 프레임워크로, 서버 측에서 HTTP 요청을 처리하고 웹 애플리케이션, API를 구축하도록 지원
const https = require('https');
const fs = require('fs');
const socketIo = require('socket.io');

// SSL 인증서 로드
const options = {
  key: fs.readFileSync('server.key'),
  cert: fs.readFileSync('server.cert')
};

const app = express();
const server = https.createServer(options, app);
const io = socketIo(server);

// 'public' 폴더에 정적 파일 제공
app.use(express.static('public'));










//2409221_2238_glory : 웹소켓 연결이 들어왔을때 아래 동작이 진행되는 것으로 구현
io.on('connection', (socket) => {
  console.log('클라이언트 서버를 통해 신규 유저가 연결 되었습니다.');

  // 240921_2239_Glory : WebRTC signaling
  socket.on('offer', (offer) => {
    socket.broadcast.emit('offer', offer);
  });

  socket.on('answer', (answer) => {
    socket.broadcast.emit('answer', answer);
  });

  socket.on('ice-candidate', (candidate) => {
    socket.broadcast.emit('ice-candidate', candidate);
  });
});












//240921_2238_glory : localhost:10873으로 배포 중
const PORT = process.env.PORT || 10873;
server.listen(PORT, () => {
  console.log(`HTTPS Server running on port ${PORT}`);
});