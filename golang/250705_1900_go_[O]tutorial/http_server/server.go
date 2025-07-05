package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"strconv"
	"strings"
	"syscall"
	"time"

	"github.com/gorilla/mux"
)

// ===== 기본 데이터 구조 =====

// User - 사용자 정보
type User struct {
	ID       int    `json:"id"`
	Name     string `json:"name"`
	Email    string `json:"email"`
	Age      int    `json:"age"`
	Created  string `json:"created"`
}

// Post - 게시글 정보
type Post struct {
	ID      int    `json:"id"`
	Title   string `json:"title"`
	Content string `json:"content"`
	Author  string `json:"author"`
	Created string `json:"created"`
}

// Response - API 응답 구조
type Response struct {
	Success bool        `json:"success"`
	Message string      `json:"message"`
	Data    interface{} `json:"data,omitempty"`
	Error   string      `json:"error,omitempty"`
}

// ===== 인메모리 데이터베이스 =====

var (
	users = []User{
		{ID: 1, Name: "김철수", Email: "kim@example.com", Age: 25, Created: "2024-01-01"},
		{ID: 2, Name: "이영희", Email: "lee@example.com", Age: 30, Created: "2024-01-02"},
		{ID: 3, Name: "박민수", Email: "park@example.com", Age: 28, Created: "2024-01-03"},
	}
	
	posts = []Post{
		{ID: 1, Title: "첫 번째 게시글", Content: "안녕하세요!", Author: "김철수", Created: "2024-01-01"},
		{ID: 2, Title: "두 번째 게시글", Content: "반갑습니다!", Author: "이영희", Created: "2024-01-02"},
		{ID: 3, Title: "세 번째 게시글", Content: "좋은 하루 되세요!", Author: "박민수", Created: "2024-01-03"},
	}
	
	userCounter = 4
	postCounter = 4
)

// ===== 미들웨어 =====

// LoggingMiddleware - 요청 로깅 미들웨어
func LoggingMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		start := time.Now()
		
		// 요청 로깅
		log.Printf("요청: %s %s - %s", r.Method, r.URL.Path, r.RemoteAddr)
		
		// 다음 핸들러 호출
		next.ServeHTTP(w, r)
		
		// 응답 시간 로깅
		duration := time.Since(start)
		log.Printf("응답: %s %s - %v", r.Method, r.URL.Path, duration)
	})
}

// CORSMiddleware - CORS 설정 미들웨어
func CORSMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type, Authorization")
		
		if r.Method == "OPTIONS" {
			w.WriteHeader(http.StatusOK)
			return
		}
		
		next.ServeHTTP(w, r)
	})
}

// AuthMiddleware - 인증 미들웨어 (간단한 예제)
func AuthMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		authHeader := r.Header.Get("Authorization")
		
		if authHeader == "" {
			respondWithError(w, "인증 헤더가 필요합니다", http.StatusUnauthorized)
			return
		}
		
		if !strings.HasPrefix(authHeader, "Bearer ") {
			respondWithError(w, "잘못된 인증 형식입니다", http.StatusUnauthorized)
			return
		}
		
		// 실제로는 토큰 검증 로직이 들어갑니다
		token := strings.TrimPrefix(authHeader, "Bearer ")
		if token != "valid-token" {
			respondWithError(w, "유효하지 않은 토큰입니다", http.StatusUnauthorized)
			return
		}
		
		next.ServeHTTP(w, r)
	})
}

// RateLimitMiddleware - 속도 제한 미들웨어
func RateLimitMiddleware(next http.Handler) http.Handler {
	clients := make(map[string]time.Time)
	
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		clientIP := r.RemoteAddr
		
		if lastRequest, exists := clients[clientIP]; exists {
			if time.Since(lastRequest) < time.Second {
				respondWithError(w, "너무 빠른 요청입니다", http.StatusTooManyRequests)
				return
			}
		}
		
		clients[clientIP] = time.Now()
		next.ServeHTTP(w, r)
	})
}

// ===== 헬퍼 함수들 =====

// respondWithJSON - JSON 응답 전송
func respondWithJSON(w http.ResponseWriter, code int, payload interface{}) {
	response, _ := json.Marshal(payload)
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(code)
	w.Write(response)
}

