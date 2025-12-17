package main

import (
	"fmt"
	"sort"
	"strings"
	"time"
)

// Go 언어의 맵(Map) 완전 가이드
func main() {
	fmt.Println("🗺️ Go 언어 맵(Map) 완전 가이드")
	fmt.Println("=============================")

	// 1. 맵 기본 사용법
	basicMaps()

	// 2. 맵 조작
	mapOperations()

	// 3. 맵 내장 함수
	mapBuiltins()

	// 4. 맵 순회
	mapIteration()

	// 5. 맵 활용 패턴
	mapPatterns()

	// 6. 맵 성능과 메모리
	mapPerformance()

	// 7. 실용적인 맵 예제
	practicalMapExamples()

	// 8. 맵의 특징과 장점
	mapFeatures()
}

// basicMaps 함수는 맵의 기본 사용법을 보여줍니다.
func basicMaps() {
	fmt.Println("\n📝 1. 맵 기본 사용법")
	fmt.Println("-------------------")

	// 맵 선언 방법들
	var map1 map[string]int                   // nil 맵
	var map2 = map[string]int{"a": 1, "b": 2} // 리터럴로 초기화
	map3 := map[string]int{"x": 10, "y": 20}  // 단축 선언
	map4 := make(map[string]int)              // make로 생성
	map5 := make(map[string]int, 10)          // make로 생성 (초기 용량 10)

	fmt.Printf("map1: %v (nil: %t)\n", map1, map1 == nil)
	fmt.Printf("map2: %v\n", map2)
	fmt.Printf("map3: %v\n", map3)
	fmt.Printf("map4: %v\n", map4)
	fmt.Printf("map5: %v\n", map5)

	// 맵 요소 접근과 수정
	fmt.Println("\n맵 요소 접근과 수정:")
	person := map[string]string{
		"name": "Alice",
		"age":  "25",
		"city": "Seoul",
	}
	fmt.Printf("원본: %v\n", person)

	// 요소 접근
	fmt.Printf("이름: %s\n", person["name"])
	fmt.Printf("나이: %s\n", person["age"])

	// 존재하지 않는 키 접근
	fmt.Printf("존재하지 않는 키: %s\n", person["job"])

	// 요소 수정
	person["age"] = "26"
	person["job"] = "Engineer"
	fmt.Printf("수정 후: %v\n", person)

	// 맵 크기
	fmt.Printf("맵 크기: %d\n", len(person))

	// 맵 비교 (직접 비교 불가)
	fmt.Println("\n맵 비교:")
	mapA := map[string]int{"a": 1, "b": 2}
	mapB := map[string]int{"a": 1, "b": 2}
	fmt.Printf("mapA == nil: %t\n", mapA == nil)
	fmt.Printf("mapB == nil: %t\n", mapB == nil)
	fmt.Printf("맵 직접 비교 불가 (컴파일 에러)\n")

	// 맵을 함수에 전달 (참조 전달)
	fmt.Println("\n맵을 함수에 전달:")
	modifyMap(person)
	fmt.Printf("수정된 맵: %v\n", person)
}

