const http = require('http');
const hostname = '0.0.0.0'; // 240531_1640_glory : 모든 IP 주소에서 접속 가능하도록 설정 + 해당 부분에서 AWS 특정 IP만 접속 가능하게 세팅 가능
const port = &$@!; // 240531_1644_glory : 어떤 포트로 열지를 결정해야함 해당 포트는 titan 내부 포트로 예를들어 1234로 설정할 경우 외부에서 1234로 연결 시도해도 공유기에 외부에서 연결받을 포트와 내부 포트와 포워딩을 안해주면 연결이 안된다.
const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  if (req.method === 'GET' && req.url === '/') {
    res.end('Hello from the server!');
  } else if (req.method === 'POST' && req.url === '/') {
    let body = '';
    req.on('data', (chunk) => {
      body += chunk.toString();
    });
    req.on('end', () => {
      console.log('Received message:', body);
      res.end('Message received by the server');
    });
  } else {
    res.statusCode = 404;
    res.end('Not found');
  }
});
server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
 

 

 

 

 

 