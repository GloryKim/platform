package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"sort"
	"strconv"
	"strings"
	"time"
)

// ===== TODO 앱 데이터 구조 =====

// Task - 할 일 항목
type Task struct {
	ID          int       `json:"id"`
	Title       string    `json:"title"`
	Description string    `json:"description"`
	Completed   bool      `json:"completed"`
	Priority    Priority  `json:"priority"`
	Category    string    `json:"category"`
	CreatedAt   time.Time `json:"created_at"`
	UpdatedAt   time.Time `json:"updated_at"`
	DueDate     *time.Time `json:"due_date,omitempty"`
}

// Priority - 우선순위 열거형
type Priority int

const (
	Low Priority = iota
	Medium
	High
	Urgent
)

// String - 우선순위를 문자열로 변환
func (p Priority) String() string {
	switch p {
	case Low:
		return "낮음"
	case Medium:
		return "보통"
	case High:
		return "높음"
	case Urgent:
		return "긴급"
	default:
		return "알 수 없음"
	}
}

// Color - 우선순위별 색상
func (p Priority) Color() string {
	switch p {
	case Low:
		return "\033[32m" // 녹색
	case Medium:
		return "\033[33m" // 노란색
	case High:
		return "\033[35m" // 자주색
	case Urgent:
		return "\033[31m" // 빨간색
	default:
		return "\033[0m" // 기본색
	}
}

// Reset - 색상 초기화
func (p Priority) Reset() string {
	return "\033[0m"
}

// ===== TODO 앱 구조체 =====

// TodoApp - TODO 앱 메인 구조체
type TodoApp struct {
	Tasks     []Task `json:"tasks"`
	NextID    int    `json:"next_id"`
	DataFile  string `json:"-"`
}

// NewTodoApp - 새로운 TODO 앱 생성
func NewTodoApp(dataFile string) *TodoApp {
	app := &TodoApp{
		Tasks:    make([]Task, 0),
		NextID:   1,
		DataFile: dataFile,
	}
	
	// 기존 데이터 로드
	app.LoadData()
	return app
}

// ===== 데이터 관리 =====

// SaveData - 데이터 저장
func (app *TodoApp) SaveData() error {
	data, err := json.MarshalIndent(app, "", "  ")
	if err != nil {
		return fmt.Errorf("JSON 마샬링 실패: %v", err)
	}
	
	err = ioutil.WriteFile(app.DataFile, data, 0644)
	if err != nil {
		return fmt.Errorf("파일 저장 실패: %v", err)
	}
	
	return nil
}

// LoadData - 데이터 로드
func (app *TodoApp) LoadData() error {
	if _, err := os.Stat(app.DataFile); os.IsNotExist(err) {
		// 파일이 없으면 새로 생성
		return app.SaveData()
	}
	
	data, err := ioutil.ReadFile(app.DataFile)
	if err != nil {
		return fmt.Errorf("파일 읽기 실패: %v", err)
	}
	
	err = json.Unmarshal(data, app)
	if err != nil {
		return fmt.Errorf("JSON 언마샬링 실패: %v", err)
	}
	
	return nil
}

// ===== 작업 관리 =====

// AddTask - 새 작업 추가
func (app *TodoApp) AddTask(title, description, category string, priority Priority, dueDate *time.Time) *Task {
	task := Task{
		ID:          app.NextID,
		Title:       title,
		Description: description,
		Completed:   false,
		Priority:    priority,
		Category:    category,
		CreatedAt:   time.Now(),
		UpdatedAt:   time.Now(),
		DueDate:     dueDate,
	}
	
	app.Tasks = append(app.Tasks, task)
	app.NextID++
	
	// 데이터 저장
	app.SaveData()
	
	return &task
}

// GetTask - 작업 조회
func (app *TodoApp) GetTask(id int) *Task {
	for i := range app.Tasks {
		if app.Tasks[i].ID == id {
			return &app.Tasks[i]
		}
	}
	return nil
}

