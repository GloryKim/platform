const http = require('http');
const url = require('url');
const fs = require('fs');
const axios = require('axios');

const hostname = '***.***.***.***';
const port = ***;
const logServerUrl = 'http://***.***.***.***:***/***';

let swiftData = [];
let lidarData = [];
let lastPrintTime = 0;
let swiftReady = false;
let lidarReady = false;
let matchCount = 0;
let mismatchCount = 0;

// 로그 파일 스트림 생성
const logStream = fs.createWriteStream('server_log.txt', {flags: 'a'});

// console.log를 오버라이드하여 파일에 로깅하고 다른 서버로 전송하도록 함
const originalConsoleLog = console.log;
console.log = function() {
    const args = Array.from(arguments);
    const timestamp = new Date().toISOString();
    const logMessage = `[${timestamp}] ${args.join(' ')}`;
    
    // 파일에 로깅
    logStream.write(logMessage + '\n');
    
    // 다른 서버로 로그 전송
    axios.post(logServerUrl, { log: logMessage })
        .catch(error => {
            originalConsoleLog('로그 전송 실패:', error.message);
        });
    
    originalConsoleLog.apply(console, args);
};

const server = http.createServer((req, res) => {
    let body = '';
    req.on('data', chunk => {
        body += chunk.toString();
    });
    req.on('end', () => {
        const parsedUrl = url.parse(req.url);
        if (req.method === 'POST') {
            if (parsedUrl.pathname === '/swift') {
                handleSwiftData(body, res);
            } else if (parsedUrl.pathname === '/lidar') {
                handleLidarData(body, res);
            } else {
                res.writeHead(404, {'Content-Type': 'text/plain'});
                res.end('404 Not Found');
            }
        } else {
            res.writeHead(405, {'Content-Type': 'text/plain'});
            res.end('Method Not Allowed');
        }
    });
});

function handleSwiftData(body, res) {
    try {
        const data = JSON.parse(body);
        swiftData.push({
            timestamp: new Date().toISOString(),
            uniqueID: data.uniqueID,
            x: data.deviceCoordinates.x,
            y: data.deviceCoordinates.y,
            z: data.deviceCoordinates.z
        });
        if (!swiftReady) {
            console.log('Swift 준비');
            swiftReady = true;
        }
        logSwiftData(data);
        matchAndPrint();
        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.end('Swift 데이터 수신 완료\n');
    } catch (error) {
        console.error('Swift 데이터 처리 오류:', error);
        res.writeHead(400, {'Content-Type': 'text/plain'});
        res.end('Invalid data format\n');
    }
}

function handleLidarData(body, res) {
    try {
        const data = JSON.parse(body);
        const logParts = data.message.split('\t');
        lidarData.push({
            timestamp: new Date().toISOString(),
            id: logParts[0].split(':')[1],
            x: -parseFloat(logParts[1].split(':')[1]),
            y: parseFloat(logParts[2].split(':')[1]),
            z: parseFloat(logParts[3].split(':')[1])
        });
        if (!lidarReady) {
            console.log('LiDAR 준비');
            lidarReady = true;
        }
        matchAndPrint();
        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.end('LiDAR 데이터 수신 완료\n');
    } catch (error) {
        console.error('LiDAR 데이터 처리 오류:', error);
        res.writeHead(400, {'Content-Type': 'text/plain'});
        res.end('Invalid data format\n');
    }
}

function logSwiftData(data) {
    const logEntry = `${new Date().toISOString()},${data.uniqueID},${data.deviceCoordinates.x},${data.deviceCoordinates.y},${data.deviceCoordinates.z}\n`;
    fs.appendFile('swift_log.csv', logEntry, (err) => {
        if (err) console.error('로그 파일 작성 오류:', err);
    });
}

function matchAndPrint() {
    if (swiftData.length > 0 && lidarData.length > 0) {
        const currentTime = Date.now();
        if (currentTime - lastPrintTime >= 100) { // 1초에 한 번만 출력
            lastPrintTime = currentTime;

            const latestSwiftData = swiftData[swiftData.length - 1];
            let closestLidarData = lidarData[0];
            let minDistance = Infinity;

            for (let lidarPoint of lidarData) {
                const distance = Math.sqrt(
                    Math.pow(latestSwiftData.x - lidarPoint.x, 2) +
                    Math.pow(latestSwiftData.z - lidarPoint.y, 2)
                );
                if (distance < minDistance) {
                    minDistance = distance;
                    closestLidarData = lidarPoint;
                }
            }

            const xDiff = Math.abs(latestSwiftData.x - closestLidarData.x);
            const zDiff = Math.abs(latestSwiftData.z - closestLidarData.y);
            const totalError = Math.sqrt(xDiff * xDiff + zDiff * zDiff);

            console.log(`매칭 결과 (${latestSwiftData.timestamp}):`);
            console.log('Swift 좌표:', latestSwiftData.x, latestSwiftData.z);
            console.log('LiDAR 좌표:', closestLidarData.x, closestLidarData.y);
            console.log('오차 (x, z):', xDiff, zDiff);
            console.log('총 거리 오차:', minDistance);

            if (totalError > 0.50) {
                console.log('불일치: 오차가 0.50을 초과했습니다.');
                mismatchCount++;
            } else {
                matchCount++;
            }

            console.log(`현재 스코어 - 일치: ${matchCount}, 불일치: ${mismatchCount}`);

            // 데이터 정리 (1분 이상 된 데이터 삭제)
            const oneMinuteAgo = Date.now() - 60000;
            swiftData = swiftData.filter(d => new Date(d.timestamp).getTime() > oneMinuteAgo);
            lidarData = lidarData.filter(d => new Date(d.timestamp).getTime() > oneMinuteAgo);
        }
    }
}

server.listen(port, hostname, () => {
    console.log(`서버가 http://${hostname}:${port}/에서 실행 중입니다.`);
});