// mapOperations 함수는 맵 조작을 보여줍니다.
func mapOperations() {
	fmt.Println("\n📝 2. 맵 조작")
	fmt.Println("-------------")

	// 맵 요소 추가
	fmt.Println("맵 요소 추가:")
	scores := make(map[string]int)
	scores["Alice"] = 95
	scores["Bob"] = 87
	scores["Charlie"] = 92
	fmt.Printf("점수 맵: %v\n", scores)

	// 맵 요소 삭제
	fmt.Println("\n맵 요소 삭제:")
	delete(scores, "Bob")
	fmt.Printf("Bob 삭제 후: %v\n", scores)

	// 존재하지 않는 키 삭제 (에러 없음)
	delete(scores, "David")
	fmt.Printf("존재하지 않는 키 삭제 후: %v\n", scores)

	// 맵 요소 존재 확인
	fmt.Println("\n맵 요소 존재 확인:")

	// 방법 1: 두 값 할당
	if score, exists := scores["Alice"]; exists {
		fmt.Printf("Alice의 점수: %d\n", score)
	} else {
		fmt.Println("Alice의 점수가 없습니다")
	}

	if score, exists := scores["David"]; exists {
		fmt.Printf("David의 점수: %d\n", score)
	} else {
		fmt.Println("David의 점수가 없습니다")
	}

	// 방법 2: 제로값 확인 (주의: 값이 0인 경우와 키가 없는 경우 구분 불가)
	if score := scores["Alice"]; score != 0 {
		fmt.Printf("Alice의 점수 (제로값 확인): %d\n", score)
	} else {
		fmt.Println("Alice의 점수가 없거나 0입니다")
	}

	// 맵 복사
	fmt.Println("\n맵 복사:")
	original := map[string]int{"a": 1, "b": 2, "c": 3}

	// 얕은 복사 (참조 복사)
	shallowCopy := original
	shallowCopy["a"] = 100
	fmt.Printf("얕은 복사 후 원본: %v\n", original)
	original["a"] = 1 // 원본 복원

	// 깊은 복사
	deepCopy := make(map[string]int)
	for key, value := range original {
		deepCopy[key] = value
	}
	deepCopy["b"] = 200
	fmt.Printf("깊은 복사 후 원본: %v\n", original)
	fmt.Printf("깊은 복사본: %v\n", deepCopy)

	// 맵 병합
	fmt.Println("\n맵 병합:")
	map1 := map[string]int{"a": 1, "b": 2}
	map2 := map[string]int{"c": 3, "d": 4}

	merged := make(map[string]int)
	for key, value := range map1 {
		merged[key] = value
	}
	for key, value := range map2 {
		merged[key] = value
	}
	fmt.Printf("병합된 맵: %v\n", merged)

	// 맵 초기화
	fmt.Println("\n맵 초기화:")
	clear(merged)
	fmt.Printf("clear 후: %v\n", merged)

	// nil 맵에 요소 추가 (런타임 패닉)
	fmt.Println("\n주의: nil 맵에 요소 추가 시 패닉")
	var nilMap map[string]int
	fmt.Printf("nil 맵: %v\n", nilMap)
	// nilMap["key"] = 1 // 이 줄은 패닉을 일으킴
}

// mapBuiltins 함수는 맵 내장 함수를 보여줍니다.
func mapBuiltins() {
	fmt.Println("\n📝 3. 맵 내장 함수")
	fmt.Println("------------------")

	// len() - 맵 크기
	person := map[string]string{
		"name": "Alice",
		"age":  "25",
		"city": "Seoul",
	}
	fmt.Printf("len(person): %d\n", len(person))

	// delete() - 요소 삭제
	fmt.Println("\ndelete() 사용:")
	fmt.Printf("삭제 전: %v\n", person)
	delete(person, "age")
	fmt.Printf("age 삭제 후: %v\n", person)

	// clear() - 모든 요소 삭제 (Go 1.21+)
	fmt.Println("\nclear() 사용:")
	fmt.Printf("clear 전: %v\n", person)
	clear(person)
	fmt.Printf("clear 후: %v\n", person)

	// make() - 맵 생성
	fmt.Println("\nmake() 사용:")
	map1 := make(map[string]int)     // 기본 용량
	map2 := make(map[string]int, 10) // 초기 용량 10
	fmt.Printf("map1: %v\n", map1)
	fmt.Printf("map2: %v\n", map2)
}

// mapIteration 함수는 맵 순회를 보여줍니다.
func mapIteration() {
	fmt.Println("\n📝 4. 맵 순회")
	fmt.Println("-------------")

	// 기본 맵 순회 (순서는 보장되지 않음)
	fmt.Println("기본 맵 순회 (순서 무작위):")
	person := map[string]string{
		"name": "Alice",
		"age":  "25",
		"city": "Seoul",
		"job":  "Engineer",
	}

	for key, value := range person {
		fmt.Printf("%s: %s\n", key, value)
	}

	// 키만 순회
	fmt.Println("\n키만 순회:")
	for key := range person {
		fmt.Printf("키: %s\n", key)
	}

	// 값만 순회 (키 무시)
	fmt.Println("\n값만 순회:")
	for _, value := range person {
		fmt.Printf("값: %s\n", value)
	}

	// 정렬된 순서로 순회
	fmt.Println("\n정렬된 순서로 순회 (키 기준):")
	var keys []string
	for key := range person {
		keys = append(keys, key)
	}
	sort.Strings(keys)

	for _, key := range keys {
		fmt.Printf("%s: %s\n", key, person[key])
	}

	// 중첩된 맵 순회
	fmt.Println("\n중첩된 맵 순회:")
	students := map[string]map[string]string{
		"Alice": {
			"age":  "25",
			"city": "Seoul",
		},
		"Bob": {
			"age":  "30",
			"city": "Busan",
		},
	}

	for name, info := range students {
		fmt.Printf("학생: %s\n", name)
		for key, value := range info {
			fmt.Printf("  %s: %s\n", key, value)
		}
	}
}

