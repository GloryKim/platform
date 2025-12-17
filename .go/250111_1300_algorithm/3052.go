package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var numbers [10]int
	for i := 0; i < 10; i++ {
		fmt.Fscan(in, &numbers[i])
	}

	remainders := make(map[int]bool)
	for _, number := range numbers {
		remainder := number % 42
		remainders[remainder] = true
	}

	fmt.Fprintln(out, len(remainders))
}