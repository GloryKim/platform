const express = require('express');
const multer = require('multer');
const path = require('path');
const https = require('https'); // HTTPS 모듈 추가
const fs = require('fs'); // 파일 시스템 모듈 추가

const app = express();

// HTTPS 서버 설정을 위한 인증서 파일 로드
const privateKey = fs.readFileSync('key.pem', 'utf8');
const certificate = fs.readFileSync('cert.pem', 'utf8');
const credentials = {
  key: privateKey,
  cert: certificate,
  passphrase: '123qwe' // 여기에 개인 키의 암호를 입력하세요. //인증서 생성 방법은 터미널에 이거 입력 openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365
};


const port = 8080; // 원하는 포트로 변경 가능

// 'save' 폴더에 파일 저장 설정
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'save/') // 파일이 저장될 경로
  },
  filename: function (req, file, cb) {
    // 파일명 설정
    cb(null, file.fieldname + '-' + Date.now() + path.extname(file.originalname))
  }
});

const upload = multer({ storage: storage });

// 루트 경로에 POST 요청 처리
app.post('/upload', upload.single('file'), (req, res) => {
  // 파일이 성공적으로 업로드되면 응답을 보냅니다.
  // 성공 응답을 더 구체적으로 구성할 수 있습니다.
  res.send({
    message: 'File uploaded successfully',
    fileInfo: req.file
  });
});

// HTTPS 서버 생성 및 실행
const httpsServer = https.createServer(credentials, app);
httpsServer.listen(port, () => {
  console.log(`Server is running on https://192.168.1.9:${port}`);
}).on('error', (err) => {
  console.error('Server start error:', err);
});
