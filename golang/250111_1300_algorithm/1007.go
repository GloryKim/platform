package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// 점 구조체 정의
type Point struct {
	x, y int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	// 테스트 케이스 수 입력
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text())

	for t := 0; t < T; t++ {
		// 점의 개수 입력
		scanner.Scan()
		N, _ := strconv.Atoi(scanner.Text())

		points := make([]Point, N)

		// 점 좌표 입력
		for i := 0; i < N; i++ {
			scanner.Scan()
			coords := strings.Fields(scanner.Text())
			x, _ := strconv.Atoi(coords[0])
			y, _ := strconv.Atoi(coords[1])
			points[i] = Point{x, y}
		}

		// 최소 벡터 합 길이 계산
		result := calculateMinVectorSum(points, N)
		fmt.Fprintf(writer, "%.12f\n", result)
	}
}

// 최소 벡터 합 길이 계산 함수
func calculateMinVectorSum(points []Point, N int) float64 {
	sumX, sumY := 0, 0
	for _, point := range points {
		sumX += point.x
		sumY += point.y
	}

	// DFS를 통해 조합 탐색
	visited := make([]bool, N)
	return findMinDifference(points, visited, 0, N/2, sumX, sumY)
}

// DFS를 이용하여 최소 차이 계산
func findMinDifference(points []Point, visited []bool, idx, remain, sumX, sumY int) float64 {
	if remain == 0 {
		x, y := 0, 0
		for i, v := range visited {
			if v {
				x += points[i].x
				y += points[i].y
			}
		}
		restX, restY := sumX-x, sumY-y
		return math.Sqrt(float64((restX-x)*(restX-x) + (restY-y)*(restY-y)))
	}

	if idx >= len(points) {
		return math.MaxFloat64
	}

	// 점 선택
	visited[idx] = true
	include := findMinDifference(points, visited, idx+1, remain-1, sumX, sumY)
	visited[idx] = false

	// 점 선택 안 함
	exclude := findMinDifference(points, visited, idx+1, remain, sumX, sumY)

	return math.Min(include, exclude)
}


/*
//1차
package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// 점 구조체 정의
type Point struct {
	x, y int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	// 테스트 케이스 수 입력
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text())

	for t := 0; t < T; t++ {
		// 점의 개수 입력
		scanner.Scan()
		N, _ := strconv.Atoi(scanner.Text())

		points := make([]Point, N)

		// 점 좌표 입력
		for i := 0; i < N; i++ {
			scanner.Scan()
			coords := strings.Fields(scanner.Text())
			x, _ := strconv.Atoi(coords[0])
			y, _ := strconv.Atoi(coords[1])
			points[i] = Point{x, y}
		}

		// 최소 벡터 합 길이 계산
		result := calculateMinVectorSum(points, N)
		fmt.Fprintf(writer, "%.12f\n", result)
	}
}

// 최소 벡터 합 길이 계산 함수
func calculateMinVectorSum(points []Point, N int) float64 {
	sumX, sumY := 0, 0
	for _, point := range points {
		sumX += point.x
		sumY += point.y
	}

	// DFS를 통해 조합 탐색
	visited := make([]bool, N)
	return findMinDifference(points, visited, 0, N/2, sumX, sumY)
}

// DFS를 이용하여 최소 차이 계산
func findMinDifference(points []Point, visited []bool, idx, remain, sumX, sumY int) float64 {
	if remain == 0 {
		x, y := 0, 0
		for i, v := range visited {
			if v {
				x += points[i].x
				y += points[i].y
			}
		}
		restX, restY := sumX-x, sumY-y
		return math.Sqrt(float64((restX-x)*(restX-x) + (restY-y)*(restY-y)))
	}

	if idx >= len(points) {
		return math.MaxFloat64
	}

	// 점 선택
	visited[idx] = true
	include := findMinDifference(points, visited, idx+1, remain-1, sumX, sumY)
	visited[idx] = false

	// 점 선택 안 함
	exclude := findMinDifference(points, visited, idx+1, remain, sumX, sumY)

	return math.Min(include, exclude)
}

package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// 점 구조체 정의
type Point struct {
	x, y int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	// 테스트 케이스 수 입력
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text())

	for t := 0; t < T; t++ {
		// 점의 개수 입력
		scanner.Scan()
		N, _ := strconv.Atoi(scanner.Text())

		points := make([]Point, N)

		// 점 좌표 입력
		for i := 0; i < N; i++ {
			scanner.Scan()
			coords := strings.Fields(scanner.Text())
			x, _ := strconv.Atoi(coords[0])
			y, _ := strconv.Atoi(coords[1])
			points[i] = Point{x, y}
		}

		// 최소 벡터 합 길이 계산
		result := calculateMinVectorSum(points, N)
		fmt.Fprintf(writer, "%.12f\n", result)
	}
}

// 최소 벡터 합 길이 계산 함수
func calculateMinVectorSum(points []Point, N int) float64 {
	sumX, sumY := 0, 0
	for _, point := range points {
		sumX += point.x
		sumY += point.y
	}

	// DFS를 통해 조합 탐색
	visited := make([]bool, N)
	return findMinDifference(points, visited, 0, N/2, sumX, sumY)
}

// DFS를 이용하여 최소 차이 계산
func findMinDifference(points []Point, visited []bool, idx, remain, sumX, sumY int) float64 {
	if remain == 0 {
		x, y := 0, 0
		for i, v := range visited {
			if v {
				x += points[i].x
				y += points[i].y
			}
		}
		restX, restY := sumX-x, sumY-y
		return math.Sqrt(float64((restX-x)*(restX-x) + (restY-y)*(restY-y)))
	}

	if idx >= len(points) {
		return math.MaxFloat64
	}

	// 점 선택
	visited[idx] = true
	include := findMinDifference(points, visited, idx+1, remain-1, sumX, sumY)
	visited[idx] = false

	// 점 선택 안 함
	exclude := findMinDifference(points, visited, idx+1, remain, sumX, sumY)

	return math.Min(include, exclude)
}

*/