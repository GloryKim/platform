package main

import (
	"fmt"
	"sort"
)

// Go 언어의 배열과 슬라이스 완전 가이드
func main() {
	fmt.Println("📊 Go 언어 배열과 슬라이스 완전 가이드")
	fmt.Println("=====================================")

	// 1. 배열 (Array)
	arrays()
	
	// 2. 슬라이스 (Slice)
	slices()
	
	// 3. 슬라이스 조작
	sliceOperations()
	
	// 4. 슬라이스 내장 함수
	sliceBuiltins()
	
	// 5. 다차원 배열과 슬라이스
	multiDimensional()
	
	// 6. 슬라이스 성능과 메모리
	slicePerformance()
	
	// 7. 실용적인 슬라이스 패턴
	practicalSlicePatterns()
	
	// 8. 배열과 슬라이스의 차이점
	arrayVsSlice()
}

// arrays 함수는 배열의 기본 사용법을 보여줍니다.
func arrays() {
	fmt.Println("\n📝 1. 배열 (Array)")
	fmt.Println("------------------")

	// 배열 선언 방법들
	var arr1 [5]int                    // 제로값으로 초기화
	var arr2 = [5]int{1, 2, 3, 4, 5}   // 리터럴로 초기화
	arr3 := [5]int{1, 2, 3, 4, 5}      // 단축 선언
	arr4 := [...]int{1, 2, 3, 4, 5}    // 크기 자동 추론
	
	// 특정 인덱스만 초기화
	arr5 := [5]int{1: 10, 3: 30}
	
	fmt.Printf("arr1: %v (크기: %d)\n", arr1, len(arr1))
	fmt.Printf("arr2: %v (크기: %d)\n", arr2, len(arr2))
	fmt.Printf("arr3: %v (크기: %d)\n", arr3, len(arr3))
	fmt.Printf("arr4: %v (크기: %d)\n", arr4, len(arr4))
	fmt.Printf("arr5: %v (크기: %d)\n", arr5, len(arr5))
	
	// 배열 요소 접근과 수정
	fmt.Println("\n배열 요소 접근과 수정:")
	arr := [5]int{1, 2, 3, 4, 5}
	fmt.Printf("원본: %v\n", arr)
	
	// 요소 접근
	fmt.Printf("첫 번째 요소: %d\n", arr[0])
	fmt.Printf("마지막 요소: %d\n", arr[len(arr)-1])
	
	// 요소 수정
	arr[0] = 100
	arr[4] = 500
	fmt.Printf("수정 후: %v\n", arr)
	
	// 배열 순회
	fmt.Println("\n배열 순회:")
	
	// 인덱스와 값 모두 사용
	for i, v := range arr {
		fmt.Printf("인덱스 %d: 값 %d\n", i, v)
	}
	
	// 인덱스만 사용
	for i := range arr {
		fmt.Printf("인덱스 %d\n", i)
	}
	
	// 값만 사용
	for _, v := range arr {
		fmt.Printf("값 %d\n", v)
	}
	
	// 전통적인 for 루프
	for i := 0; i < len(arr); i++ {
		fmt.Printf("arr[%d] = %d\n", i, arr[i])
	}
	
	// 배열 비교
	fmt.Println("\n배열 비교:")
	arrA := [3]int{1, 2, 3}
	arrB := [3]int{1, 2, 3}
	arrC := [3]int{1, 2, 4}
	
	fmt.Printf("arrA == arrB: %t\n", arrA == arrB)
	fmt.Printf("arrA == arrC: %t\n", arrA == arrC)
	
	// 배열을 함수에 전달 (값 복사)
	fmt.Println("\n배열을 함수에 전달:")
	modifyArray(arr)
	fmt.Printf("원본 배열 (변경되지 않음): %v\n", arr)
	
	// 배열을 포인터로 전달
	modifyArrayByPointer(&arr)
	fmt.Printf("포인터로 수정된 배열: %v\n", arr)
}

