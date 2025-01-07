const http = require('http');
const hostname = '**.***.***.**'; //240531_1643_glory : PC에 물려있는 공유기 자체의 IP정보 즉 다른망의 IP가 직접적으로 필요로 하다. (예 : 12.34.56.78)
const port = &$@$; //240531_1661_glory : 외부에서는 &$@$ 이걸로 접속할 예정인데, 내부에서는 &$@!으로 호스팅중이니 공유기 차원에서 두개가 동일한 거라는 포트포워딩 작업이 필요로 하다. (예 : 1234(외부)<->2345(내부), 포트 번호가 같아도 괜찮음)
// GET 요청 보내기
const getRequest = http.request({
  hostname,
  port,
  path: '/',
  method: 'GET',
}, (res) => {
  let data = '';
  res.on('data', (chunk) => {
    data += chunk;
  });
  res.on('end', () => {
    console.log('GET response:', data);
  });
}).on('error', (err) => {
  console.error(`GET error: ${err.message}`);
});
getRequest.end();
// POST 요청 보내기
const postData = JSON.stringify({
  message: 'hello',
});
const postRequest = http.request({
  hostname,
  port,
  path: '/',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Content-Length': postData.length,
  },
}, (res) => {
  let data = '';
  res.on('data', (chunk) => {
    data += chunk;
  });
  res.on('end', () => {
    console.log('POST response:', data);
  });
}).on('error', (err) => {
  console.error(`POST error: ${err.message}`);
});
postRequest.write(postData);
postRequest.end();