// UpdateTask - 작업 수정
func (app *TodoApp) UpdateTask(id int, title, description, category string, priority Priority, dueDate *time.Time) error {
	task := app.GetTask(id)
	if task == nil {
		return fmt.Errorf("작업을 찾을 수 없습니다: ID %d", id)
	}
	
	task.Title = title
	task.Description = description
	task.Category = category
	task.Priority = priority
	task.DueDate = dueDate
	task.UpdatedAt = time.Now()
	
	app.SaveData()
	return nil
}

// DeleteTask - 작업 삭제
func (app *TodoApp) DeleteTask(id int) error {
	for i := range app.Tasks {
		if app.Tasks[i].ID == id {
			app.Tasks = append(app.Tasks[:i], app.Tasks[i+1:]...)
			app.SaveData()
			return nil
		}
	}
	return fmt.Errorf("작업을 찾을 수 없습니다: ID %d", id)
}

// ToggleTask - 작업 완료 상태 토글
func (app *TodoApp) ToggleTask(id int) error {
	task := app.GetTask(id)
	if task == nil {
		return fmt.Errorf("작업을 찾을 수 없습니다: ID %d", id)
	}
	
	task.Completed = !task.Completed
	task.UpdatedAt = time.Now()
	
	app.SaveData()
	return nil
}

// ===== 작업 조회 =====

// GetAllTasks - 모든 작업 조회
func (app *TodoApp) GetAllTasks() []Task {
	return app.Tasks
}

// GetTasksByStatus - 상태별 작업 조회
func (app *TodoApp) GetTasksByStatus(completed bool) []Task {
	var result []Task
	for _, task := range app.Tasks {
		if task.Completed == completed {
			result = append(result, task)
		}
	}
	return result
}

// GetTasksByPriority - 우선순위별 작업 조회
func (app *TodoApp) GetTasksByPriority(priority Priority) []Task {
	var result []Task
	for _, task := range app.Tasks {
		if task.Priority == priority {
			result = append(result, task)
		}
	}
	return result
}

// GetTasksByCategory - 카테고리별 작업 조회
func (app *TodoApp) GetTasksByCategory(category string) []Task {
	var result []Task
	for _, task := range app.Tasks {
		if strings.EqualFold(task.Category, category) {
			result = append(result, task)
		}
	}
	return result
}

// SearchTasks - 작업 검색
func (app *TodoApp) SearchTasks(query string) []Task {
	var result []Task
	query = strings.ToLower(query)
	
	for _, task := range app.Tasks {
		if strings.Contains(strings.ToLower(task.Title), query) ||
		   strings.Contains(strings.ToLower(task.Description), query) ||
		   strings.Contains(strings.ToLower(task.Category), query) {
			result = append(result, task)
		}
	}
	return result
}

// GetOverdueTasks - 기한이 지난 작업 조회
func (app *TodoApp) GetOverdueTasks() []Task {
	var result []Task
	now := time.Now()
	
	for _, task := range app.Tasks {
		if !task.Completed && task.DueDate != nil && task.DueDate.Before(now) {
			result = append(result, task)
		}
	}
	return result
}

// ===== 통계 =====

// GetStats - 통계 정보
func (app *TodoApp) GetStats() map[string]interface{} {
	total := len(app.Tasks)
	completed := 0
	overdue := 0
	
	priorityCount := make(map[Priority]int)
	categoryCount := make(map[string]int)
	
	for _, task := range app.Tasks {
		if task.Completed {
			completed++
		}
		
		if !task.Completed && task.DueDate != nil && task.DueDate.Before(time.Now()) {
			overdue++
		}
		
		priorityCount[task.Priority]++
		categoryCount[task.Category]++
	}
	
	return map[string]interface{}{
		"total":           total,
		"completed":       completed,
		"pending":         total - completed,
		"overdue":         overdue,
		"completion_rate": float64(completed) / float64(total) * 100,
		"priority_stats":  priorityCount,
		"category_stats":  categoryCount,
	}
}