// slices 함수는 슬라이스의 기본 사용법을 보여줍니다.
func slices() {
	fmt.Println("\n📝 2. 슬라이스 (Slice)")
	fmt.Println("----------------------")

	// 슬라이스 선언 방법들
	var slice1 []int                    // nil 슬라이스
	var slice2 = []int{1, 2, 3, 4, 5}   // 리터럴로 초기화
	slice3 := []int{1, 2, 3, 4, 5}      // 단축 선언
	slice4 := make([]int, 5)            // make로 생성 (길이 5)
	slice5 := make([]int, 5, 10)        // make로 생성 (길이 5, 용량 10)
	
	fmt.Printf("slice1: %v (길이: %d, 용량: %d, nil: %t)\n", 
		slice1, len(slice1), cap(slice1), slice1 == nil)
	fmt.Printf("slice2: %v (길이: %d, 용량: %d)\n", 
		slice2, len(slice2), cap(slice2))
	fmt.Printf("slice3: %v (길이: %d, 용량: %d)\n", 
		slice3, len(slice3), cap(slice3))
	fmt.Printf("slice4: %v (길이: %d, 용량: %d)\n", 
		slice4, len(slice4), cap(slice4))
	fmt.Printf("slice5: %v (길이: %d, 용량: %d)\n", 
		slice5, len(slice5), cap(slice5))
	
	// 슬라이스 요소 접근과 수정
	fmt.Println("\n슬라이스 요소 접근과 수정:")
	slice := []int{1, 2, 3, 4, 5}
	fmt.Printf("원본: %v\n", slice)
	
	// 요소 접근
	if len(slice) > 0 {
		fmt.Printf("첫 번째 요소: %d\n", slice[0])
		fmt.Printf("마지막 요소: %d\n", slice[len(slice)-1])
	}
	
	// 요소 수정
	slice[0] = 100
	slice[len(slice)-1] = 500
	fmt.Printf("수정 후: %v\n", slice)
	
	// 슬라이스 순회
	fmt.Println("\n슬라이스 순회:")
	
	// 인덱스와 값 모두 사용
	for i, v := range slice {
		fmt.Printf("인덱스 %d: 값 %d\n", i, v)
	}
	
	// 슬라이스 비교 (직접 비교 불가)
	fmt.Println("\n슬라이스 비교:")
	sliceA := []int{1, 2, 3}
	sliceB := []int{1, 2, 3}
	
	fmt.Printf("sliceA == nil: %t\n", sliceA == nil)
	fmt.Printf("sliceB == nil: %t\n", sliceB == nil)
	fmt.Printf("슬라이스 직접 비교 불가 (컴파일 에러)\n")
	
	// 슬라이스를 함수에 전달 (참조 전달)
	fmt.Println("\n슬라이스를 함수에 전달:")
	modifySlice(slice)
	fmt.Printf("수정된 슬라이스: %v\n", slice)
	
	// 슬라이스 복사
	fmt.Println("\n슬라이스 복사:")
	original := []int{1, 2, 3, 4, 5}
	
	// 얕은 복사 (참조 복사)
	shallowCopy := original
	shallowCopy[0] = 100
	fmt.Printf("얕은 복사 후 원본: %v\n", original)
	
	// 깊은 복사
	deepCopy := make([]int, len(original))
	copy(deepCopy, original)
	deepCopy[1] = 200
	fmt.Printf("깊은 복사 후 원본: %v\n", original)
	fmt.Printf("깊은 복사본: %v\n", deepCopy)
}

