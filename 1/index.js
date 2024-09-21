const express = require('express'); //240921_2238_glory : Node.js에서 Express는 웹 애플리케이션 프레임워크로, 서버 측에서 HTTP 요청을 처리하고 웹 애플리케이션, API를 구축하도록 지원
const https = require('https');
const fs = require('fs');
const socketIo = require('socket.io');
const bodyParser = require('body-parser'); //240922_0220_glory : POST 요청의 JSON 데이터를 파싱하기 위한 body-parser 사용


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
//app.use(bodyParser.json()); //240922_0221_glory : JSON 형식의 요청 데이터를 처리하기 위해 body-parser 사용
/*
상기 내용 쓰면 오류 발생
mac@macui-MacBookPro 1 % node index.js
HTTPS Server running on port 10873
PayloadTooLargeError: request entity too large
    at readStream (/Users/mac/glory/1/node_modules/raw-body/index.js:163:17)
    at getRawBody (/Users/mac/glory/1/node_modules/raw-body/index.js:116:12)
    at read (/Users/mac/glory/1/node_modules/body-parser/lib/read.js:79:3)
    at jsonParser (/Users/mac/glory/1/node_modules/body-parser/lib/types/json.js:138:5)
    at Layer.handle [as handle_request] (/Users/mac/glory/1/node_modules/express/lib/router/layer.js:95:5)
    at trim_prefix (/Users/mac/glory/1/node_modules/express/lib/router/index.js:328:13)
    at /Users/mac/glory/1/node_modules/express/lib/router/index.js:286:9
    at Function.process_params (/Users/mac/glory/1/node_modules/express/lib/router/index.js:346:12)
    at next (/Users/mac/glory/1/node_modules/express/lib/router/index.js:280:10)
    at serveStatic (/Users/mac/glory/1/node_modules/serve-static/index.js:75:16)
mac@macui-MacBookPro 1 % 
*/
app.use(bodyParser.json({ limit: '100mb' })); // 240922_0141_glory : 기본 크기 제한을 100MB로 설정




//240921_2302_glory : go+sendRequest를 무차별로 받을때 
app.post('/api/test', (req, res) => { //240922_0135_glory : go쪽에서 post로 보내고 있으니 get에서 post로 수정함
  //console.log('go서버에서 연락이 왔어요.');
  //res.send('Test response');//일단 주석
  const receivedData = req.body; //240922_0223_glory : POST로 받은 JSON 데이터를 가져옴
  console.log('Received data:', receivedData);

  // 로그 파일에 데이터 저장
  logDataToFile(receivedData);

  res.status(200).send('Data received and logged'); // 클라이언트에게 응답
});





// 240922_0128_glory : go 서버로 받아진 대용량 로그 파일에 데이터를 저장하는 함수
function logDataToFile(data) {
  fs.appendFile('received_data.log', JSON.stringify(data) + '\n', (err) => {
    if (err) {
      console.error('Error logging data to file:', err);
    } else {
      console.log('Data logged to file successfully');
    }
  });
}







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