// respondWithError - 에러 응답 전송
func respondWithError(w http.ResponseWriter, message string, code int) {
	response := Response{
		Success: false,
		Error:   message,
	}
	respondWithJSON(w, code, response)
}

// respondWithSuccess - 성공 응답 전송
func respondWithSuccess(w http.ResponseWriter, message string, data interface{}) {
	response := Response{
		Success: true,
		Message: message,
		Data:    data,
	}
	respondWithJSON(w, http.StatusOK, response)
}

// ===== 핸들러 함수들 =====

// HomeHandler - 홈 페이지
func HomeHandler(w http.ResponseWriter, r *http.Request) {
	response := Response{
		Success: true,
		Message: "Go HTTP 서버에 오신 것을 환영합니다!",
		Data: map[string]interface{}{
			"version": "1.0.0",
			"endpoints": []string{
				"GET /api/users",
				"GET /api/users/{id}",
				"POST /api/users",
				"PUT /api/users/{id}",
				"DELETE /api/users/{id}",
				"GET /api/posts",
				"GET /api/posts/{id}",
				"POST /api/posts",
				"PUT /api/posts/{id}",
				"DELETE /api/posts/{id}",
			},
		},
	}
	respondWithJSON(w, http.StatusOK, response)
}

// GetUsersHandler - 모든 사용자 조회
func GetUsersHandler(w http.ResponseWriter, r *http.Request) {
	respondWithSuccess(w, "사용자 목록 조회 성공", users)
}

// GetUserHandler - 특정 사용자 조회
func GetUserHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 사용자 ID", http.StatusBadRequest)
		return
	}
	
	for _, user := range users {
		if user.ID == id {
			respondWithSuccess(w, "사용자 조회 성공", user)
			return
		}
	}
	
	respondWithError(w, "사용자를 찾을 수 없습니다", http.StatusNotFound)
}

// CreateUserHandler - 사용자 생성
func CreateUserHandler(w http.ResponseWriter, r *http.Request) {
	var newUser User
	if err := json.NewDecoder(r.Body).Decode(&newUser); err != nil {
		respondWithError(w, "잘못된 요청 데이터", http.StatusBadRequest)
		return
	}
	
	// 필수 필드 검증
	if newUser.Name == "" || newUser.Email == "" {
		respondWithError(w, "이름과 이메일은 필수입니다", http.StatusBadRequest)
		return
	}
	
	// 이메일 중복 검사
	for _, user := range users {
		if user.Email == newUser.Email {
			respondWithError(w, "이미 존재하는 이메일입니다", http.StatusConflict)
			return
		}
	}
	
	// 새 사용자 생성
	newUser.ID = userCounter
	newUser.Created = time.Now().Format("2006-01-02")
	users = append(users, newUser)
	userCounter++
	
	respondWithSuccess(w, "사용자 생성 성공", newUser)
}

// UpdateUserHandler - 사용자 수정
func UpdateUserHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 사용자 ID", http.StatusBadRequest)
		return
	}
	
	var updateUser User
	if err := json.NewDecoder(r.Body).Decode(&updateUser); err != nil {
		respondWithError(w, "잘못된 요청 데이터", http.StatusBadRequest)
		return
	}
	
	// 사용자 찾기 및 수정
	for i, user := range users {
		if user.ID == id {
			updateUser.ID = id
			updateUser.Created = user.Created // 생성일은 유지
			users[i] = updateUser
			respondWithSuccess(w, "사용자 수정 성공", updateUser)
			return
		}
	}
	
	respondWithError(w, "사용자를 찾을 수 없습니다", http.StatusNotFound)
}

// DeleteUserHandler - 사용자 삭제
func DeleteUserHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 사용자 ID", http.StatusBadRequest)
		return
	}
	
	// 사용자 찾기 및 삭제
	for i, user := range users {
		if user.ID == id {
			users = append(users[:i], users[i+1:]...)
			respondWithSuccess(w, "사용자 삭제 성공", nil)
			return
		}
	}
	
	respondWithError(w, "사용자를 찾을 수 없습니다", http.StatusNotFound)
}

// GetPostsHandler - 모든 게시글 조회
func GetPostsHandler(w http.ResponseWriter, r *http.Request) {
	respondWithSuccess(w, "게시글 목록 조회 성공", posts)
}

