package advanced

import (
	"context"
	"fmt"
	"math/rand"
	"runtime"
	"sync"
	"time"
)

// ===== 고루틴 기본 개념 =====

// BasicGoroutine - 기본 고루틴 예제
func BasicGoroutine() {
	fmt.Println("=== 고루틴 기본 예제 ===")
	
	// 동기 실행
	fmt.Println("동기 실행:")
	for i := 1; i <= 3; i++ {
		fmt.Printf("작업 %d 실행 중...\n", i)
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("작업 %d 완료\n", i)
	}
	
	// 비동기 실행 (고루틴)
	fmt.Println("\n비동기 실행 (고루틴):")
	for i := 1; i <= 3; i++ {
		go func(id int) {
			fmt.Printf("고루틴 %d 시작\n", id)
			time.Sleep(100 * time.Millisecond)
			fmt.Printf("고루틴 %d 완료\n", id)
		}(i)
	}
	
	// 메인 고루틴이 종료되지 않도록 대기
	time.Sleep(500 * time.Millisecond)
}

// ===== 채널 기본 개념 =====

// BasicChannel - 기본 채널 예제
func BasicChannel() {
	fmt.Println("\n=== 채널 기본 예제 ===")
	
	// 채널 생성
	ch := make(chan string)
	
	// 고루틴에서 채널로 데이터 전송
	go func() {
		fmt.Println("고루틴: 데이터 전송 준비")
		time.Sleep(100 * time.Millisecond)
		ch <- "안녕하세요!"
		fmt.Println("고루틴: 데이터 전송 완료")
	}()
	
	// 메인 고루틴에서 채널에서 데이터 수신
	fmt.Println("메인: 데이터 수신 대기 중...")
	message := <-ch
	fmt.Printf("메인: 수신된 메시지 - %s\n", message)
}

// ===== 채널 방향성 =====

// ChannelDirections - 채널 방향성 예제
func ChannelDirections() {
	fmt.Println("\n=== 채널 방향성 예제 ===")
	
	// 양방향 채널
	bidirectional := make(chan int)
	
	// 송신 전용 채널
	sendOnly := make(chan<- int)
	
	// 수신 전용 채널
	receiveOnly := make(<-chan int)
	
	fmt.Printf("양방향 채널: %T\n", bidirectional)
	fmt.Printf("송신 전용 채널: %T\n", sendOnly)
	fmt.Printf("수신 전용 채널: %T\n", receiveOnly)
	
	// 채널 방향성 변환
	sendOnly = bidirectional // 양방향 → 송신 전용
	receiveOnly = bidirectional // 양방향 → 수신 전용
	
	// 실제 사용 예제
	go func(ch chan<- int) {
		ch <- 42
	}(bidirectional)
	
	value := <-receiveOnly
	fmt.Printf("수신된 값: %d\n", value)
}

// ===== 버퍼링된 채널 =====

// BufferedChannel - 버퍼링된 채널 예제
func BufferedChannel() {
	fmt.Println("\n=== 버퍼링된 채널 예제 ===")
	
	// 버퍼 크기가 2인 채널
	ch := make(chan int, 2)
	
	// 버퍼가 가득 찰 때까지 블록되지 않음
	ch <- 1
	ch <- 2
	fmt.Println("버퍼링된 채널에 2개 값 전송 완료")
	
	// 값 수신
	fmt.Printf("수신된 값 1: %d\n", <-ch)
	fmt.Printf("수신된 값 2: %d\n", <-ch)
	
	// 버퍼가 비어있을 때 수신하면 블록
	fmt.Println("버퍼링된 채널에서 추가 값 수신 시도...")
	go func() {
		time.Sleep(500 * time.Millisecond)
		ch <- 3
		fmt.Println("추가 값 전송 완료")
	}()
	
	value := <-ch
	fmt.Printf("추가 수신된 값: %d\n", value)
}

// ===== 채널 닫기 =====

// ChannelClose - 채널 닫기 예제
func ChannelClose() {
	fmt.Println("\n=== 채널 닫기 예제 ===")
	
	ch := make(chan int)
	
	// 고루틴에서 값 전송 후 채널 닫기
	go func() {
		for i := 1; i <= 3; i++ {
			ch <- i
			time.Sleep(100 * time.Millisecond)
		}
		close(ch) // 채널 닫기
		fmt.Println("채널이 닫혔습니다")
	}()
	
	// 채널이 닫힐 때까지 값 수신
	for {
		value, ok := <-ch
		if !ok {
			fmt.Println("채널이 닫혔습니다")
			break
		}
		fmt.Printf("수신된 값: %d\n", value)
	}
	
	// range를 사용한 채널 순회
	fmt.Println("\nrange를 사용한 채널 순회:")
	ch2 := make(chan string)
	go func() {
		ch2 <- "첫 번째"
		ch2 <- "두 번째"
		ch2 <- "세 번째"
		close(ch2)
	}()
	
	for value := range ch2 {
		fmt.Printf("수신: %s\n", value)
	}
}

