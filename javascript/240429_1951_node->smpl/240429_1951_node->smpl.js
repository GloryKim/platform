const express = require('express');
const http = require('http');
const socketIO = require('socket.io');

const multer = require('multer');

const app = express();
const server = http.createServer(app);
const io = socketIO(server);

const fs = require('fs-extra');
const path = require('path');
const axios = require('axios');

const FormData = require('form-data');


app.use(express.static('public')); // 정적 파일 제공을 위한 폴더 설정
// JSON 요청 본문을 파싱하기 위한 미들웨어 추가
app.use(express.json());

function generateRandomString(length) {
    const characters = 'ABykloCDEz06789'; //240429_1953_glory : 랜덤한 문자열
    let result = '';
    for (let i = 0; i < length; i++) {
        result += characters.charAt(Math.floor(Math.random() * characters.length));
    }
    return result;
}

io.on('connection', (socket) => {
    console.log('New client connected');
    const sessionId = generateRandomString(40);
    const sessionPath = path.join(__dirname, 'images', sessionId);
    fs.ensureDirSync(sessionPath);
    let imagePaths = [];

    socket.on('image-capture', async (data) => {
        const base64Data = data.replace(/^data:image\/png;base64,/, "");
        const filePath = path.join(sessionPath, `image_${sessionId}_${imagePaths.length + 1}.png`);

        await fs.writeFile(filePath, base64Data, 'base64');
        console.log('Image saved to', filePath);
        imagePaths.push(filePath);

        if (imagePaths.length === 4) {
            const formData = new FormData();
            imagePaths.forEach(imagePath => {
                formData.append('images', fs.createReadStream(imagePath));
            });
            formData.append('folderName', sessionId);

            axios.post('http://localhost:1249/upload', formData, {
                headers: {
                    ...formData.getHeaders()
                }
            })
            .then(response => console.log('Images and folder name sent to server:', response.status))
            .catch(error => console.log('Failed to send images and folder name:', error));
        }
    });

    socket.on('disconnect', () => {
        console.log('Client disconnected');
    });
});


// 파일 저장을 위한 multer 설정
const storage = multer.diskStorage({
    destination: function (req, file, cb) {
        const folderName = req.body.folder_name;
        const dir = path.join(__dirname, 'download', folderName);
        fs.ensureDirSync(dir);  // 폴더가 없으면 생성
        cb(null, dir);
    },
    filename: function (req, file, cb) {
        cb(null, file.originalname);
    }
});

const upload = multer({ storage: storage });

// 동적으로 파일 필드 이름을 처리하도록 수정
app.post('/receive-images-glory', upload.fields([{ name: 'image_1' }, { name: 'image_2' }, { name: 'image_3' }, { name: 'image_4' }]), (req, res) => {
    if (!req.files) {
        return res.status(400).send('No files were uploaded.');
    }
    const folderName = req.body.folder_name;
    console.log(`Received images for folder: ${folderName}`);
    res.status(200).send('Images received successfully.');
});



const PORT = process.env.PORT || 1000;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});