// GetPostHandler - 특정 게시글 조회
func GetPostHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 게시글 ID", http.StatusBadRequest)
		return
	}
	
	for _, post := range posts {
		if post.ID == id {
			respondWithSuccess(w, "게시글 조회 성공", post)
			return
		}
	}
	
	respondWithError(w, "게시글을 찾을 수 없습니다", http.StatusNotFound)
}

// CreatePostHandler - 게시글 생성
func CreatePostHandler(w http.ResponseWriter, r *http.Request) {
	var newPost Post
	if err := json.NewDecoder(r.Body).Decode(&newPost); err != nil {
		respondWithError(w, "잘못된 요청 데이터", http.StatusBadRequest)
		return
	}
	
	// 필수 필드 검증
	if newPost.Title == "" || newPost.Content == "" || newPost.Author == "" {
		respondWithError(w, "제목, 내용, 작성자는 필수입니다", http.StatusBadRequest)
		return
	}
	
	// 새 게시글 생성
	newPost.ID = postCounter
	newPost.Created = time.Now().Format("2006-01-02")
	posts = append(posts, newPost)
	postCounter++
	
	respondWithSuccess(w, "게시글 생성 성공", newPost)
}

// UpdatePostHandler - 게시글 수정
func UpdatePostHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 게시글 ID", http.StatusBadRequest)
		return
	}
	
	var updatePost Post
	if err := json.NewDecoder(r.Body).Decode(&updatePost); err != nil {
		respondWithError(w, "잘못된 요청 데이터", http.StatusBadRequest)
		return
	}
	
	// 게시글 찾기 및 수정
	for i, post := range posts {
		if post.ID == id {
			updatePost.ID = id
			updatePost.Created = post.Created // 생성일은 유지
			posts[i] = updatePost
			respondWithSuccess(w, "게시글 수정 성공", updatePost)
			return
		}
	}
	
	respondWithError(w, "게시글을 찾을 수 없습니다", http.StatusNotFound)
}

// DeletePostHandler - 게시글 삭제
func DeletePostHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.Atoi(vars["id"])
	if err != nil {
		respondWithError(w, "잘못된 게시글 ID", http.StatusBadRequest)
		return
	}
	
	// 게시글 찾기 및 삭제
	for i, post := range posts {
		if post.ID == id {
			posts = append(posts[:i], posts[i+1:]...)
			respondWithSuccess(w, "게시글 삭제 성공", nil)
			return
		}
	}
	
	respondWithError(w, "게시글을 찾을 수 없습니다", http.StatusNotFound)
}

// SearchHandler - 검색 기능
func SearchHandler(w http.ResponseWriter, r *http.Request) {
	query := r.URL.Query().Get("q")
	if query == "" {
		respondWithError(w, "검색어가 필요합니다", http.StatusBadRequest)
		return
	}
	
	// 사용자 검색
	var matchedUsers []User
	for _, user := range users {
		if strings.Contains(strings.ToLower(user.Name), strings.ToLower(query)) ||
		   strings.Contains(strings.ToLower(user.Email), strings.ToLower(query)) {
			matchedUsers = append(matchedUsers, user)
		}
	}
	
	// 게시글 검색
	var matchedPosts []Post
	for _, post := range posts {
		if strings.Contains(strings.ToLower(post.Title), strings.ToLower(query)) ||
		   strings.Contains(strings.ToLower(post.Content), strings.ToLower(query)) ||
		   strings.Contains(strings.ToLower(post.Author), strings.ToLower(query)) {
			matchedPosts = append(matchedPosts, post)
		}
	}
	
	result := map[string]interface{}{
		"users": matchedUsers,
		"posts": matchedPosts,
		"query": query,
	}
	
	respondWithSuccess(w, "검색 완료", result)
}

// HealthCheckHandler - 헬스 체크
func HealthCheckHandler(w http.ResponseWriter, r *http.Request) {
	response := Response{
		Success: true,
		Message: "서버가 정상 작동 중입니다",
		Data: map[string]interface{}{
			"status":    "healthy",
			"timestamp": time.Now().Format(time.RFC3339),
			"uptime":    "서버 시작 시간 정보",
		},
	}
	respondWithJSON(w, http.StatusOK, response)
}

// ===== 서버 설정 및 실행 =====

