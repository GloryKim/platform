package main

import (
	"fmt"
)

func main() {
	var N, L int
	fmt.Scan(&N, &L)

	found := false

	for length := L; length <= 100; length++ {
		// Calculate the starting point of the sequence
		// (2 * N + length - length^2) / (2 * length) should be an integer
		start := (N - (length*(length-1))/2) / length

		// Check if the calculated start is valid
		if start >= 0 && (N-(length*(length-1))/2)%length == 0 {
			found = true
			for i := 0; i < length; i++ {
				fmt.Print(start+i, " ")
			}
			fmt.Println()
			break
		}
	}

	if !found {
		fmt.Println(-1)
	}
} 