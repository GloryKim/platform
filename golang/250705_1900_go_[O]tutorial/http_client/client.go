package main

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"strings"
	"time"
)

// ===== 기본 데이터 구조 =====

// User - 사용자 정보
type User struct {
	ID      int    `json:"id"`
	Name    string `json:"name"`
	Email   string `json:"email"`
	Age     int    `json:"age"`
	Created string `json:"created"`
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

// ===== HTTP 클라이언트 구조체 =====

// APIClient - API 클라이언트
type APIClient struct {
	BaseURL    string
	HTTPClient *http.Client
	Headers    map[string]string
}

// NewAPIClient - 새로운 API 클라이언트 생성
func NewAPIClient(baseURL string) *APIClient {
	return &APIClient{
		BaseURL: baseURL,
		HTTPClient: &http.Client{
			Timeout: 30 * time.Second,
		},
		Headers: map[string]string{
			"Content-Type": "application/json",
			"User-Agent":   "Go-HTTP-Client/1.0",
		},
	}
}

// SetHeader - 헤더 설정
func (c *APIClient) SetHeader(key, value string) {
	c.Headers[key] = value
}

// SetAuthToken - 인증 토큰 설정
func (c *APIClient) SetAuthToken(token string) {
	c.SetHeader("Authorization", "Bearer "+token)
}

// ===== 기본 HTTP 메서드들 =====

// doRequest - HTTP 요청 실행
func (c *APIClient) doRequest(method, endpoint string, body io.Reader) (*http.Response, error) {
	// URL 생성
	url := c.BaseURL + endpoint
	
	// 요청 생성
	req, err := http.NewRequest(method, url, body)
	if err != nil {
		return nil, fmt.Errorf("요청 생성 실패: %v", err)
	}
	
	// 헤더 설정
	for key, value := range c.Headers {
		req.Header.Set(key, value)
	}
	
	// 요청 실행
	resp, err := c.HTTPClient.Do(req)
	if err != nil {
		return nil, fmt.Errorf("요청 실행 실패: %v", err)
	}
	
	return resp, nil
}

// GET - GET 요청
func (c *APIClient) GET(endpoint string) (*http.Response, error) {
	return c.doRequest("GET", endpoint, nil)
}

// POST - POST 요청
func (c *APIClient) POST(endpoint string, data interface{}) (*http.Response, error) {
	jsonData, err := json.Marshal(data)
	if err != nil {
		return nil, fmt.Errorf("JSON 마샬링 실패: %v", err)
	}
	
	return c.doRequest("POST", endpoint, bytes.NewBuffer(jsonData))
}

// PUT - PUT 요청
func (c *APIClient) PUT(endpoint string, data interface{}) (*http.Response, error) {
	jsonData, err := json.Marshal(data)
	if err != nil {
		return nil, fmt.Errorf("JSON 마샬링 실패: %v", err)
	}
	
	return c.doRequest("PUT", endpoint, bytes.NewBuffer(jsonData))
}

// DELETE - DELETE 요청
func (c *APIClient) DELETE(endpoint string) (*http.Response, error) {
	return c.doRequest("DELETE", endpoint, nil)
}

// ===== 응답 처리 헬퍼 =====

// parseResponse - 응답 파싱
func (c *APIClient) parseResponse(resp *http.Response, target interface{}) error {
	defer resp.Body.Close()
	
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return fmt.Errorf("응답 읽기 실패: %v", err)
	}
	
	if resp.StatusCode >= 400 {
		return fmt.Errorf("HTTP 에러 %d: %s", resp.StatusCode, string(body))
	}
	
	if target != nil {
		if err := json.Unmarshal(body, target); err != nil {
			return fmt.Errorf("JSON 언마샬링 실패: %v", err)
		}
	}
	
	return nil
}

// ===== 사용자 API 메서드들 =====

// GetUsers - 모든 사용자 조회
func (c *APIClient) GetUsers() ([]User, error) {
	resp, err := c.GET("/api/users")
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var users []User
	if err := json.Unmarshal(jsonData, &users); err != nil {
		return nil, fmt.Errorf("사용자 데이터 파싱 실패: %v", err)
	}
	
	return users, nil
}

