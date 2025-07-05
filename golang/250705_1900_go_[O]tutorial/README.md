# 🚀 Go 언어 종합 학습 프로젝트

Go 언어의 모든 문법과 기능을 포함한 종합적인 학습 프로젝트입니다. 기본 문법부터 고급 기능, HTTP 통신, 실용적 예제까지 모든 것을 다룹니다.

## 📋 프로젝트 구조

```
250625_1215_go/
├── README.md                 # 프로젝트 설명 및 실행 가이드
├── go.mod                    # Go 모듈 설정
├── main.go                   # 메인 진입점
├── basics/                   # 기본 문법
│   ├── variables.go          # 변수, 타입, 상수, 변환
│   ├── functions.go          # 함수, 메서드, 가변인수
│   ├── control_flow.go       # 제어문 (if, for, switch)
│   ├── arrays_slices.go      # 배열과 슬라이스
│   ├── maps.go               # 맵 (해시맵)
│   └── structs.go            # 구조체, 임베딩, 포인터
├── advanced/                 # 고급 기능
│   ├── interfaces.go         # 인터페이스, 디자인 패턴
│   └── goroutines.go         # 고루틴, 채널, 동시성
├── http_server/              # HTTP 서버
│   └── server.go             # RESTful API 서버
├── http_client/              # HTTP 클라이언트
│   └── client.go             # API 클라이언트
├── examples/                 # 실용적 예제
│   └── todo_app.go           # TODO 앱 (대화형)
└── tests/                    # 테스트 코드
    └── basics_test.go        # 기본 문법 테스트
```

## 🎯 주요 특징

### ✅ **완전한 Go 문법 커버리지**
- 모든 기본 타입과 변수 선언
- 함수, 메서드, 가변인수
- 제어문 (if, for, switch, break/continue)
- 배열, 슬라이스, 맵
- 구조체, 임베딩, 포인터
- 인터페이스, 고루틴, 채널

### ✅ **실용적인 예제들**
- HTTP 서버/클라이언트
- TODO 앱 (대화형)
- 디자인 패턴 구현
- 동시성 패턴

### ✅ **한국어 주석과 설명**
- 모든 코드에 상세한 한국어 주석
- 개념 설명과 사용법 안내
- 실행 결과 예시

### ✅ **테스트 코드**
- 단위 테스트
- 벤치마크 테스트
- 테이블 주도 테스트

## 🚀 빠른 시작

### 1. 프로젝트 클론 및 설정

```bash
# 프로젝트 디렉토리로 이동
cd 250625_1215_go

# 의존성 설치
go mod tidy
```

### 2. 기본 실행

```bash
# 메뉴 보기
go run main.go

# 기본 문법 예제 실행
go run main.go basics

# 고급 기능 예제 실행
go run main.go advanced

# 모든 예제 실행
go run main.go all
```

## 📚 상세 사용법

### 기본 문법 (basics)

```bash
go run main.go basics
```

**포함 내용:**
- 변수 선언과 타입 (정수, 실수, 문자열, 불린)
- 타입 변환과 상수
- 함수 정의와 호출
- 메서드와 리시버
- 제어문 (if, for, switch)
- 배열과 슬라이스 조작
- 맵 사용법
- 구조체와 임베딩

### 고급 기능 (advanced)

```bash
go run main.go advanced
```

**포함 내용:**
- 인터페이스 정의와 구현
- 디자인 패턴 (Strategy, Factory, Observer, Adapter, Decorator)
- 고루틴과 동시성
- 채널과 동기화
- 고급 동시성 패턴 (Worker Pool, Pipeline, Fan-Out/Fan-In)

### HTTP 서버 (http-server)

```bash
# 서버 실행
go run http_server/server.go
```

**기능:**
- RESTful API 서버
- 사용자/게시글 CRUD
- 미들웨어 (로깅, CORS, 인증)
- 검색 기능
- 헬스 체크

**API 엔드포인트:**
- `GET /` - 홈 페이지
- `GET /health` - 헬스 체크
- `GET /api/users` - 사용자 목록
- `POST /api/users` - 사용자 생성
- `GET /api/users/{id}` - 사용자 조회
- `PUT /api/users/{id}` - 사용자 수정
- `DELETE /api/users/{id}` - 사용자 삭제
- `GET /api/search?q=검색어` - 검색