// sliceOperations 함수는 슬라이스 조작을 보여줍니다.
func sliceOperations() {
	fmt.Println("\n📝 3. 슬라이스 조작")
	fmt.Println("-------------------")

	// 슬라이스 추가 (append)
	fmt.Println("슬라이스 추가:")
	slice := []int{1, 2, 3}
	fmt.Printf("원본: %v (길이: %d, 용량: %d)\n", slice, len(slice), cap(slice))
	
	// 단일 요소 추가
	slice = append(slice, 4)
	fmt.Printf("4 추가: %v (길이: %d, 용량: %d)\n", slice, len(slice), cap(slice))
	
	// 여러 요소 추가
	slice = append(slice, 5, 6, 7)
	fmt.Printf("5,6,7 추가: %v (길이: %d, 용량: %d)\n", slice, len(slice), cap(slice))
	
	// 다른 슬라이스 추가
	otherSlice := []int{8, 9, 10}
	slice = append(slice, otherSlice...)
	fmt.Printf("다른 슬라이스 추가: %v (길이: %d, 용량: %d)\n", slice, len(slice), cap(slice))
	
	// 슬라이스 자르기 (slicing)
	fmt.Println("\n슬라이스 자르기:")
	numbers := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	fmt.Printf("원본: %v\n", numbers)
	
	// 기본 자르기
	slice1 := numbers[2:5]  // 인덱스 2부터 4까지 (5 미포함)
	fmt.Printf("numbers[2:5]: %v\n", slice1)
	
	// 시작 인덱스 생략
	slice2 := numbers[:5]   // 처음부터 인덱스 4까지
	fmt.Printf("numbers[:5]: %v\n", slice2)
	
	// 끝 인덱스 생략
	slice3 := numbers[5:]   // 인덱스 5부터 끝까지
	fmt.Printf("numbers[5:]: %v\n", slice3)
	
	// 전체 슬라이스
	slice4 := numbers[:]    // 전체
	fmt.Printf("numbers[:]: %v\n", slice4)
	
	// 슬라이스와 용량
	fmt.Println("\n슬라이스와 용량:")
	original := make([]int, 5, 10)
	for i := range original {
		original[i] = i
	}
	fmt.Printf("원본: %v (길이: %d, 용량: %d)\n", original, len(original), cap(original))
	
	// 부분 슬라이스
	partial := original[1:3]
	fmt.Printf("partial[1:3]: %v (길이: %d, 용량: %d)\n", partial, len(partial), cap(partial))
	
	// 슬라이스 삭제
	fmt.Println("\n슬라이스 삭제:")
	sliceToDelete := []int{1, 2, 3, 4, 5}
	fmt.Printf("삭제 전: %v\n", sliceToDelete)
	
	// 인덱스 2 삭제
	sliceToDelete = append(sliceToDelete[:2], sliceToDelete[3:]...)
	fmt.Printf("인덱스 2 삭제 후: %v\n", sliceToDelete)
	
	// 슬라이스 삽입
	fmt.Println("\n슬라이스 삽입:")
	sliceToInsert := []int{1, 2, 4, 5}
	fmt.Printf("삽입 전: %v\n", sliceToInsert)
	
	// 인덱스 2에 3 삽입
	sliceToInsert = append(sliceToInsert[:2], append([]int{3}, sliceToInsert[2:]...)...)
	fmt.Printf("인덱스 2에 3 삽입 후: %v\n", sliceToInsert)
}

// sliceBuiltins 함수는 슬라이스 내장 함수를 보여줍니다.
func sliceBuiltins() {
	fmt.Println("\n📝 4. 슬라이스 내장 함수")
	fmt.Println("------------------------")

	// len() - 길이
	slice := []int{1, 2, 3, 4, 5}
	fmt.Printf("len(slice): %d\n", len(slice))
	
	// cap() - 용량
	fmt.Printf("cap(slice): %d\n", cap(slice))
	
	// append() - 요소 추가
	fmt.Println("\nappend() 사용:")
	slice = append(slice, 6)
	fmt.Printf("append 후: %v\n", slice)
	
	// copy() - 슬라이스 복사
	fmt.Println("\ncopy() 사용:")
	source := []int{10, 20, 30, 40, 50}
	dest := make([]int, 3)
	copied := copy(dest, source)
	fmt.Printf("복사된 요소 수: %d\n", copied)
	fmt.Printf("대상 슬라이스: %v\n", dest)
	
	// make() - 슬라이스 생성
	fmt.Println("\nmake() 사용:")
	slice1 := make([]int, 5)     // 길이 5, 용량 5
	slice2 := make([]int, 5, 10) // 길이 5, 용량 10
	fmt.Printf("slice1: %v (길이: %d, 용량: %d)\n", slice1, len(slice1), cap(slice1))
	fmt.Printf("slice2: %v (길이: %d, 용량: %d)\n", slice2, len(slice2), cap(slice2))
	
	// 슬라이스 정렬
	fmt.Println("\n슬라이스 정렬:")
	unsorted := []int{3, 1, 4, 1, 5, 9, 2, 6}
	fmt.Printf("정렬 전: %v\n", unsorted)
	sort.Ints(unsorted)
	fmt.Printf("정렬 후: %v\n", unsorted)
	
	// 슬라이스 검색
	fmt.Println("\n슬라이스 검색:")
	sorted := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	target := 5
	index := sort.SearchInts(sorted, target)
	if index < len(sorted) && sorted[index] == target {
		fmt.Printf("%d을(를) 인덱스 %d에서 찾았습니다.\n", target, index)
	} else {
		fmt.Printf("%d을(를) 찾을 수 없습니다.\n", target)
	}
}

