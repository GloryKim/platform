const express = require('express'); //240921_2238_glory : Node.js에서 Express는 웹 애플리케이션 프레임워크로, 서버 측에서 HTTP 요청을 처리하고 웹 애플리케이션, API를 구축하도록 지원
const https = require('https');
const fs = require('fs');
const socketIo = require('socket.io');
const bodyParser = require('body-parser'); //240922_0220_glory : POST 요청의 JSON 데이터를 파싱하기 위한 body-parser 사용
const sharp = require('sharp'); // 240928_2314_glory : 이미지 영상처리를 위한 간이 라이브러리
const axios = require('axios'); // 240928_2329_glory : HTTP 요청을 위한 axios 추가
const path = require('path'); // path 모듈을 추가하여 파일 경로 처리



// SSL 인증서 로드
const options = {
  key: fs.readFileSync('server.key'),
  cert: fs.readFileSync('server.cert')
};

const app = express();
const server = https.createServer(options, app);
const io = socketIo(server);


//241009_1558_glory : 포인트클라우드 수신을 위한 내용 미리 반영
const net = require('net');
const { Buffer } = require('buffer');


// 서버에 저장된 포인트 클라우드 데이터를 저장할 변수
let latestPointCloudData = null;




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













//https://localhost:10873/pointscloud
// 포인트 클라우드 데이터를 받아서 저장
app.post('/pointscloud', (req, res) => {
  const pointCloudData = req.body; // 요청 본문에서 JSON 데이터 추출
  console.log(`Received point cloud with ${pointCloudData.point_count} points`);

  // 받은 데이터를 변수에 저장하여 이후 GET 요청에 사용할 수 있도록 함
  latestPointCloudData = pointCloudData;

  // 로그 파일로 데이터 저장
  fs.appendFile('point_cloud_data.log', JSON.stringify(pointCloudData) + '\n', (err) => {
    if (err) {
      console.error('Error saving point cloud data to log file:', err);
      return res.status(500).send('Error saving point cloud data');
    }

    // 성공적으로 파일에 저장되면 응답 전송
    res.status(200).send('Point cloud data received and saved successfully');
  });
});

// 포인트 클라우드 데이터를 반환하는 API
app.get('/api/pointscloud', (req, res) => {
  if (latestPointCloudData) {
    // 실시간으로 받은 데이터를 클라이언트에 반환
    res.json(latestPointCloudData);
  } else {
    // 데이터가 없을 경우 에러 응답
    res.status(404).send({ error: 'No point cloud data available' });
  }
});

// 정적 파일로 index2.html 제공
app.get('/pointscloud', (req, res) => {
  res.sendFile(path.join(__dirname, 'public/index2.html'));
});

// favicon.ico 요청 무시 (404 방지)
app.get('/favicon.ico', (req, res) => res.status(204));


























//241007_1420_glory : 아래쪽에 있는 받는쪽 코드를 받는쪽 PC에 붙여 놓고크롬창 옆에 내용을 입력하면 전달되고 https://localhost:10873/time-monitor
// 현재 시간을 가져오는 함수
// 포트차단이 걸려있을경우 해제 및 특정포트 허가가 필요하다면 포트포워딩도 필요한 상황임
function getCurrentTime() {
  return new Date().toISOString(); // ISO 형식의 현재 시간 반환
}
// 새 필드: /time-monitor
// 1.2.3.4:30873 서버로 현재 시간을 전송
app.get('/time-monitor', (req, res) => {
  const currentTime = getCurrentTime();
  console.log('현재 시간:', currentTime);

  const agent = new https.Agent({
    rejectUnauthorized: false,
  });

  axios.post('http://1.2.3.4:30873/time-data', { time: currentTime }, {
    headers: {
      'Content-Type': 'application/json',
    },
    httpsAgent: agent,
  })
  .then(response => {
    console.log('현재 시간 전송 성공:', response.data);
    res.status(200).send('현재 시간 전송 완료');
  })
  .catch(err => {
    console.error('현재 시간 전송 중 오류 발생:', err);
    res.status(500).send('현재 시간 전송 실패');
  });
});