### HTTP 클라이언트 (http-client)

```bash
# 클라이언트 실행 (서버가 실행 중이어야 함)
go run http_client/client.go
```

**기능:**
- API 클라이언트
- 모든 CRUD 작업
- 배치 요청
- 에러 처리
- 재시도 기능

### 실용적 예제 (examples)

```bash
# TODO 앱 실행
go run examples/todo_app.go
```

**기능:**
- 대화형 TODO 앱
- 작업 추가/수정/삭제
- 우선순위 설정
- 카테고리 분류
- 검색 기능
- 통계 보기
- JSON 파일 저장/로드

### 테스트 (tests)

```bash
# 모든 테스트 실행
go test ./tests/...

# 벤치마크 테스트
go test -bench=. ./tests/...

# 테스트 커버리지
go test -cover ./tests/...
```

## 🔧 개별 파일 실행

각 파일을 독립적으로 실행할 수도 있습니다:

```bash
# 기본 문법 파일들
go run basics/variables.go
go run basics/functions.go
go run basics/control_flow.go
go run basics/arrays_slices.go
go run basics/maps.go
go run basics/structs.go

# 고급 기능 파일들
go run advanced/interfaces.go
go run advanced/goroutines.go

# HTTP 서버/클라이언트
go run http_server/server.go
go run http_client/client.go

# TODO 앱
go run examples/todo_app.go
```

## 🌐 HTTP 서버 테스트

서버가 실행된 후 다음과 같이 테스트할 수 있습니다:

```bash
# 홈 페이지 접근
curl http://localhost:8080/

# 사용자 목록 조회
curl http://localhost:8080/api/users

# 새 사용자 생성
curl -X POST http://localhost:8080/api/users \
  -H "Content-Type: application/json" \
  -d '{"name":"홍길동","email":"hong@example.com","age":30}'

# 특정 사용자 조회
curl http://localhost:8080/api/users/1

# 검색
curl http://localhost:8080/api/search?q=김철수
```

## 📖 학습 가이드

### 1단계: 기본 문법
```bash
go run main.go basics
```
- 변수, 함수, 제어문의 기본 개념 학습
- 배열, 슬라이스, 맵의 사용법 이해
- 구조체와 메서드의 개념 파악

### 2단계: 고급 기능
```bash
go run main.go advanced
```
- 인터페이스와 다형성 학습
- 고루틴과 동시성 프로그래밍 이해
- 디자인 패턴의 실제 구현 확인

### 3단계: 실용적 예제
```bash
# HTTP 서버 실행
go run http_server/server.go

# 새 터미널에서 클라이언트 실행
go run http_client/client.go

# TODO 앱 실행
go run examples/todo_app.go
```
- 실제 프로젝트에서 사용할 수 있는 패턴들 학습
- HTTP 통신의 실제 구현 확인
- 대화형 애플리케이션 개발 방법 이해

### 4단계: 테스트
```bash
go test ./tests/...
```
- 테스트 코드 작성 방법 학습
- 벤치마크 테스트로 성능 측정
- 테스트 커버리지 확인

## 🛠️ 개발 환경

- **Go 버전**: 1.21 이상
- **의존성**: gorilla/mux (HTTP 라우터)
- **운영체제**: 모든 플랫폼 지원

## 📝 주의사항

1. **HTTP 서버/클라이언트**: 서버를 먼저 실행한 후 클라이언트를 실행해야 합니다.
2. **TODO 앱**: 대화형 인터페이스이므로 터미널에서 직접 실행해야 합니다.
3. **테스트**: 일부 테스트는 독립적으로 실행할 수 있습니다.

## 🤝 기여하기

이 프로젝트는 학습 목적으로 만들어졌습니다. 개선사항이나 버그 리포트는 언제든 환영합니다!

## 📄 라이선스

이 프로젝트는 MIT 라이선스 하에 배포됩니다.

---

**🎉 Go 언어의 모든 것을 한 곳에서 학습하세요!** 