// mapPatterns 함수는 맵 활용 패턴을 보여줍니다.
func mapPatterns() {
	fmt.Println("\n📝 5. 맵 활용 패턴")
	fmt.Println("------------------")

	// 카운터 패턴
	fmt.Println("카운터 패턴:")
	words := []string{"apple", "banana", "apple", "cherry", "banana", "apple"}
	counter := make(map[string]int)

	for _, word := range words {
		counter[word]++
	}
	fmt.Printf("단어 빈도: %v\n", counter)

	// 그룹화 패턴
	fmt.Println("\n그룹화 패턴:")
	people := []struct {
		Name string
		Age  int
		City string
	}{
		{"Alice", 25, "Seoul"},
		{"Bob", 30, "Busan"},
		{"Charlie", 25, "Seoul"},
		{"David", 35, "Busan"},
	}

	// 도시별로 그룹화
	cityGroups := make(map[string][]string)
	for _, person := range people {
		cityGroups[person.City] = append(cityGroups[person.City], person.Name)
	}
	fmt.Printf("도시별 그룹: %v\n", cityGroups)

	// 캐시 패턴 (재귀 함수)
	fmt.Println("\n캐시 패턴:")
	fibCache := make(map[int]int)

	// 피보나치 수열 계산 (메모이제이션)
	// *** FIX: 재귀 함수 리터럴을 사용하려면 변수를 먼저 선언해야 합니다. ***
	var fib func(n int) int
	fib = func(n int) int {
		if n <= 1 {
			return n
		}

		// 캐시 확인
		if result, exists := fibCache[n]; exists {
			return result
		}

		// 계산하고 캐시에 저장 (이제 fib가 정의되어 있으므로 재귀 호출 가능)
		result := fib(n-1) + fib(n-2)
		fibCache[n] = result
		return result
	}

	fmt.Printf("피보나치(10): %d\n", fib(10))
	fmt.Printf("피보나치(20): %d\n", fib(20))
	fmt.Printf("캐시 내용: %v\n", fibCache)

	// 설정 패턴
	fmt.Println("\n설정 패턴:")
	config := map[string]interface{}{
		"host":     "localhost",
		"port":     8080,
		"timeout":  30.5,
		"debug":    true,
		"features": []string{"auth", "logging", "caching"},
	}

	// 설정 값 추출
	if host, ok := config["host"].(string); ok {
		fmt.Printf("호스트: %s\n", host)
	}
	if port, ok := config["port"].(int); ok {
		fmt.Printf("포트: %d\n", port)
	}
	if timeout, ok := config["timeout"].(float64); ok {
		fmt.Printf("타임아웃: %.1f\n", timeout)
	}

	// 기본값 패턴
	fmt.Println("\n기본값 패턴:")
	userPrefs := map[string]string{
		"theme": "dark",
	}

	// 기본값과 함께 값 가져오기
	theme := getWithDefault(userPrefs, "theme", "light")
	language := getWithDefault(userPrefs, "language", "ko")
	fmt.Printf("테마: %s\n", theme)
	fmt.Printf("언어: %s\n", language)
}