// ===== 정렬 =====

// SortTasksByPriority - 우선순위별 정렬
func (app *TodoApp) SortTasksByPriority() []Task {
	tasks := make([]Task, len(app.Tasks))
	copy(tasks, app.Tasks)
	
	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].Priority > tasks[j].Priority
	})
	
	return tasks
}

// SortTasksByDueDate - 기한별 정렬
func (app *TodoApp) SortTasksByDueDate() []Task {
	tasks := make([]Task, len(app.Tasks))
	copy(tasks, app.Tasks)
	
	sort.Slice(tasks, func(i, j int) bool {
		if tasks[i].DueDate == nil && tasks[j].DueDate == nil {
			return false
		}
		if tasks[i].DueDate == nil {
			return false
		}
		if tasks[j].DueDate == nil {
			return true
		}
		return tasks[i].DueDate.Before(*tasks[j].DueDate)
	})
	
	return tasks
}

// SortTasksByCreatedAt - 생성일별 정렬
func (app *TodoApp) SortTasksByCreatedAt() []Task {
	tasks := make([]Task, len(app.Tasks))
	copy(tasks, app.Tasks)
	
	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].CreatedAt.After(tasks[j].CreatedAt)
	})
	
	return tasks
}

// ===== 표시 =====

// DisplayTask - 작업 표시
func (app *TodoApp) DisplayTask(task Task) {
	status := "□"
	if task.Completed {
		status = "■"
	}
	
	fmt.Printf("%s [%d] %s\n", status, task.ID, task.Title)
	fmt.Printf("   설명: %s\n", task.Description)
	fmt.Printf("   카테고리: %s\n", task.Category)
	fmt.Printf("   우선순위: %s%s%s\n", task.Priority.Color(), task.Priority.String(), task.Priority.Reset())
	
	if task.DueDate != nil {
		dueStr := task.DueDate.Format("2006-01-02 15:04")
		if task.DueDate.Before(time.Now()) && !task.Completed {
			fmt.Printf("   기한: %s (기한 초과!)\n", dueStr)
		} else {
			fmt.Printf("   기한: %s\n", dueStr)
		}
	}
	
	fmt.Printf("   생성일: %s\n", task.CreatedAt.Format("2006-01-02 15:04"))
	fmt.Printf("   수정일: %s\n", task.UpdatedAt.Format("2006-01-02 15:04"))
	fmt.Println()
}

// DisplayTasks - 작업 목록 표시
func (app *TodoApp) DisplayTasks(tasks []Task) {
	if len(tasks) == 0 {
		fmt.Println("작업이 없습니다.")
		return
	}
	
	for _, task := range tasks {
		app.DisplayTask(task)
	}
}

// DisplayStats - 통계 표시
func (app *TodoApp) DisplayStats() {
	stats := app.GetStats()
	
	fmt.Println("=== TODO 앱 통계 ===")
	fmt.Printf("전체 작업: %d개\n", stats["total"])
	fmt.Printf("완료된 작업: %d개\n", stats["completed"])
	fmt.Printf("대기 중인 작업: %d개\n", stats["pending"])
	fmt.Printf("기한 초과: %d개\n", stats["overdue"])
	fmt.Printf("완료율: %.1f%%\n", stats["completion_rate"])
	
	fmt.Println("\n우선순위별 통계:")
	for priority, count := range stats["priority_stats"].(map[Priority]int) {
		fmt.Printf("  %s%s%s: %d개\n", priority.Color(), priority.String(), priority.Reset(), count)
	}
	
	fmt.Println("\n카테고리별 통계:")
	for category, count := range stats["category_stats"].(map[string]int) {
		fmt.Printf("  %s: %d개\n", category, count)
	}
	fmt.Println()
}

// ===== 대화형 인터페이스 =====