// multiDimensional 함수는 다차원 배열과 슬라이스를 보여줍니다.
func multiDimensional() {
	fmt.Println("\n📝 5. 다차원 배열과 슬라이스")
	fmt.Println("----------------------------")

	// 2차원 배열
	fmt.Println("2차원 배열:")
	var matrix [3][3]int
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			matrix[i][j] = i*3 + j + 1
		}
	}
	
	fmt.Println("2차원 배열 출력:")
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			fmt.Printf("%d ", matrix[i][j])
		}
		fmt.Println()
	}
	
	// 2차원 슬라이스
	fmt.Println("\n2차원 슬라이스:")
	rows, cols := 3, 4
	slice2D := make([][]int, rows)
	for i := range slice2D {
		slice2D[i] = make([]int, cols)
		for j := range slice2D[i] {
			slice2D[i][j] = i*cols + j + 1
		}
	}
	
	fmt.Println("2차원 슬라이스 출력:")
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			fmt.Printf("%2d ", slice2D[i][j])
		}
		fmt.Println()
	}
	
	// 불규칙한 2차원 슬라이스 (jagged array)
	fmt.Println("\n불규칙한 2차원 슬라이스:")
	jagged := make([][]int, 3)
	jagged[0] = []int{1, 2, 3}
	jagged[1] = []int{4, 5}
	jagged[2] = []int{6, 7, 8, 9}
	
	for i, row := range jagged {
		fmt.Printf("행 %d: %v\n", i, row)
	}
	
	// 3차원 슬라이스
	fmt.Println("\n3차원 슬라이스:")
	depth, height, width := 2, 3, 4
	slice3D := make([][][]int, depth)
	for i := range slice3D {
		slice3D[i] = make([][]int, height)
		for j := range slice3D[i] {
			slice3D[i][j] = make([]int, width)
			for k := range slice3D[i][j] {
				slice3D[i][j][k] = i*height*width + j*width + k + 1
			}
		}
	}
	
	fmt.Println("3차원 슬라이스 출력:")
	for i := 0; i < depth; i++ {
		fmt.Printf("깊이 %d:\n", i)
		for j := 0; j < height; j++ {
			for k := 0; k < width; k++ {
				fmt.Printf("%2d ", slice3D[i][j][k])
			}
			fmt.Println()
		}
		fmt.Println()
	}
}

