package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var n int
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	fmt.Fscan(reader, &n)
	minVal, maxVal := 1000001, -1000001

	for i := 0; i < n; i++ {
		var num int
		fmt.Fscan(reader, &num)

		if minVal > num {
			minVal = num
		}

		if maxVal < num {
			maxVal = num
		}
	}

	writer.WriteString(fmt.Sprintf("%d %d\n", minVal, maxVal))
}