// RunInteractive - 대화형 인터페이스 실행
func (app *TodoApp) RunInteractive() {
	fmt.Println("=== TODO 앱 ===")
	fmt.Println("명령어:")
	fmt.Println("  add     - 새 작업 추가")
	fmt.Println("  list    - 작업 목록 보기")
	fmt.Println("  view    - 특정 작업 보기")
	fmt.Println("  edit    - 작업 수정")
	fmt.Println("  toggle  - 작업 완료 상태 변경")
	fmt.Println("  delete  - 작업 삭제")
	fmt.Println("  search  - 작업 검색")
	fmt.Println("  stats   - 통계 보기")
	fmt.Println("  quit    - 종료")
	fmt.Println()
	
	for {
		fmt.Print("명령어 입력: ")
		var command string
		fmt.Scanln(&command)
		
		switch command {
		case "add":
			app.handleAdd()
		case "list":
			app.handleList()
		case "view":
			app.handleView()
		case "edit":
			app.handleEdit()
		case "toggle":
			app.handleToggle()
		case "delete":
			app.handleDelete()
		case "search":
			app.handleSearch()
		case "stats":
			app.handleStats()
		case "quit":
			fmt.Println("TODO 앱을 종료합니다.")
			return
		default:
			fmt.Println("알 수 없는 명령어입니다.")
		}
		fmt.Println()
	}
}

// handleAdd - 작업 추가 처리
func (app *TodoApp) handleAdd() {
	var title, description, category string
	var priorityStr string
	
	fmt.Print("제목: ")
	fmt.Scanln(&title)
	
	fmt.Print("설명: ")
	fmt.Scanln(&description)
	
	fmt.Print("카테고리: ")
	fmt.Scanln(&category)
	
	fmt.Print("우선순위 (낮음/보통/높음/긴급): ")
	fmt.Scanln(&priorityStr)
	
	var priority Priority
	switch priorityStr {
	case "낮음":
		priority = Low
	case "보통":
		priority = Medium
	case "높음":
		priority = High
	case "긴급":
		priority = Urgent
	default:
		priority = Medium
	}
	
	task := app.AddTask(title, description, category, priority, nil)
	fmt.Printf("작업이 추가되었습니다: ID %d\n", task.ID)
}

// handleList - 작업 목록 처리
func (app *TodoApp) handleList() {
	fmt.Print("필터 (all/completed/pending/priority/category): ")
	var filter string
	fmt.Scanln(&filter)
	
	var tasks []Task
	switch filter {
	case "completed":
		tasks = app.GetTasksByStatus(true)
	case "pending":
		tasks = app.GetTasksByStatus(false)
	case "priority":
		fmt.Print("우선순위 (낮음/보통/높음/긴급): ")
		var priorityStr string
		fmt.Scanln(&priorityStr)
		var priority Priority
		switch priorityStr {
		case "낮음":
			priority = Low
		case "보통":
			priority = Medium
		case "높음":
			priority = High
		case "긴급":
			priority = Urgent
		default:
			tasks = app.GetAllTasks()
		}
		if tasks == nil {
			tasks = app.GetTasksByPriority(priority)
		}
	case "category":
		fmt.Print("카테고리: ")
		var category string
		fmt.Scanln(&category)
		tasks = app.GetTasksByCategory(category)
	default:
		tasks = app.GetAllTasks()
	}
	
	app.DisplayTasks(tasks)
}

// handleView - 작업 조회 처리
func (app *TodoApp) handleView() {
	fmt.Print("작업 ID: ")
	var idStr string
	fmt.Scanln(&idStr)
	
	id, err := strconv.Atoi(idStr)
	if err != nil {
		fmt.Println("잘못된 ID입니다.")
		return
	}
	
	task := app.GetTask(id)
	if task == nil {
		fmt.Println("작업을 찾을 수 없습니다.")
		return
	}
	
	app.DisplayTask(*task)
}