// GetUser - 특정 사용자 조회
func (c *APIClient) GetUser(id int) (*User, error) {
	endpoint := fmt.Sprintf("/api/users/%d", id)
	resp, err := c.GET(endpoint)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var user User
	if err := json.Unmarshal(jsonData, &user); err != nil {
		return nil, fmt.Errorf("사용자 데이터 파싱 실패: %v", err)
	}
	
	return &user, nil
}

// CreateUser - 사용자 생성
func (c *APIClient) CreateUser(user User) (*User, error) {
	resp, err := c.POST("/api/users", user)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var createdUser User
	if err := json.Unmarshal(jsonData, &createdUser); err != nil {
		return nil, fmt.Errorf("사용자 데이터 파싱 실패: %v", err)
	}
	
	return &createdUser, nil
}

// UpdateUser - 사용자 수정
func (c *APIClient) UpdateUser(id int, user User) (*User, error) {
	endpoint := fmt.Sprintf("/api/users/%d", id)
	resp, err := c.PUT(endpoint, user)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var updatedUser User
	if err := json.Unmarshal(jsonData, &updatedUser); err != nil {
		return nil, fmt.Errorf("사용자 데이터 파싱 실패: %v", err)
	}
	
	return &updatedUser, nil
}

// DeleteUser - 사용자 삭제
func (c *APIClient) DeleteUser(id int) error {
	endpoint := fmt.Sprintf("/api/users/%d", id)
	resp, err := c.DELETE(endpoint)
	if err != nil {
		return err
	}
	
	return c.parseResponse(resp, nil)
}

// ===== 게시글 API 메서드들 =====

// GetPosts - 모든 게시글 조회
func (c *APIClient) GetPosts() ([]Post, error) {
	resp, err := c.GET("/api/posts")
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var posts []Post
	if err := json.Unmarshal(jsonData, &posts); err != nil {
		return nil, fmt.Errorf("게시글 데이터 파싱 실패: %v", err)
	}
	
	return posts, nil
}

// GetPost - 특정 게시글 조회
func (c *APIClient) GetPost(id int) (*Post, error) {
	endpoint := fmt.Sprintf("/api/posts/%d", id)
	resp, err := c.GET(endpoint)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var post Post
	if err := json.Unmarshal(jsonData, &post); err != nil {
		return nil, fmt.Errorf("게시글 데이터 파싱 실패: %v", err)
	}
	
	return &post, nil
}

// CreatePost - 게시글 생성
func (c *APIClient) CreatePost(post Post) (*Post, error) {
	resp, err := c.POST("/api/posts", post)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var createdPost Post
	if err := json.Unmarshal(jsonData, &createdPost); err != nil {
		return nil, fmt.Errorf("게시글 데이터 파싱 실패: %v", err)
	}
	
	return &createdPost, nil
}

// UpdatePost - 게시글 수정
func (c *APIClient) UpdatePost(id int, post Post) (*Post, error) {
	endpoint := fmt.Sprintf("/api/posts/%d", id)
	resp, err := c.PUT(endpoint, post)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 JSON으로 변환 후 다시 파싱
	jsonData, _ := json.Marshal(response.Data)
	var updatedPost Post
	if err := json.Unmarshal(jsonData, &updatedPost); err != nil {
		return nil, fmt.Errorf("게시글 데이터 파싱 실패: %v", err)
	}
	
	return &updatedPost, nil
}

// DeletePost - 게시글 삭제
func (c *APIClient) DeletePost(id int) error {
	endpoint := fmt.Sprintf("/api/posts/%d", id)
	resp, err := c.DELETE(endpoint)
	if err != nil {
		return err
	}
	
	return c.parseResponse(resp, nil)
}

// ===== 검색 기능 =====

// Search - 검색 기능
func (c *APIClient) Search(query string) (map[string]interface{}, error) {
	endpoint := fmt.Sprintf("/api/search?q=%s", url.QueryEscape(query))
	resp, err := c.GET(endpoint)
	if err != nil {
		return nil, err
	}
	
	var response Response
	if err := c.parseResponse(resp, &response); err != nil {
		return nil, err
	}
	
	// 응답 데이터를 map으로 변환
	jsonData, _ := json.Marshal(response.Data)
	var result map[string]interface{}
	if err := json.Unmarshal(jsonData, &result); err != nil {
		return nil, fmt.Errorf("검색 결과 파싱 실패: %v", err)
	}
	
	return result, nil
}

