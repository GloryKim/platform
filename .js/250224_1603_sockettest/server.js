const net = require('net');

const SERVER_IP = '12.23.45.56'; // A 서버 외부 IP
const SERVER_PORT = 12345; // 포트포워딩된 외부 포트

const client = new net.Socket();

client.connect(SERVER_PORT, SERVER_IP, () => {
    console.log(`서버(${SERVER_IP}:${SERVER_PORT})에 연결됨`);
    
    // 데이터 전송
    client.write('안녕하세요, A 서버!');
});

client.on('data', (data) => {
    console.log('서버 응답:', data.toString());
    
    // 연결 종료
    client.destroy();
});

client.on('close', () => {
    console.log('서버와의 연결 종료');
});

client.on('error', (err) => {
    console.error('소켓 에러:', err.message);
});