// setupRoutes - 라우터 설정
func setupRoutes() *mux.Router {
	r := mux.NewRouter()
	
	// 미들웨어 적용
	r.Use(LoggingMiddleware)
	r.Use(CORSMiddleware)
	
	// 기본 라우트
	r.HandleFunc("/", HomeHandler).Methods("GET")
	r.HandleFunc("/health", HealthCheckHandler).Methods("GET")
	
	// API 라우트
	api := r.PathPrefix("/api").Subrouter()
	
	// 사용자 관련 라우트
	api.HandleFunc("/users", GetUsersHandler).Methods("GET")
	api.HandleFunc("/users", CreateUserHandler).Methods("POST")
	api.HandleFunc("/users/{id}", GetUserHandler).Methods("GET")
	api.HandleFunc("/users/{id}", UpdateUserHandler).Methods("PUT")
	api.HandleFunc("/users/{id}", DeleteUserHandler).Methods("DELETE")
	
	// 게시글 관련 라우트
	api.HandleFunc("/posts", GetPostsHandler).Methods("GET")
	api.HandleFunc("/posts", CreatePostHandler).Methods("POST")
	api.HandleFunc("/posts/{id}", GetPostHandler).Methods("GET")
	api.HandleFunc("/posts/{id}", UpdatePostHandler).Methods("PUT")
	api.HandleFunc("/posts/{id}", DeletePostHandler).Methods("DELETE")
	
	// 검색 라우트
	api.HandleFunc("/search", SearchHandler).Methods("GET")
	
	// 인증이 필요한 라우트 (예제)
	protected := api.PathPrefix("/protected").Subrouter()
	protected.Use(AuthMiddleware)
	protected.HandleFunc("/users", GetUsersHandler).Methods("GET")
	
	return r
}

// RunServer - 서버 실행
func RunServer() {
	router := setupRoutes()
	
	// 서버 설정
	srv := &http.Server{
		Addr:         ":8080",
		Handler:      router,
		ReadTimeout:  15 * time.Second,
		WriteTimeout: 15 * time.Second,
		IdleTimeout:  60 * time.Second,
	}
	
	fmt.Println("🚀 Go HTTP 서버가 시작되었습니다!")
	fmt.Println("📍 서버 주소: http://localhost:8080")
	fmt.Println("📚 API 문서:")
	fmt.Println("   GET  /                    - 홈 페이지")
	fmt.Println("   GET  /health              - 헬스 체크")
	fmt.Println("   GET  /api/users           - 사용자 목록")
	fmt.Println("   POST /api/users           - 사용자 생성")
	fmt.Println("   GET  /api/users/{id}      - 사용자 조회")
	fmt.Println("   PUT  /api/users/{id}      - 사용자 수정")
	fmt.Println("   DELETE /api/users/{id}    - 사용자 삭제")
	fmt.Println("   GET  /api/posts           - 게시글 목록")
	fmt.Println("   POST /api/posts           - 게시글 생성")
	fmt.Println("   GET  /api/posts/{id}      - 게시글 조회")
	fmt.Println("   PUT  /api/posts/{id}      - 게시글 수정")
	fmt.Println("   DELETE /api/posts/{id}    - 게시글 삭제")
	fmt.Println("   GET  /api/search?q=검색어  - 검색")
	fmt.Println("")
	fmt.Println("💡 테스트 예제:")
	fmt.Println("   curl http://localhost:8080/")
	fmt.Println("   curl http://localhost:8080/api/users")
	fmt.Println("   curl -X POST http://localhost:8080/api/users -H 'Content-Type: application/json' -d '{\"name\":\"홍길동\",\"email\":\"hong@example.com\",\"age\":30}'")
	fmt.Println("")
	
	// 서버 시작
	if err := srv.ListenAndServe(); err != nil {
		log.Fatal("서버 시작 실패:", err)
	}
}

// GracefulShutdown - 우아한 종료
func GracefulShutdown(srv *http.Server) {
	// 종료 신호 대기
	quit := make(chan os.Signal, 1)
	signal.Notify(quit, syscall.SIGINT, syscall.SIGTERM)
	<-quit
	
	fmt.Println("\n🛑 서버 종료 중...")
	
	// 30초 타임아웃으로 우아한 종료
	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()
	
	if err := srv.Shutdown(ctx); err != nil {
		log.Fatal("서버 강제 종료:", err)
	}
	
	fmt.Println("✅ 서버가 안전하게 종료되었습니다.")
}

func main() {
	RunServer()
} 