// ===== 고급 기능들 =====

// GetWithContext - 컨텍스트를 사용한 GET 요청
func (c *APIClient) GetWithContext(ctx context.Context, endpoint string) (*http.Response, error) {
	url := c.BaseURL + endpoint
	
	req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
	if err != nil {
		return nil, fmt.Errorf("요청 생성 실패: %v", err)
	}
	
	// 헤더 설정
	for key, value := range c.Headers {
		req.Header.Set(key, value)
	}
	
	return c.HTTPClient.Do(req)
}

// PostWithTimeout - 타임아웃을 사용한 POST 요청
func (c *APIClient) PostWithTimeout(endpoint string, data interface{}, timeout time.Duration) (*http.Response, error) {
	// 임시 클라이언트 생성
	tempClient := &http.Client{
		Timeout: timeout,
	}
	
	jsonData, err := json.Marshal(data)
	if err != nil {
		return nil, fmt.Errorf("JSON 마샬링 실패: %v", err)
	}
	
	url := c.BaseURL + endpoint
	req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsonData))
	if err != nil {
		return nil, fmt.Errorf("요청 생성 실패: %v", err)
	}
	
	// 헤더 설정
	for key, value := range c.Headers {
		req.Header.Set(key, value)
	}
	
	return tempClient.Do(req)
}

// ===== 배치 요청 =====

// BatchGetUsers - 여러 사용자 동시 조회
func (c *APIClient) BatchGetUsers(ids []int) (map[int]*User, error) {
	results := make(map[int]*User)
	
	// 고루틴을 사용한 동시 요청
	type result struct {
		id   int
		user *User
		err  error
	}
	
	ch := make(chan result, len(ids))
	
	for _, id := range ids {
		go func(userID int) {
			user, err := c.GetUser(userID)
			ch <- result{id: userID, user: user, err: err}
		}(id)
	}
	
	// 결과 수집
	for i := 0; i < len(ids); i++ {
		res := <-ch
		if res.err != nil {
			return nil, fmt.Errorf("사용자 %d 조회 실패: %v", res.id, res.err)
		}
		results[res.id] = res.user
	}
	
	return results, nil
}

// ===== 파일 업로드 =====

// UploadFile - 파일 업로드 (시뮬레이션)
func (c *APIClient) UploadFile(filename string, data []byte) error {
	// 실제로는 multipart/form-data를 사용합니다
	// 여기서는 시뮬레이션으로 JSON으로 전송
	fileData := map[string]interface{}{
		"filename": filename,
		"size":     len(data),
		"content":  string(data),
	}
	
	resp, err := c.POST("/api/upload", fileData)
	if err != nil {
		return err
	}
	
	return c.parseResponse(resp, nil)
}

// ===== 실용적인 예제들 =====

