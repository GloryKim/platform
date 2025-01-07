// Copyright (C) 2024 GloryKim (glory@keti.re.kr)

/*

SQLite는 C로 작성된 오픈 소스 임베디드 관계형 데이터베이스 관리 시스템(RDBMS).
- 서버가 필요 없는 파일 기반의 데이터베이스로, 모든 데이터가 단일 파일에 저장.
- 주로 소형 애플리케이션, 모바일 애플리케이션, 데스크탑 소프트웨어 등에 사용됨.
- ACID(원자성, 일관성, 고립성, 내구성) 속성을 지원.
- SQL 표준을 준수하며, 복잡한 쿼리도 처리 가능.
- 외부 라이브러리 없이 사용 가능하여 배포와 유지 관리가 간편.

[주요 특징]
- 경량화된 구조로 매우 작은 메모리 및 디스크 공간 사용.
- 단일 데이터베이스 파일을 사용하여 손쉬운 배포 가능.
- 트랜잭션을 지원하여 데이터 무결성 유지.
- 풍부한 데이터 타입 지원(정수, 실수, 텍스트, BLOB 등).
- 외부 종속성이 없으며 크로스 플랫폼 지원.

[요약]
sqlite3: Node.js에서 SQLite 데이터베이스에 연결하기 위한 패키지.
Database: SQLite 데이터베이스를 열거나 생성하는 메서드.
CREATE TABLE: users라는 이름의 테이블을 생성.
INSERT INTO: 데이터 삽입을 위해 준비된 문(statement)을 실행.
db.each: 테이블에서 데이터를 조회하고 각 행을 출력.
db.close: 데이터베이스 연결을 종료.
*/


/*
JavaScript로 SQLite 구현 예제
SQLite는 서버가 필요 없는 데이터베이스이기 때문에, Node.js 환경에서 이를 쉽게 구현할 수 있음. sqlite3 패키지를 사용하여 SQLite 데이터베이스에 접근 가능.
*/

const sqlite3 = require('sqlite3').verbose();

// 데이터베이스 연결 (test.db 파일이 없으면 생성됨)
const db = new sqlite3.Database('test.db');

// 테이블 생성
db.serialize(() => {
    db.run("CREATE TABLE IF NOT EXISTS users (id INT, name TEXT)");

    // 데이터 삽입
    const stmt = db.prepare("INSERT INTO users VALUES (?, ?)");
    stmt.run(1, "김영광");
    stmt.run(2, "김광영");
    stmt.finalize();

    // 데이터 조회
    db.each("SELECT id, name FROM users", (err, row) => {
        if (err) {
            console.error(err.message);
        } else {
            console.log(`User ID: ${row.id}, Name: ${row.name}`);
        }
    });
});

// 데이터베이스 연결 종료
db.close((err) => {
    if (err) {
        console.error(err.message);
    } else {
        console.log('Database connection closed.');
    }
});



/*
터미널 결과
mac@macui-MacBookPro platform % cd 240821_1658_SQLlite+node 
mac@macui-MacBookPro 240821_1658_SQLlite+node % npm install sqlite3

npm WARN deprecated inflight@1.0.6: This module is not supported, and leaks memory. Do not use it. Check out lru-cache if you want a good and tested way to coalesce async requests by a key value, which is much more comprehensive and powerful.
npm WARN deprecated rimraf@3.0.2: Rimraf versions prior to v4 are no longer supported
npm WARN deprecated glob@7.2.3: Glob versions prior to v9 are no longer supported
npm WARN deprecated gauge@4.0.4: This package is no longer supported.
npm WARN deprecated are-we-there-yet@3.0.1: This package is no longer supported.
npm WARN deprecated @npmcli/move-file@1.1.2: This functionality has been moved to @npmcli/fs
npm WARN deprecated npmlog@6.0.2: This package is no longer supported.

added 123 packages in 6s

12 packages are looking for funding
  run `npm fund` for details
mac@macui-MacBookPro 240821_1658_SQLlite+node % node main.js 
User ID: 1, Name: Alice
User ID: 2, Name: Bob
Database connection closed.
mac@macui-MacBookPro 240821_1658_SQLlite+node % node main.js
User ID: 1, Name: Alice
User ID: 2, Name: Bob
User ID: 1, Name: Alice
User ID: 2, Name: Bob
Database connection closed.
mac@macui-MacBookPro 240821_1658_SQLlite+node % node main.js
User ID: 1, Name: Alice
User ID: 2, Name: Bob
User ID: 1, Name: Alice
User ID: 2, Name: Bob
User ID: 1, Name: 김영광
User ID: 2, Name: 김광영
Database connection closed.
mac@macui-MacBookPro 240821_1658_SQLlite+node %
*/