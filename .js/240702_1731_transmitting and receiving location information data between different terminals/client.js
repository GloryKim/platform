const http = require('http');
const fs = require('fs');

const hostname = '***.***.***.***';
const port = ***;

// 로그 파일 스트림 생성
const logStream = fs.createWriteStream('received_logs.txt', {flags: 'a'});

const server = http.createServer((req, res) => {
    if (req.method === 'POST' && req.url === '/log') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            try {
                const logData = JSON.parse(body);
                const logMessage = logData.log;
                
                // 받은 로그를 파일에 저장
                logStream.write(logMessage + '\n');
                
                console.log('로그 수신:', logMessage);
                
                res.writeHead(200, {'Content-Type': 'text/plain'});
                res.end('로그 수신 완료\n');
            } catch (error) {
                console.error('로그 처리 오류:', error);
                res.writeHead(400, {'Content-Type': 'text/plain'});
                res.end('Invalid log format\n');
            }
        });
    } else {
        res.writeHead(404, {'Content-Type': 'text/plain'});
        res.end('404 Not Found\n');
    }
});

server.listen(port, hostname, () => {
    console.log(`로그 수신 서버가 http://${hostname}:${port}/에서 실행 중입니다.`);
});