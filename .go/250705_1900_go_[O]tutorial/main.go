package main

import (
	"fmt"
	"os"
	"strings"

	"250625_1215_go/basics"
	"250625_1215_go/advanced"
)

// main 함수는 프로그램의 진입점입니다.
// Go에서는 main 패키지의 main 함수가 프로그램의 시작점이 됩니다.
func main() {
	fmt.Println("🚀 Go 언어 종합 학습 프로젝트")
	fmt.Println("================================")
	fmt.Println()

	if len(os.Args) < 2 {
		showMenu()
		return
	}

	category := strings.ToLower(os.Args[1])

	switch category {
	case "basics":
		runBasics()
	case "advanced":
		runAdvanced()
	case "http-server":
		runHTTPServer()
	case "http-client":
		runHTTPClient()
	case "examples":
		runExamples()
	case "tests":
		runTests()
	case "all":
		runAll()
	case "generics":
		runGenerics()
	case "defer-panic":
		runDeferPanic()
	default:
		fmt.Printf("알 수 없는 카테고리: %s\n", category)
		showMenu()
	}
}

func showMenu() {
	fmt.Println("사용 가능한 카테고리:")
	fmt.Println("  basics      - 기본 문법 (변수, 함수, 제어문, 배열, 슬라이스, 맵, 구조체)")
	fmt.Println("  advanced    - 고급 기능 (인터페이스, 고루틴, 동시성)")
	fmt.Println("  http-server - HTTP 서버 예제")
	fmt.Println("  http-client - HTTP 클라이언트 예제")
	fmt.Println("  examples    - 실용적 예제 (TODO 앱)")
	fmt.Println("  tests       - 테스트 코드 실행")
	fmt.Println("  all         - 모든 예제 실행")
	fmt.Println("  generics     - 제네릭(Generics) 예제")
	fmt.Println("  defer-panic  - defer/panic/recover 예제")
	fmt.Println()
	fmt.Println("사용법: go run main.go [카테고리]")
	fmt.Println("예시:  go run main.go basics")
}

func runBasics() {
	fmt.Println("📚 기본 문법 예제 실행 중...")
	fmt.Println("================================")
	
	basics.RunVariableExamples()
	basics.RunFunctionExamples()
	basics.RunControlFlowExamples()
	basics.RunArraySliceExamples()
	basics.RunMapExamples()
	basics.RunStructExamples()
}

func runAdvanced() {
	fmt.Println("🔬 고급 기능 예제 실행 중...")
	fmt.Println("================================")
	
	advanced.RunInterfaceExamples()
	advanced.RunGoroutineExamples()
}

func runHTTPServer() {
	fmt.Println("🌐 HTTP 서버 실행 중...")
	fmt.Println("================================")
	fmt.Println("서버를 시작하려면 다음 명령어를 실행하세요:")
	fmt.Println("  go run http_server/server.go")
	fmt.Println()
	fmt.Println("또는 별도 터미널에서:")
	fmt.Println("  cd http_server")
	fmt.Println("  go run server.go")
}

func runHTTPClient() {
	fmt.Println("📡 HTTP 클라이언트 실행 중...")
	fmt.Println("================================")
	fmt.Println("클라이언트를 실행하려면 다음 명령어를 실행하세요:")
	fmt.Println("  go run http_client/client.go")
	fmt.Println()
	fmt.Println("또는 별도 터미널에서:")
	fmt.Println("  cd http_client")
	fmt.Println("  go run client.go")
}

func runExamples() {
	fmt.Println("💡 실용적 예제 실행 중...")
	fmt.Println("================================")
	fmt.Println("TODO 앱을 실행하려면 다음 명령어를 실행하세요:")
	fmt.Println("  go run examples/todo_app.go")
	fmt.Println()
	fmt.Println("또는 별도 터미널에서:")
	fmt.Println("  cd examples")
	fmt.Println("  go run todo_app.go")
}

func runTests() {
	fmt.Println("🧪 테스트 코드 실행 중...")
	fmt.Println("================================")
	fmt.Println("테스트를 실행하려면 다음 명령어를 실행하세요:")
	fmt.Println("  go test ./tests/...")
	fmt.Println()
	fmt.Println("벤치마크 테스트:")
	fmt.Println("  go test -bench=. ./tests/...")
	fmt.Println()
	fmt.Println("테스트 커버리지:")
	fmt.Println("  go test -cover ./tests/...")
}

func runAll() {
	fmt.Println("🎯 모든 예제 실행 중...")
	fmt.Println("================================")
	
	runBasics()
	fmt.Println()
	runAdvanced()
	fmt.Println()
	
	fmt.Println("🌐 HTTP 서버/클라이언트는 별도로 실행해야 합니다:")
	fmt.Println("  터미널 1: go run http_server/server.go")
	fmt.Println("  터미널 2: go run http_client/client.go")
	fmt.Println()
	
	fmt.Println("💡 TODO 앱은 별도로 실행해야 합니다:")
	fmt.Println("  go run examples/todo_app.go")
	fmt.Println()
	
	fmt.Println("🧪 테스트는 별도로 실행해야 합니다:")
	fmt.Println("  go test ./tests/...")
}

func runGenerics() {
	fmt.Println("🧩 제네릭(Generics) 예제 실행 중...")
	fmt.Println("================================")
	fmt.Println("go run advanced/generics.go 로 직접 실행하세요.")
}

func runDeferPanic() {
	fmt.Println("🛑 defer/panic/recover 예제 실행 중...")
	fmt.Println("================================")
	fmt.Println("go run advanced/defer_panic.go 로 직접 실행하세요.")
} 