// Copyright (C) 2024 GloryKim (glory@keti.re.kr)



const express = require('express');
const path = require('path');
const app = express();

// 클라이언트 측에서 사용할 HTML 파일 제공
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});


// 서버 시작
const PORT = process.env.PORT || 3001;
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});



/*
Web Storage API 개요
- Web Storage API는 웹 브라우저에서 데이터를 클라이언트 측에 로컬로 저장할 수 있는 방법을 제공하는 API.

두 가지 주요 메커니즘: localStorage와 sessionStorage.
- 브라우저 탭 간에 데이터를 유지하거나 탭이 닫힐 때까지 데이터를 저장하는 용도로 사용됨.

주요 특징
1. localStorage:
- 영구 저장소로, 데이터를 명시적으로 삭제하지 않는 한 브라우저를 닫아도 유지됨.
- 데이터 저장은 도메인 단위로 이루어지며, 동일한 도메인에서는 모든 탭과 창에서 접근 가능.
- 데이터 용량: 약 5~10MB.

2. sessionStorage:
- 세션 기반 저장소로, 데이터를 브라우저 탭을 닫을 때까지 유지.
- 데이터는 각 브라우저 탭마다 별도로 저장되며, 같은 페이지라도 탭이 다르면 접근 불가.
- 데이터 용량: 일반적으로 localStorage와 동일하지만, 각 브라우저에 따라 다를 수 있음.
*/



/*
로컬 스토리지 (localStorage)
- 클라이언트 측 저장소
- 브라우저에서 제공하는 도메인 단위 데이터 저장
- 데이터는 명시적으로 삭제 전까지 영구적으로 유지
- 용량: 5~10MB
- 자바스크립트를 통해 접근 가능, 서버로 전송되지 않음
- 보안: 자바스크립트로 접근 가능하므로 민감한 데이터 저장에 주의
- 요약: 클라이언트 측에서 대량의 데이터를 저장하고, 서버로 전송할 필요가 없을 때 사용

쿠키 (Cookie)
- 클라이언트 측의 작은 데이터 저장 방법
- 세션 관리, 사용자 식별 등 서버와 클라이언트 간 데이터 전송에 사용
- 설정된 만료 시간에 따라 수명 결정 (세션 쿠키는 브라우저 종료 시 삭제)
- 용량: 약 4KB
- 자바스크립트와 서버 모두 접근 가능, HTTP 요청 시마다 서버로 자동 전송
- 보안: HttpOnly, Secure 속성으로 보안 강화 가능
- 요약: 서버와 클라이언트 간의 작은 데이터를 전송하거나, 세션 관리 및 사용자 인증 정보를 저장할 때 사용
*/



/*
#초기 세팅
mac@macui-MacBookPro platform % cd 240821_1732_webstorageAPI 
mac@macui-MacBookPro 240821_1732_webstorageAPI % npm init -y
Wrote to /Users/mac/github/platform/240821_1732_webstorageAPI/package.json:

{
  "name": "240821_1732_webstorageapi",
  "version": "1.0.0",
  "description": "",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "keywords": [],
  "author": "",
  "license": "ISC"
}


mac@macui-MacBookPro 240821_1732_webstorageAPI % npm install express


added 64 packages, and audited 65 packages in 1s

12 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities
mac@macui-MacBookPro 240821_1732_webstorageAPI % node main.js
Server is running on http://localhost:3001

*/



/*
HTML 코드

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Storage API Example</title>
</head>
<body>
    <h1>Web Storage API Example</h1>

    <!-- Local Storage 관련 버튼 -->
    <h2>Local Storage</h2>
    <button id="saveLocal">Save to localStorage</button>
    <button id="loadLocal">Load from localStorage</button>
    <button id="clearLocal">Clear localStorage</button>
    <p id="outputLocal"></p>

    <!-- Session Storage 관련 버튼 -->
    <h2>Session Storage</h2>
    <button id="saveSession">Save to sessionStorage</button>
    <button id="loadSession">Load from sessionStorage</button>
    <button id="clearSession">Clear sessionStorage</button>
    <p id="outputSession"></p>

    <script>
        // Proxy를 사용해 localStorage와 sessionStorage의 접근 및 변화를 감시하는 객체
        const storageHandler = {
            get(target, prop) {
                // 메서드가 호출될 때(예: getItem, setItem), prop을 체크
                if (typeof target[prop] === 'function') {
                    return function(...args) {
                        console.log(`Calling ${prop} with args:`, args);
                        return target[prop].apply(target, args);
                    };
                }
                // 메서드가 아닌 프로퍼티 접근은 그대로 반환
                return target[prop];
            },
            set(target, prop, value) {
                // 일반적인 프로퍼티 세팅은 그대로 진행
                console.log(`Setting key "${prop}" to`, value);
                target[prop] = value;
                return true;
            },
            deleteProperty(target, prop) {
                // 프로퍼티 삭제 처리
                console.log(`Deleting key "${prop}"`);
                delete target[prop];
                return true;
            }
        };

        // localStorage와 sessionStorage에 Proxy를 적용
        const localStorageProxy = new Proxy(localStorage, storageHandler);
        const sessionStorageProxy = new Proxy(sessionStorage, storageHandler);

        // Local Storage 버튼 이벤트 처리
        document.getElementById('saveLocal').addEventListener('click', () => {
            // 'username'이라는 키로 값을 저장
            localStorageProxy.setItem('username', 'GloryKim');
            document.getElementById('outputLocal').textContent = 'Saved to localStorage: GloryKim';
        });

        document.getElementById('loadLocal').addEventListener('click', () => {
            // 'username' 키의 값을 가져옴
            const data = localStorageProxy.getItem('username');
            if (data) {
                document.getElementById('outputLocal').textContent = `Loaded from localStorage: ${data}`;
            } else {
                document.getElementById('outputLocal').textContent = 'No data found in localStorage';
            }
        });

        document.getElementById('clearLocal').addEventListener('click', () => {
            // 'username' 키의 값을 삭제
            localStorageProxy.removeItem('username');
            document.getElementById('outputLocal').textContent = 'Cleared from localStorage';
        });

        // Session Storage 버튼 이벤트 처리
        document.getElementById('saveSession').addEventListener('click', () => {
            // 'sessionKey'라는 키로 값을 저장
            sessionStorageProxy.setItem('sessionKey', '12345');
            document.getElementById('outputSession').textContent = 'Saved to sessionStorage: 12345';
        });

        document.getElementById('loadSession').addEventListener('click', () => {
            // 'sessionKey' 키의 값을 가져옴
            const data = sessionStorageProxy.getItem('sessionKey');
            if (data) {
                document.getElementById('outputSession').textContent = `Loaded from sessionStorage: ${data}`;
            } else {
                document.getElementById('outputSession').textContent = 'No data found in sessionStorage';
            }
        });

        document.getElementById('clearSession').addEventListener('click', () => {
            // 'sessionKey' 키의 값을 삭제
            sessionStorageProxy.removeItem('sessionKey');
            document.getElementById('outputSession').textContent = 'Cleared from sessionStorage';
        });
    </script>
</body>
</html>

*/