// ===== select 문 =====

// SelectExample - select 문 예제
func SelectExample() {
	fmt.Println("\n=== select 문 예제 ===")
	
	ch1 := make(chan string)
	ch2 := make(chan string)
	
	// 고루틴 1
	go func() {
		time.Sleep(200 * time.Millisecond)
		ch1 <- "채널 1에서 온 메시지"
	}()
	
	// 고루틴 2
	go func() {
		time.Sleep(100 * time.Millisecond)
		ch2 <- "채널 2에서 온 메시지"
	}()
	
	// select로 여러 채널 동시 대기
	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-ch1:
			fmt.Printf("채널 1: %s\n", msg1)
		case msg2 := <-ch2:
			fmt.Printf("채널 2: %s\n", msg2)
		case <-time.After(300 * time.Millisecond):
			fmt.Println("타임아웃!")
		}
	}
}

// ===== 동기화 (Mutex) =====

// MutexExample - 뮤텍스 예제
func MutexExample() {
	fmt.Println("\n=== 뮤텍스 예제 ===")
	
	var (
		counter int
		mutex   sync.Mutex
		wg      sync.WaitGroup
	)
	
	// 여러 고루틴에서 동시에 카운터 증가
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			
			for j := 0; j < 1000; j++ {
				mutex.Lock() // 뮤텍스 잠금
				counter++
				mutex.Unlock() // 뮤텍스 해제
			}
			fmt.Printf("고루틴 %d 완료\n", id)
		}(i)
	}
	
	wg.Wait()
	fmt.Printf("최종 카운터 값: %d\n", counter)
}

// ===== RWMutex =====

// RWMutexExample - 읽기/쓰기 뮤텍스 예제
func RWMutexExample() {
	fmt.Println("\n=== 읽기/쓰기 뮤텍스 예제 ===")
	
	var (
		data map[string]int
		rw   sync.RWMutex
		wg   sync.WaitGroup
	)
	
	data = make(map[string]int)
	
	// 읽기 고루틴들 (동시 실행 가능)
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			for j := 0; j < 5; j++ {
				rw.RLock() // 읽기 잠금
				fmt.Printf("읽기 고루틴 %d: 데이터 읽는 중...\n", id)
				time.Sleep(50 * time.Millisecond)
				rw.RUnlock() // 읽기 해제
			}
		}(i)
	}
	
	// 쓰기 고루틴 (독점 실행)
	wg.Add(1)
	go func() {
		defer wg.Done()
		for i := 0; i < 3; i++ {
			rw.Lock() // 쓰기 잠금
			fmt.Printf("쓰기 고루틴: 데이터 쓰는 중... (%d)\n", i)
			data[fmt.Sprintf("key%d", i)] = i
			time.Sleep(100 * time.Millisecond)
			rw.Unlock() // 쓰기 해제
		}
	}()
	
	wg.Wait()
	fmt.Printf("최종 데이터: %v\n", data)
}

// ===== WaitGroup =====

// WaitGroupExample - WaitGroup 예제
func WaitGroupExample() {
	fmt.Println("\n=== WaitGroup 예제 ===")
	
	var wg sync.WaitGroup
	
	// 여러 고루틴 시작
	for i := 1; i <= 3; i++ {
		wg.Add(1) // 고루틴 추가
		
		go func(id int) {
			defer wg.Done() // 고루틴 완료 시그널
			
			fmt.Printf("고루틴 %d 시작\n", id)
			time.Sleep(time.Duration(rand.Intn(500)) * time.Millisecond)
			fmt.Printf("고루틴 %d 완료\n", id)
		}(i)
	}
	
	fmt.Println("모든 고루틴 완료 대기 중...")
	wg.Wait() // 모든 고루틴 완료까지 대기
	fmt.Println("모든 고루틴이 완료되었습니다!")
}

// ===== 채널을 이용한 동기화 =====

// ChannelSync - 채널을 이용한 동기화 예제
func ChannelSync() {
	fmt.Println("\n=== 채널을 이용한 동기화 예제 ===")
	
	// 작업 완료 신호용 채널
	done := make(chan bool)
	
	// 고루틴에서 작업 수행
	go func() {
		fmt.Println("고루틴: 작업 시작")
		time.Sleep(200 * time.Millisecond)
		fmt.Println("고루틴: 작업 완료")
		done <- true // 완료 신호 전송
	}()
	
	fmt.Println("메인: 고루틴 완료 대기 중...")
	<-done // 완료 신호 수신까지 대기
	fmt.Println("메인: 고루틴이 완료되었습니다!")
}

