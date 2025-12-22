package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// 행성계 구조체 정의
type Planet struct {
	cx, cy, r int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	// 테스트 케이스 수 입력
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text())

	for t := 0; t < T; t++ {
		// 출발점과 도착점 입력
		scanner.Scan()
		points := strings.Fields(scanner.Text())
		x1, _ := strconv.Atoi(points[0])
		y1, _ := strconv.Atoi(points[1])
		x2, _ := strconv.Atoi(points[2])
		y2, _ := strconv.Atoi(points[3])

		// 행성계 개수 입력
		scanner.Scan()
		n, _ := strconv.Atoi(scanner.Text())

		planets := make([]Planet, n)

		// 행성계 정보 입력
		for i := 0; i < n; i++ {
			scanner.Scan()
			planetData := strings.Fields(scanner.Text())
			cx, _ := strconv.Atoi(planetData[0])
			cy, _ := strconv.Atoi(planetData[1])
			r, _ := strconv.Atoi(planetData[2])
			planets[i] = Planet{cx, cy, r}
		}

		// 최소 진입/이탈 횟수 계산
		result := 0
		for _, planet := range planets {
			startInside := isInside(x1, y1, planet)
			endInside := isInside(x2, y2, planet)
			if startInside != endInside {
				result++
			}
		}
		fmt.Fprintln(writer, result)
	}
}

// 점이 행성계 내부에 있는지 여부 확인
func isInside(x, y int, planet Planet) bool {
	distance := math.Sqrt(float64((x-planet.cx)*(x-planet.cx) + (y-planet.cy)*(y-planet.cy)))
	return distance < float64(planet.r)
}