// handleEdit - 작업 수정 처리
func (app *TodoApp) handleEdit() {
	fmt.Print("작업 ID: ")
	var idStr string
	fmt.Scanln(&idStr)
	
	id, err := strconv.Atoi(idStr)
	if err != nil {
		fmt.Println("잘못된 ID입니다.")
		return
	}
	
	task := app.GetTask(id)
	if task == nil {
		fmt.Println("작업을 찾을 수 없습니다.")
		return
	}
	
	var title, description, category string
	var priorityStr string
	
	fmt.Printf("제목 (현재: %s): ", task.Title)
	fmt.Scanln(&title)
	if title == "" {
		title = task.Title
	}
	
	fmt.Printf("설명 (현재: %s): ", task.Description)
	fmt.Scanln(&description)
	if description == "" {
		description = task.Description
	}
	
	fmt.Printf("카테고리 (현재: %s): ", task.Category)
	fmt.Scanln(&category)
	if category == "" {
		category = task.Category
	}
	
	fmt.Printf("우선순위 (현재: %s): ", task.Priority.String())
	fmt.Scanln(&priorityStr)
	
	var priority Priority
	switch priorityStr {
	case "낮음":
		priority = Low
	case "보통":
		priority = Medium
	case "높음":
		priority = High
	case "긴급":
		priority = Urgent
	default:
		priority = task.Priority
	}
	
	err = app.UpdateTask(id, title, description, category, priority, task.DueDate)
	if err != nil {
		fmt.Printf("작업 수정 실패: %v\n", err)
	} else {
		fmt.Println("작업이 수정되었습니다.")
	}
}

// handleToggle - 작업 토글 처리
func (app *TodoApp) handleToggle() {
	fmt.Print("작업 ID: ")
	var idStr string
	fmt.Scanln(&idStr)
	
	id, err := strconv.Atoi(idStr)
	if err != nil {
		fmt.Println("잘못된 ID입니다.")
		return
	}
	
	err = app.ToggleTask(id)
	if err != nil {
		fmt.Printf("작업 상태 변경 실패: %v\n", err)
	} else {
		fmt.Println("작업 상태가 변경되었습니다.")
	}
}

// handleDelete - 작업 삭제 처리
func (app *TodoApp) handleDelete() {
	fmt.Print("작업 ID: ")
	var idStr string
	fmt.Scanln(&idStr)
	
	id, err := strconv.Atoi(idStr)
	if err != nil {
		fmt.Println("잘못된 ID입니다.")
		return
	}
	
	err = app.DeleteTask(id)
	if err != nil {
		fmt.Printf("작업 삭제 실패: %v\n", err)
	} else {
		fmt.Println("작업이 삭제되었습니다.")
	}
}

// handleSearch - 작업 검색 처리
func (app *TodoApp) handleSearch() {
	fmt.Print("검색어: ")
	var query string
	fmt.Scanln(&query)
	
	tasks := app.SearchTasks(query)
	app.DisplayTasks(tasks)
}

// handleStats - 통계 처리
func (app *TodoApp) handleStats() {
	app.DisplayStats()
}

// ===== 메인 함수 =====

func main() {
	app := NewTodoApp("todo_data.json")
	
	// 샘플 데이터 추가 (처음 실행 시)
	if len(app.Tasks) == 0 {
		fmt.Println("샘플 데이터를 추가합니다...")
		
		due1 := time.Now().Add(24 * time.Hour)
		due2 := time.Now().Add(-2 * time.Hour)
		
		app.AddTask("Go 언어 학습", "Go 언어 기본 문법과 고급 기능 학습", "학습", High, &due1)
		app.AddTask("프로젝트 계획", "새 프로젝트의 요구사항 분석 및 설계", "업무", Urgent, &due2)
		app.AddTask("운동하기", "30분 조깅하기", "건강", Medium, nil)
		app.AddTask("장보기", "우유, 빵, 계란 구매", "생활", Low, nil)
		
		// 첫 번째 작업 완료 처리
		app.ToggleTask(1)
	}
	
	app.RunInteractive()
} 