// mapPerformance 함수는 맵 성능과 메모리를 보여줍니다.
func mapPerformance() {
	fmt.Println("\n📝 6. 맵 성능과 메모리")
	fmt.Println("----------------------")

	// 맵 초기 용량 설정의 중요성
	fmt.Println("맵 초기 용량 설정:")
	const numElements = 10000
	
	// 용량 없이 시작 (여러 번의 재할당 발생 가능)
	start1 := time.Now()
	smallCap := make(map[int]int)
	for i := 0; i < numElements; i++ {
		smallCap[i] = i
	}
	fmt.Printf("용량 미지정 시 소요 시간: %v\n", time.Since(start1))

	// 필요한 용량을 미리 할당
	start2 := time.Now()
	largeCap := make(map[int]int, numElements)
	for i := 0; i < numElements; i++ {
		largeCap[i] = i
	}
	fmt.Printf("용량 지정 시 소요 시간: %v\n", time.Since(start2))


	// 맵 메모리 해제
	fmt.Println("\n맵 메모리 해제:")
	largeMap := make(map[string]int, 100000)
	for i := 0; i < 100000; i++ {
		largeMap[fmt.Sprintf("key%d", i)] = i
	}
	fmt.Printf("대용량 맵 생성: %d 요소\n", len(largeMap))

	// 메모리를 가비지 컬렉터가 회수하도록 nil 할당
	largeMap = nil
	fmt.Printf("nil 할당 후: %v\n", largeMap)

	// 맵 재사용
	fmt.Println("\n맵 재사용:")
	reusable := make(map[string]int, 100)

	// 첫 번째 사용
	for i := 0; i < 10; i++ {
		reusable[fmt.Sprintf("key%d", i)] = i
	}
	fmt.Printf("첫 번째 사용: %v\n", reusable)

	// 재사용 (clear 사용, 새로 make하는 것보다 효율적)
	clear(reusable)
	for i := 10; i < 20; i++ {
		reusable[fmt.Sprintf("key%d", i)] = i
	}
	fmt.Printf("재사용 후: %v\n", reusable)

	// 맵 vs 슬라이스 성능 비교 (검색)
	fmt.Println("\n맵 vs 슬라이스 검색 성능 비교:")

	searchMap := make(map[string]int, numElements)
	for i := 0; i < numElements; i++ {
		searchMap[fmt.Sprintf("key%d", i)] = i
	}

	var searchSlice []string
	for i := 0; i < numElements; i++ {
		searchSlice = append(searchSlice, fmt.Sprintf("key%d", i))
	}

	target := "key9999"

	// 맵 검색 (O(1))
	if _, exists := searchMap[target]; exists {
		fmt.Printf("맵에서 '%s' 찾음 (시간 복잡도: O(1))\n", target)
	}

	// 슬라이스 검색 (O(n))
	for _, item := range searchSlice {
		if item == target {
			fmt.Printf("슬라이스에서 '%s' 찾음 (시간 복잡도: O(n))\n", target)
			break
		}
	}
}