/*
(base) server@test:~glory/glory/glory$ sudo ufw allow 30873/tcp
Rule added
Rule added (v6)
(base) server@test:~glory/glory/glory$ node main.js 
시간 모니터링 서버가 30873 포트에서 실행 중입니다.
요청 수신: { time: '2024-10-07T05:19:20.955Z' }
수신한 시간 데이터: { time: '2024-10-07T05:19:20.955Z' }
^C
(base) server@test:~glory/glory/glory$ 
*/
//241007_1423_glory : 위에 구문은 받는쪽에 대해서 초기에 방화벽 허가가 필요한 부분에 대한 내용이며, 아래는 받는쪽 코드이다. http로 했으니 참고할 것 // cors가 과연 필수적일까? 그리고 공유기 포트포워딩도 필수적일까? 이것은 아직도 의문임 더 좋은 방법 있는지 검토할 것
//241007_1724_glory : 아래는 받는쪽 코드이니 참고할 것
/*
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const PORT = 30873;

const cors = require('cors');
app.use(cors());  // 모든 도메인에서의 요청 허용

app.use(bodyParser.json());

// 현재 시간을 받는 필드 추가
app.post('/time-data', (req, res) => {
  console.log('요청 수신:', req.body);  // 로그 추가
  const timeData = req.body;
  console.log('수신한 시간 데이터:', timeData);

  res.status(200).send('시간 데이터 수신 완료');
});

// 서버 실행
app.listen(PORT, () => {
console.log(`시간 모니터링 서버가 ${PORT} 포트에서 실행 중입니다.`);
});
*/














// 240928_2314_glory : 새로운 필드 추가: /processed-image
// public/sample.jpg 파일을 이미지 처리한 후 localhost:10874로 전송하는 필드
app.get('/processed-image', (req, res) => {
  const inputImagePath = 'public/sample.jpg'; // 처리할 이미지 경로

  console.log('이미지 처리 시작');

  sharp(inputImagePath)
    .resize(200, 200) // 이미지 크기 조정 (예: 200x200으로 리사이즈)
    .toBuffer() // 이미지 데이터를 버퍼로 변환
    .then((data) => {
      console.log(`이미지 처리 완료, 크기: ${data.length} bytes`);

      const agent = new https.Agent({
        rejectUnauthorized: false, // SSL 검증 비활성화
      });

      // 이미지 데이터를 10874 포트의 NestJS 서버로 전송
      axios.post('https://localhost:10874/upload', data, {
        headers: {
          'Content-Type': 'image/jpeg',
        },
        httpsAgent: agent, // SSL 옵션 추가
      })
      .then((response) => {
        console.log('이미지 전송 성공:', response.data);
        res.status(200).send('이미지 전송 완료');
      })
      .catch((err) => {
        console.error('이미지 전송 중 오류 발생:', err);
        res.status(500).send('이미지 전송 실패');
      });
    })
    .catch((err) => {
      console.error('이미지 처리 중 오류 발생:', err);
      res.status(500).send('이미지 처리 오류');
    });
});













// 240928_2314_glory : 새로운 필드 추가: processed-image_fastapi
// public/sample.jpg 파일을 이미지 처리한 후 localhost:20873으로 전송하는 필드
// 241004_1815_glory : 실행방법 : 크롬창 열고 https://localhost:10873/processed-image_fastapi
app.get('/processed-image_fastapi', (req, res) => {
  const inputImagePath = 'public/sample.jpg'; // 처리할 이미지 경로

  console.log('이미지 처리 시작');

  sharp(inputImagePath)
    .resize(200, 200) // 이미지 크기 조정 (예: 200x200으로 리사이즈)
    .toBuffer() // 이미지 데이터를 버퍼로 변환
    .then((data) => {
      console.log(`이미지 처리 완료, 크기: ${data.length} bytes`);

      const agent = new https.Agent({
        rejectUnauthorized: false, // SSL 검증 비활성화
      });

      // 이미지 데이터를 10874 포트의 NestJS 서버로 전송
      axios.post('https://localhost:20873/upload', data, {
        headers: {
          'Content-Type': 'image/jpeg',
        },
        httpsAgent: agent, // SSL 옵션 추가
      })
      .then((response) => {
        console.log('이미지 전송 성공:', response.data);
        res.status(200).send('이미지 전송 완료');
      })
      .catch((err) => {
        console.error('이미지 전송 중 오류 발생:', err);
        res.status(500).send('이미지 전송 실패');
      });
    })
    .catch((err) => {
      console.error('이미지 처리 중 오류 발생:', err);
      res.status(500).send('이미지 처리 오류');
    });
});

















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