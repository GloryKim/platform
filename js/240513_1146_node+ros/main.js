const WebSocketClient = require('websocket').client;
const express = require('express');
const http = require('http').Server(express());
const io = require('socket.io')(http);
const app = express();

app.use(express.static('public'));

const client = new WebSocketClient();

function connectWebSocket() {
  client.connect('ws://localhost:9090');

  client.on('connect', function(connection) {
    console.log('WebSocket Client Connected');

    // 특정 토픽 구독 설정
    const topics = [
      "/cam_image1"
    ];

    topics.forEach(topic => {
      connection.send(JSON.stringify({
        op: "subscribe",
        topic: topic
      }));
    });

    connection.on('error', function(error) {
      console.log("Connection Error: " + error.toString());
    });

    connection.on('close', function(code, description) {
        console.log('WebSocket Connection Closed');
        console.log('Code:', code, 'Description:', description);
    });
      

    connection.on('message', function(message) {
      if (message.type === 'utf8') {
        console.log("Received: " + message.utf8Data);
        io.emit('ros_message', message.utf8Data); // Socket.IO를 통해 메시지를 클라이언트에 전송
      }
    });
  });

  client.on('connectFailed', function(error) {
    console.log('Connect Error: ' + error.toString());
    setTimeout(connectWebSocket, 1000); // 연결 실패시 5초 후 재연결 시도
  });
}

connectWebSocket(); // 웹소켓 연결 시작

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/public/index.html');
});

http.listen(3000, function() {
  console.log('Server running on port 3000');
});


//public/index.html
/*
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>ROS Web Interface</title>
<script src="/socket.io/socket.io.js"></script>
<script>
  document.addEventListener('DOMContentLoaded', function() {
    var socket = io();
    socket.on('ros_message', function(msg) {
      console.log('Received message: ' + msg);
      var node = document.createElement("LI");
      var textnode = document.createTextNode(msg);
      node.appendChild(textnode);
      document.getElementById("messages").appendChild(node);
    });
  });
</script>
</head>
<body>
<h1>ROS Messages</h1>
<ul id="messages"></ul>
</body>
</html>
*/

//Code: 1009 Description: Frame size of 16384218 bytes exceeds maximum accepted frame size : 상기 오류는 프레임사이즈 측 bag파일이 커서 발생하는 문제