// ===== 고급 패턴들 =====

// WorkerPool - 워커 풀 패턴
func WorkerPool() {
	fmt.Println("\n=== 워커 풀 패턴 ===")
	
	const numWorkers = 3
	const numJobs = 10
	
	// 작업 채널과 결과 채널
	jobs := make(chan int, numJobs)
	results := make(chan int, numJobs)
	
	// 워커 고루틴들 시작
	for i := 1; i <= numWorkers; i++ {
		go worker(i, jobs, results)
	}
	
	// 작업 전송
	for i := 1; i <= numJobs; i++ {
		jobs <- i
	}
	close(jobs) // 작업 채널 닫기
	
	// 결과 수집
	for i := 1; i <= numJobs; i++ {
		result := <-results
		fmt.Printf("작업 %d 결과: %d\n", i, result)
	}
}

// worker - 워커 함수
func worker(id int, jobs <-chan int, results chan<- int) {
	for job := range jobs {
		fmt.Printf("워커 %d: 작업 %d 처리 중...\n", id, job)
		time.Sleep(100 * time.Millisecond)
		results <- job * 2 // 작업 결과
	}
}

// Pipeline - 파이프라인 패턴
func Pipeline() {
	fmt.Println("\n=== 파이프라인 패턴 ===")
	
	// 1단계: 숫자 생성
	numbers := generate(1, 5)
	
	// 2단계: 제곱 계산
	squares := square(numbers)
	
	// 3단계: 결과 출력
	for result := range squares {
		fmt.Printf("파이프라인 결과: %d\n", result)
	}
}

// generate - 숫자 생성기
func generate(start, end int) <-chan int {
	ch := make(chan int)
	go func() {
		defer close(ch)
		for i := start; i <= end; i++ {
			ch <- i
		}
	}()
	return ch
}

// square - 제곱 계산기
func square(in <-chan int) <-chan int {
	ch := make(chan int)
	go func() {
		defer close(ch)
		for n := range in {
			ch <- n * n
		}
	}()
	return ch
}

// FanOutFanIn - Fan-Out/Fan-In 패턴
func FanOutFanIn() {
	fmt.Println("\n=== Fan-Out/Fan-In 패턴 ===")
	
	// 입력 채널
	input := make(chan int)
	
	// Fan-Out: 여러 워커로 작업 분산
	workers := make([]<-chan int, 3)
	for i := 0; i < 3; i++ {
		workers[i] = workerFanOut(i, input)
	}
	
	// Fan-In: 결과 통합
	output := fanIn(workers...)
	
	// 입력 전송
	go func() {
		for i := 1; i <= 6; i++ {
			input <- i
		}
		close(input)
	}()
	
	// 결과 수집
	for result := range output {
		fmt.Printf("Fan-Out/Fan-In 결과: %d\n", result)
	}
}

// workerFanOut - Fan-Out 워커
func workerFanOut(id int, input <-chan int) <-chan int {
	output := make(chan int)
	go func() {
		defer close(output)
		for n := range input {
			fmt.Printf("워커 %d: %d 처리 중...\n", id, n)
			time.Sleep(100 * time.Millisecond)
			output <- n * n
		}
	}()
	return output
}

// fanIn - Fan-In 함수
func fanIn(inputs ...<-chan int) <-chan int {
	output := make(chan int)
	var wg sync.WaitGroup
	
	// 각 입력 채널에서 결과 수집
	for _, input := range inputs {
		wg.Add(1)
		go func(ch <-chan int) {
			defer wg.Done()
			for n := range ch {
				output <- n
			}
		}(input)
	}
	
	// 모든 고루틴 완료 후 출력 채널 닫기
	go func() {
		wg.Wait()
		close(output)
	}()
	
	return output
}

// ===== 컨텍스트 (Context) =====

// ContextExample - 컨텍스트 예제
func ContextExample() {
	fmt.Println("\n=== 컨텍스트 예제 ===")
	
	// 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
	defer cancel()
	
	// 컨텍스트를 사용하는 고루틴
	go func() {
		for {
			select {
			case <-ctx.Done():
				fmt.Println("컨텍스트 취소됨:", ctx.Err())
				return
			default:
				fmt.Println("작업 수행 중...")
				time.Sleep(500 * time.Millisecond)
			}
		}
	}()
	
	// 메인 고루틴 대기
	time.Sleep(3 * time.Second)
}

// ===== 고루틴 누수 방지 =====