// RunClientExamples - 클라이언트 예제 실행
func RunClientExamples() {
	fmt.Println("=== Go HTTP 클라이언트 예제 ===")
	
	// 클라이언트 생성
	client := NewAPIClient("http://localhost:8080")
	
	// 인증 토큰 설정 (필요한 경우)
	client.SetAuthToken("valid-token")
	
	// 1. 홈 페이지 접근
	fmt.Println("\n1. 홈 페이지 접근:")
	resp, err := client.GET("/")
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		defer resp.Body.Close()
		body, _ := io.ReadAll(resp.Body)
		fmt.Printf("응답: %s\n", string(body))
	}
	
	// 2. 사용자 목록 조회
	fmt.Println("\n2. 사용자 목록 조회:")
	users, err := client.GetUsers()
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("사용자 수: %d\n", len(users))
		for _, user := range users {
			fmt.Printf("  - %s (%s)\n", user.Name, user.Email)
		}
	}
	
	// 3. 특정 사용자 조회
	fmt.Println("\n3. 특정 사용자 조회:")
	user, err := client.GetUser(1)
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("사용자: %s (%s)\n", user.Name, user.Email)
	}
	
	// 4. 새 사용자 생성
	fmt.Println("\n4. 새 사용자 생성:")
	newUser := User{
		Name:  "홍길동",
		Email: "hong@example.com",
		Age:   30,
	}
	
	createdUser, err := client.CreateUser(newUser)
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("생성된 사용자: ID=%d, %s (%s)\n", 
			createdUser.ID, createdUser.Name, createdUser.Email)
	}
	
	// 5. 사용자 수정
	fmt.Println("\n5. 사용자 수정:")
	if createdUser != nil {
		createdUser.Age = 31
		updatedUser, err := client.UpdateUser(createdUser.ID, *createdUser)
		if err != nil {
			fmt.Printf("에러: %v\n", err)
		} else {
			fmt.Printf("수정된 사용자: 나이=%d\n", updatedUser.Age)
		}
	}
	
	// 6. 게시글 목록 조회
	fmt.Println("\n6. 게시글 목록 조회:")
	posts, err := client.GetPosts()
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("게시글 수: %d\n", len(posts))
		for _, post := range posts {
			fmt.Printf("  - %s (작성자: %s)\n", post.Title, post.Author)
		}
	}
	
	// 7. 새 게시글 생성
	fmt.Println("\n7. 새 게시글 생성:")
	newPost := Post{
		Title:   "HTTP 클라이언트 테스트",
		Content: "Go HTTP 클라이언트로 작성한 게시글입니다.",
		Author:  "홍길동",
	}
	
	createdPost, err := client.CreatePost(newPost)
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("생성된 게시글: ID=%d, %s\n", createdPost.ID, createdPost.Title)
	}
	
	// 8. 검색 기능
	fmt.Println("\n8. 검색 기능:")
	searchResults, err := client.Search("김철수")
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("검색 결과: %+v\n", searchResults)
	}
	
	// 9. 배치 요청
	fmt.Println("\n9. 배치 요청:")
	batchUsers, err := client.BatchGetUsers([]int{1, 2, 3})
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Printf("배치 조회 결과: %d명의 사용자\n", len(batchUsers))
		for id, user := range batchUsers {
			fmt.Printf("  ID %d: %s\n", id, user.Name)
		}
	}
	
	// 10. 컨텍스트를 사용한 요청
	fmt.Println("\n10. 컨텍스트를 사용한 요청:")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	
	resp, err = client.GetWithContext(ctx, "/api/users")
	if err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		defer resp.Body.Close()
		fmt.Printf("컨텍스트 요청 성공: 상태 코드 %d\n", resp.StatusCode)
	}
	
	// 11. 사용자 삭제 (정리)
	fmt.Println("\n11. 사용자 삭제 (정리):")
	if createdUser != nil {
		err := client.DeleteUser(createdUser.ID)
		if err != nil {
			fmt.Printf("에러: %v\n", err)
		} else {
			fmt.Println("사용자 삭제 성공")
		}
	}
	
	// 12. 게시글 삭제 (정리)
	fmt.Println("\n12. 게시글 삭제 (정리):")
	if createdPost != nil {
		err := client.DeletePost(createdPost.ID)
		if err != nil {
			fmt.Printf("에러: %v\n", err)
		} else {
			fmt.Println("게시글 삭제 성공")
		}
	}
	
	fmt.Println("\n✅ HTTP 클라이언트 예제 완료!")
}

// ===== 고급 클라이언트 기능 =====

// RetryClient - 재시도 기능이 있는 클라이언트
type RetryClient struct {
	*APIClient
	MaxRetries int
	RetryDelay time.Duration
}

// NewRetryClient - 재시도 클라이언트 생성
func NewRetryClient(baseURL string, maxRetries int, retryDelay time.Duration) *RetryClient {
	return &RetryClient{
		APIClient:  NewAPIClient(baseURL),
		MaxRetries: maxRetries,
		RetryDelay: retryDelay,
	}
}

// GetWithRetry - 재시도 기능이 있는 GET 요청
func (rc *RetryClient) GetWithRetry(endpoint string) (*http.Response, error) {
	var lastErr error
	
	for i := 0; i <= rc.MaxRetries; i++ {
		resp, err := rc.GET(endpoint)
		if err == nil {
			return resp, nil
		}
		
		lastErr = err
		fmt.Printf("요청 실패 (시도 %d/%d): %v\n", i+1, rc.MaxRetries+1, err)
		
		if i < rc.MaxRetries {
			time.Sleep(rc.RetryDelay)
		}
	}
	
	return nil, fmt.Errorf("최대 재시도 횟수 초과: %v", lastErr)
}

// ===== 메인 함수 =====

func main() {
	RunClientExamples()
} 