// slicePerformance 함수는 슬라이스 성능과 메모리 관리를 보여줍니다.
func slicePerformance() {
	fmt.Println("\n📝 6. 슬라이스 성능과 메모리")
	fmt.Println("---------------------------")

	// 슬라이스 용량 증가 패턴
	fmt.Println("슬라이스 용량 증가 패턴:")
	slice := make([]int, 0, 1)
	fmt.Printf("초기: 길이=%d, 용량=%d\n", len(slice), cap(slice))
	
	for i := 0; i < 10; i++ {
		slice = append(slice, i)
		fmt.Printf("추가 %d: 길이=%d, 용량=%d\n", i, len(slice), cap(slice))
	}
	
	// 사전 할당으로 성능 최적화
	fmt.Println("\n사전 할당으로 성능 최적화:")
	
	// 비효율적인 방법
	inefficient := make([]int, 0)
	for i := 0; i < 1000; i++ {
		inefficient = append(inefficient, i)
	}
	fmt.Printf("비효율적: 최종 용량=%d\n", cap(inefficient))
	
	// 효율적인 방법
	efficient := make([]int, 0, 1000)
	for i := 0; i < 1000; i++ {
		efficient = append(efficient, i)
	}
	fmt.Printf("효율적: 최종 용량=%d\n", cap(efficient))
	
	// 슬라이스 메모리 해제
	fmt.Println("\n슬라이스 메모리 해제:")
	largeSlice := make([]int, 1000000)
	fmt.Printf("대용량 슬라이스 생성: 길이=%d, 용량=%d\n", len(largeSlice), cap(largeSlice))
	
	// 메모리 해제
	largeSlice = nil
	fmt.Printf("nil 할당 후: 길이=%d, 용량=%d\n", len(largeSlice), cap(largeSlice))
	
	// 슬라이스 재사용
	fmt.Println("\n슬라이스 재사용:")
	reusable := make([]int, 0, 100)
	
	// 첫 번째 사용
	for i := 0; i < 10; i++ {
		reusable = append(reusable, i)
	}
	fmt.Printf("첫 번째 사용: %v\n", reusable)
	
	// 재사용 (길이만 0으로)
	reusable = reusable[:0]
	for i := 10; i < 20; i++ {
		reusable = append(reusable, i)
	}
	fmt.Printf("재사용 후: %v\n", reusable)
}

// practicalSlicePatterns 함수는 실용적인 슬라이스 패턴을 보여줍니다.
func practicalSlicePatterns() {
	fmt.Println("\n📝 7. 실용적인 슬라이스 패턴")
	fmt.Println("----------------------------")

	// 슬라이스 필터링
	fmt.Println("슬라이스 필터링:")
	numbers := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	
	// 짝수만 필터링
	var evens []int
	for _, num := range numbers {
		if num%2 == 0 {
			evens = append(evens, num)
		}
	}
	fmt.Printf("짝수만: %v\n", evens)
	
	// 슬라이스 매핑
	fmt.Println("\n슬라이스 매핑:")
	var squares []int
	for _, num := range numbers {
		squares = append(squares, num*num)
	}
	fmt.Printf("제곱: %v\n", squares)
	
	// 슬라이스 축약 (reduce)
	fmt.Println("\n슬라이스 축약:")
	sum := 0
	for _, num := range numbers {
		sum += num
	}
	fmt.Printf("합계: %d\n", sum)
	
	// 슬라이스 중복 제거
	fmt.Println("\n슬라이스 중복 제거:")
	duplicates := []int{1, 2, 2, 3, 3, 3, 4, 5, 5}
	unique := removeDuplicates(duplicates)
	fmt.Printf("원본: %v\n", duplicates)
	fmt.Printf("중복 제거: %v\n", unique)
	
	// 슬라이스 회전
	fmt.Println("\n슬라이스 회전:")
	original := []int{1, 2, 3, 4, 5}
	rotated := rotateSlice(original, 2)
	fmt.Printf("원본: %v\n", original)
	fmt.Printf("2칸 회전: %v\n", rotated)
	
	// 슬라이스 배치 처리
	fmt.Println("\n슬라이스 배치 처리:")
	data := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	batchSize := 3
	batches := processInBatches(data, batchSize)
	for i, batch := range batches {
		fmt.Printf("배치 %d: %v\n", i+1, batch)
	}
}