// GoroutineLeakPrevention - 고루틴 누수 방지 예제
func GoroutineLeakPrevention() {
	fmt.Println("\n=== 고루틴 누수 방지 예제 ===")
	
	// 올바른 방법: 채널 닫기
	ch := make(chan int)
	
	go func() {
		defer close(ch) // 반드시 채널 닫기
		for i := 1; i <= 3; i++ {
			ch <- i
		}
	}()
	
	for value := range ch {
		fmt.Printf("수신: %d\n", value)
	}
	
	// 컨텍스트를 사용한 취소
	ctx, cancel := context.WithCancel(context.Background())
	
	go func() {
		for {
			select {
			case <-ctx.Done():
				fmt.Println("고루틴 정상 종료")
				return
			default:
				// 작업 수행
				time.Sleep(100 * time.Millisecond)
			}
		}
	}()
	
	time.Sleep(300 * time.Millisecond)
	cancel() // 고루틴 취소
}

// ===== 성능 최적화 =====

// PerformanceOptimization - 성능 최적화 예제
func PerformanceOptimization() {
	fmt.Println("\n=== 성능 최적화 예제 ===")
	
	// 1. 적절한 버퍼 크기 사용
	bufferedCh := make(chan int, 100)
	
	// 2. 고루틴 풀 사용
	const numWorkers = 10
	workerPool := make(chan struct{}, numWorkers)
	
	for i := 0; i < 20; i++ {
		workerPool <- struct{}{} // 워커 획득
		go func(id int) {
			defer func() { <-workerPool }() // 워커 반환
			
			// 작업 수행
			time.Sleep(50 * time.Millisecond)
			bufferedCh <- id
		}(i)
	}
	
	// 결과 수집
	for i := 0; i < 20; i++ {
		<-bufferedCh
	}
	
	fmt.Println("성능 최적화 예제 완료")
}

// ===== 실용적인 예제들 =====

// WebCrawler - 웹 크롤러 시뮬레이션
func WebCrawler() {
	fmt.Println("\n=== 웹 크롤러 시뮬레이션 ===")
	
	urls := []string{
		"https://example1.com",
		"https://example2.com",
		"https://example3.com",
		"https://example4.com",
		"https://example5.com",
	}
	
	// 동시 크롤링
	results := make(chan string, len(urls))
	var wg sync.WaitGroup
	
	for _, url := range urls {
		wg.Add(1)
		go func(u string) {
			defer wg.Done()
			
			// 크롤링 시뮬레이션
			time.Sleep(time.Duration(rand.Intn(500)) * time.Millisecond)
			results <- fmt.Sprintf("크롤링 완료: %s", u)
		}(url)
	}
	
	// 고루틴 완료 대기
	go func() {
		wg.Wait()
		close(results)
	}()
	
	// 결과 수집
	for result := range results {
		fmt.Println(result)
	}
}

// RateLimiter - 속도 제한기
func RateLimiter() {
	fmt.Println("\n=== 속도 제한기 ===")
	
	// 초당 2개 요청으로 제한
	limiter := time.Tick(500 * time.Millisecond)
	
	for i := 1; i <= 5; i++ {
		<-limiter // 속도 제한 대기
		fmt.Printf("요청 %d 처리 중...\n", i)
	}
}

// ===== 테스트 헬퍼 =====

// GoroutineCounter - 고루틴 개수 카운터
func GoroutineCounter() {
	fmt.Println("\n=== 고루틴 개수 모니터링 ===")
	
	// 고루틴 개수 출력
	fmt.Printf("현재 고루틴 개수: %d\n", runtime.NumGoroutine())
	
	// 여러 고루틴 생성
	for i := 0; i < 5; i++ {
		go func() {
			time.Sleep(1 * time.Second)
		}()
	}
	
	fmt.Printf("고루틴 생성 후 개수: %d\n", runtime.NumGoroutine())
	
	// 잠시 대기 후 다시 확인
	time.Sleep(2 * time.Second)
	fmt.Printf("대기 후 고루틴 개수: %d\n", runtime.NumGoroutine())
}

// RunGoroutineExamples - 모든 고루틴 예제 실행
func RunGoroutineExamples() {
	fmt.Println("=== Go 고루틴과 동시성 예제 ===")
	
	// 기본 개념들
	BasicGoroutine()
	BasicChannel()
	ChannelDirections()
	BufferedChannel()
	ChannelClose()
	SelectExample()
	
	// 동기화
	MutexExample()
	RWMutexExample()
	WaitGroupExample()
	ChannelSync()
	
	// 고급 패턴들
	WorkerPool()
	Pipeline()
	FanOutFanIn()
	
	// 컨텍스트와 최적화
	ContextExample()
	GoroutineLeakPrevention()
	PerformanceOptimization()
	
	// 실용적인 예제들
	WebCrawler()
	RateLimiter()
	GoroutineCounter()
} 