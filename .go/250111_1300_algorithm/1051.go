package main

import (
    "bufio"
    "fmt"
    "os"
)

func main() {
    var N, M int
    fmt.Scan(&N, &M)

    scanner := bufio.NewScanner(os.Stdin)
    grid := make([]string, N)

    for i := 0; i < N; i++ {
        scanner.Scan()
        grid[i] = scanner.Text()
    }

    maxSize := 1

    for i := 0; i < N; i++ {
        for j := 0; j < M; j++ {
            for size := 1; i+size < N && j+size < M; size++ {
                if grid[i][j] == grid[i][j+size] && grid[i][j] == grid[i+size][j] && grid[i][j] == grid[i+size][j+size] {
                    squareSize := (size + 1) * (size + 1)
                    if squareSize > maxSize {
                        maxSize = squareSize
                    }
                }
            }
        }
    }

    fmt.Println(maxSize)
}