// arrayVsSlice 함수는 배열과 슬라이스의 차이점을 보여줍니다.
func arrayVsSlice() {
	fmt.Println("\n📝 8. 배열과 슬라이스의 차이점")
	fmt.Println("----------------------------")

	fmt.Println("✅ 배열 (Array)의 특징:")
	fmt.Println("  1. 고정 크기 (선언 시 크기가 결정됨)")
	fmt.Println("  2. 값 타입 (함수에 전달 시 복사됨)")
	fmt.Println("  3. 크기가 타입의 일부 (다른 크기는 다른 타입)")
	fmt.Println("  4. 직접 비교 가능 (==, !=")
	fmt.Println("  5. 메모리에 연속적으로 저장")
	
	fmt.Println("\n✅ 슬라이스 (Slice)의 특징:")
	fmt.Println("  1. 동적 크기 (런타임에 크기 변경 가능)")
	fmt.Println("  2. 참조 타입 (함수에 전달 시 참조 전달)")
	fmt.Println("  3. 크기가 타입의 일부가 아님")
	fmt.Println("  4. 직접 비교 불가 (nil과만 비교 가능)")
	fmt.Println("  5. 내부적으로 배열을 참조")
	
	// 실제 예제로 차이점 보여주기
	fmt.Println("\n실제 차이점 예제:")
	
	// 배열 예제
	arr1 := [3]int{1, 2, 3}
	arr2 := [3]int{1, 2, 3}
	fmt.Printf("배열 비교: arr1 == arr2 = %t\n", arr1 == arr2)
	
	// 슬라이스 예제
	slice1 := []int{1, 2, 3}
	slice2 := []int{1, 2, 3}
	fmt.Printf("슬라이스 nil 비교: slice1 == nil = %t\n", slice1 == nil)
	fmt.Printf("슬라이스 nil 비교: slice2 == nil = %t\n", slice2 == nil)
	fmt.Printf("슬라이스 직접 비교 불가 (컴파일 에러)\n")
	
	// 함수 전달 차이점
	fmt.Println("\n함수 전달 차이점:")
	
	// 배열 전달 (값 복사)
	array := [5]int{1, 2, 3, 4, 5} // 250705_1913_glory : 타입 불일치 오류 수정: modifyArray 함수가 [5]int 타입을 기대하는데 [3]int 타입을 전달하던 문제를 해결
	fmt.Printf("함수 호출 전 배열: %v\n", array)
	modifyArray(array)
	fmt.Printf("함수 호출 후 배열 (변경되지 않음): %v\n", array)
	
	// 슬라이스 전달 (참조 전달)
	slice := []int{1, 2, 3}
	fmt.Printf("함수 호출 전 슬라이스: %v\n", slice)
	modifySlice(slice)
	fmt.Printf("함수 호출 후 슬라이스 (변경됨): %v\n", slice)
}

// 헬퍼 함수들

func modifyArray(arr [5]int) {
	arr[0] = 999
	fmt.Printf("함수 내부 배열: %v\n", arr)
}

func modifyArrayByPointer(arr *[5]int) {
	arr[0] = 999
	fmt.Printf("함수 내부 배열 (포인터): %v\n", *arr)
}

func modifySlice(slice []int) {
	if len(slice) > 0 {
		slice[0] = 999
	}
	fmt.Printf("함수 내부 슬라이스: %v\n", slice)
}

func removeDuplicates(slice []int) []int {
	seen := make(map[int]bool)
	var result []int
	
	for _, item := range slice {
		if !seen[item] {
			seen[item] = true
			result = append(result, item)
		}
	}
	
	return result
}

func rotateSlice(slice []int, positions int) []int {
	length := len(slice)
	if length == 0 {
		return slice
	}
	
	positions = positions % length
	if positions < 0 {
		positions += length
	}
	
	result := make([]int, length)
	for i := 0; i < length; i++ {
		newIndex := (i + positions) % length
		result[newIndex] = slice[i]
	}
	
	return result
}

func processInBatches(data []int, batchSize int) [][]int {
	var batches [][]int
	
	for i := 0; i < len(data); i += batchSize {
		end := i + batchSize
		if end > len(data) {
			end = len(data)
		}
		batches = append(batches, data[i:end])
	}
	
	return batches
} 