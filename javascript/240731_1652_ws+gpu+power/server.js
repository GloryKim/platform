const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const { exec } = require('child_process');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

function getGpuPowerUsage() {
  return new Promise((resolve, reject) => {
    exec('nvidia-smi --query-gpu=power.draw --format=csv,noheader,nounits', (error, stdout, stderr) => {
      if (error) {
        reject(`exec error: ${error}`);
        return;
      }
      resolve(stdout.trim());
    });
  });
}

wss.on('connection', (ws) => {
  console.log('New client connected');
  
  const interval = setInterval(() => {
    getGpuPowerUsage().then((powerUsage) => {
      ws.send(powerUsage);
    }).catch((error) => {
      ws.send(`Error: ${error}`);
    });
  }, 1000); // 1초마다 전력 소모량 전송

  ws.on('close', () => {
    console.log('Client disconnected');
    clearInterval(interval);
  });
});

server.listen(8080, '0.0.0.0', () => {
  console.log('Server is listening on port 8080');
});
