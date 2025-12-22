package main

import (
	"fmt" // 표준 입출력을 위한 패키지
)

func add(a int, b int) int {
	return a + b
}

func main() {

	var a, b int
	fmt.Scanln(&a, &b)
	
	sum := add(a, b) // add 함수 호출
	fmt.Println(sum)
}

/*
package main
 
import "fmt"
 
func main() {
    var a, b int
    fmt.Scanf("%d %d", &a, &b)
    fmt.Printf("%d\n", a+b)
}
*/