// practicalMapExamples 함수는 실용적인 맵 예제를 보여줍니다.
func practicalMapExamples() {
	fmt.Println("\n📝 7. 실용적인 맵 예제")
	fmt.Println("----------------------")

	// 단어 빈도 분석
	fmt.Println("단어 빈도 분석:")
	text := "hello world hello go programming world go"
	words := strings.Fields(text)

	wordCount := make(map[string]int)
	for _, word := range words {
		wordCount[word]++
	}

	fmt.Printf("텍스트: \"%s\"\n", text)
	fmt.Printf("단어 빈도: %v\n", wordCount)

	// 가장 많이 나온 단어 찾기
	var maxWord string
	var maxCount int
	for word, count := range wordCount {
		if count > maxCount {
			maxWord = word
			maxCount = count
		}
	}
	fmt.Printf("가장 많이 나온 단어: '%s' (%d회)\n", maxWord, maxCount)

	// 사용자 세션 관리
	fmt.Println("\n사용자 세션 관리:")
	sessions := make(map[string]map[string]interface{})

	// 세션 생성
	sessions["user1"] = map[string]interface{}{
		"loginTime":  time.Now().Add(-2 * time.Hour),
		"lastActivity": time.Now().Add(-10 * time.Minute),
		"ip":         "192.168.1.100",
		"active":     true,
	}

	sessions["user2"] = map[string]interface{}{
		"loginTime":  time.Now().Add(-5 * time.Hour),
		"lastActivity": time.Now().Add(-3 * time.Hour),
		"ip":         "192.168.1.101",
		"active":     false,
	}

	fmt.Printf("활성 세션 수: %d\n", countActiveSessions(sessions))

	// 설정 관리
	fmt.Println("\n설정 관리:")
	config := createConfig()

	// 설정 값 가져오기
	dbHost := getConfigString(config, "database.host", "localhost")
	dbPort := getConfigInt(config, "database.port", 5432)
	debug := getConfigBool(config, "app.debug", false)

	fmt.Printf("데이터베이스: %s:%d\n", dbHost, dbPort)
	fmt.Printf("디버그 모드: %t\n", debug)
	fmt.Printf("API 키 (기본값 사용): %s\n", getConfigString(config, "api.key", "default-key"))


	// 캐시 구현
	fmt.Println("\n캐시 구현:")
	cache := make(map[string]cacheEntry)

	// 캐시에 데이터 저장
	setCache(cache, "user:1", "Alice", 5) // 5초 만료
	setCache(cache, "user:2", "Bob", 10)   // 10초 만료
	fmt.Printf("캐시 저장: user:1, user:2\n")

	// 캐시에서 데이터 가져오기
	if value, found := getCache(cache, "user:1"); found {
		fmt.Printf("캐시에서 가져오기 (user:1): %s\n", value)
	} else {
		fmt.Println("user:1이 캐시에 없거나 만료되었습니다.")
	}
	
	fmt.Println("6초 대기...")
	time.Sleep(6 * time.Second)

	// 6초 후 다시 가져오기
	if value, found := getCache(cache, "user:1"); found {
		fmt.Printf("캐시에서 가져오기 (user:1): %s\n", value)
	} else {
		fmt.Println("user:1이 캐시에 없거나 만료되었습니다.")
	}
	if value, found := getCache(cache, "user:2"); found {
		fmt.Printf("캐시에서 가져오기 (user:2): %s\n", value)
	} else {
		fmt.Println("user:2가 캐시에 없거나 만료되었습니다.")
	}


	// 만료된 캐시 정리
	cleanupCache(cache)
	fmt.Printf("정리 후 캐시 크기: %d\n", len(cache))
}

// mapFeatures 함수는 맵의 특징을 설명합니다.
func mapFeatures() {
	fmt.Println("\n📝 8. 맵의 특징과 장점")
	fmt.Println("----------------------")

	fmt.Println("✅ 맵(Map)의 주요 특징:")
	fmt.Println("  1. 키-값(Key-Value) 쌍으로 데이터 저장")
	fmt.Println("  2. 해시 테이블 기반 (평균 O(1) 시간 복잡도로 요소 접근)")
	fmt.Println("  3. 참조 타입 (함수에 전달 시 주소 복사)")
	fmt.Println("  4. 키는 비교 가능한(comparable) 타입이어야 함 (e.g., int, string, struct)")
	fmt.Println("  5. 순서가 보장되지 않음 (range 순회 시 무작위 순서)")
	fmt.Println("  6. nil 맵은 읽기만 가능 (쓰기 시 런타임 패닉 발생)")
	fmt.Println("  7. 동적 크기 (요소 추가 시 자동으로 크기 조절)")
	fmt.Println("  8. 직접 비교 불가 (== 연산자 사용 불가, nil과만 비교 가능)")
	fmt.Println("  9. 내장 함수: len(), delete(), clear()")
	fmt.Println("  10. range 키워드로 순회 가능")

	fmt.Println("\n✅ 맵의 장점:")
	fmt.Println("  1. 빠른 검색, 삽입, 삭제 (평균 O(1))")
	fmt.Println("  2. 유연한 데이터 구조 표현 가능")
	fmt.Println("  3. 데이터의 관계를 키-값으로 명확하게 표현")
	
	fmt.Println("\n✅ 맵의 사용 사례:")
	fmt.Println("  - 캐시 구현")
	fmt.Println("  - 설정(Configuration) 관리")
	fmt.Println("  - 데이터 카운팅 및 통계 (e.g., 단어 빈도수)")
	fmt.Println("  - 데이터 그룹화 및 분류")
	fmt.Println("  - 데이터의 존재 여부 빠른 확인 (Set처럼 활용)")
	fmt.Println("  - JSON 등 다른 데이터 형식과의 변환")
}

// --- 헬퍼 함수들 ---

// modifyMap은 맵을 인자로 받아 수정합니다. 맵은 참조 타입이므로 원본이 변경됩니다.
func modifyMap(m map[string]string) {
	m["modified"] = "true"
	fmt.Printf("함수 내부에서 수정: %v\n", m)
}

