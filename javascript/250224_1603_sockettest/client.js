const net = require('net');

const SERVER_PORT = 12345; // 내부 포트, 여기에 접속하려면 12.23.45.56으로 접속해야함

const server = net.createServer((socket) => {
    console.log('클라이언트 연결됨:', socket.remoteAddress, socket.remotePort);

    socket.on('data', (data) => {
        console.log('수신된 데이터:', data.toString());

        // 클라이언트에게 응답 전송
        socket.write(`서버 응답: ${data.toString()}`);
    });

    socket.on('close', () => {
        console.log('클라이언트 연결 종료');
    });

    socket.on('error', (err) => {
        console.error('소켓 에러:', err.message);
    });
});

server.listen(SERVER_PORT, () => {
    console.log(`서버가 포트 ${SERVER_PORT}에서 대기 중...`);
});
