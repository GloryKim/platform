const express = require('express');
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

io.on('connection', (socket) => {
  console.log('New user connected');

  // WebRTC signaling
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

// 서버 실행
const PORT = process.env.PORT || 12000;
server.listen(PORT, () => {
  console.log(`HTTPS Server running on port ${PORT}`);
});