// getWithDefault는 맵에 키가 존재하면 해당 값을, 없으면 기본값을 반환합니다.
func getWithDefault(m map[string]string, key, defaultValue string) string {
	if value, exists := m[key]; exists {
		return value
	}
	return defaultValue
}

// countActiveSessions는 활성화된 세션의 수를 계산합니다.
func countActiveSessions(sessions map[string]map[string]interface{}) int {
	count := 0
	for _, session := range sessions {
		if active, ok := session["active"].(bool); ok && active {
			count++
		}
	}
	return count
}

// createConfig는 중첩된 맵으로 설정 예제를 생성합니다.
func createConfig() map[string]interface{} {
	return map[string]interface{}{
		"database": map[string]interface{}{
			"host": "db.example.com",
			"port": 5432,
			"user": "admin",
		},
		"app": map[string]interface{}{
			"debug": true,
			"name":  "My Awesome App",
		},
	}
}

// getConfigString은 중첩된 맵에서 .(점)으로 구분된 경로로 string 값을 안전하게 가져옵니다.
func getConfigString(config map[string]interface{}, path string, defaultValue string) string {
	keys := strings.Split(path, ".")
	current, ok := config[keys[0]]
	if !ok {
		return defaultValue
	}

	for i := 1; i < len(keys); i++ {
		if m, ok := current.(map[string]interface{}); ok {
			current, ok = m[keys[i]]
			if !ok {
				return defaultValue
			}
		} else {
			return defaultValue
		}
	}

	if value, ok := current.(string); ok {
		return value
	}

	return defaultValue
}

// getConfigInt는 중첩된 맵에서 .(점)으로 구분된 경로로 int 값을 안전하게 가져옵니다.
func getConfigInt(config map[string]interface{}, path string, defaultValue int) int {
	keys := strings.Split(path, ".")
	current, ok := config[keys[0]]
	if !ok {
		return defaultValue
	}
	
	for i := 1; i < len(keys); i++ {
		if m, ok := current.(map[string]interface{}); ok {
			current, ok = m[keys[i]]
			if !ok {
				return defaultValue
			}
		} else {
			return defaultValue
		}
	}
	
	if value, ok := current.(int); ok {
		return value
	}
	
	return defaultValue
}

// getConfigBool은 중첩된 맵에서 .(점)으로 구분된 경로로 bool 값을 안전하게 가져옵니다.
func getConfigBool(config map[string]interface{}, path string, defaultValue bool) bool {
	keys := strings.Split(path, ".")
	current, ok := config[keys[0]]
	if !ok {
		return defaultValue
	}

	for i := 1; i < len(keys); i++ {
		if m, ok := current.(map[string]interface{}); ok {
			current, ok = m[keys[i]]
			if !ok {
				return defaultValue
			}
		} else {
			return defaultValue
		}
	}

	if value, ok := current.(bool); ok {
		return value
	}

	return defaultValue
}


// cacheEntry는 캐시 값과 만료 시간을 저장하는 구조체입니다.
type cacheEntry struct {
	value      string
	expiration int64 // Unix timestamp
}

// setCache는 캐시에 키-값 쌍을 저장하고 만료 시간을 설정합니다.
func setCache(cache map[string]cacheEntry, key, value string, ttlSeconds int) {
	expiration := time.Now().Unix() + int64(ttlSeconds)
	cache[key] = cacheEntry{
		value:      value,
		expiration: expiration,
	}
}

// getCache는 캐시에서 만료되지 않은 값을 가져옵니다. 만료된 경우 값을 삭제합니다.
func getCache(cache map[string]cacheEntry, key string) (string, bool) {
	entry, exists := cache[key]
	if !exists {
		return "", false
	}

	if time.Now().Unix() >= entry.expiration {
		// 만료된 항목 삭제
		delete(cache, key)
		return "", false
	}
	
	return entry.value, true
}

// cleanupCache는 캐시에서 만료된 모든 항목을 정리합니다.
func cleanupCache(cache map[string]cacheEntry) {
	now := time.Now().Unix()
	for key, entry := range cache {
		if now >= entry.expiration {
			delete(cache, key)
		}
	}
}
