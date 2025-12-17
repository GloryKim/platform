package main

import (
    "bufio"
    "fmt"
    "os"
)

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    writer := bufio.NewWriter(os.Stdout)
    defer writer.Flush()

    var T int
    fmt.Fscanln(reader, &T)

    for i := 0; i < T; i++ {
        var N, K int
        fmt.Fscanln(reader, &N, &K)

        times := make([]int, N+1)
        for i := 1; i <= N; i++ {
            fmt.Fscan(reader, &times[i])
        }

        fmt.Fscanln(reader)

        edges := make([][]int, N+1)
        inDegree := make([]int, N+1)

        for j := 0; j < K; j++ {
            var X, Y int
            fmt.Fscanln(reader, &X, &Y)
            edges[X] = append(edges[X], Y)
            inDegree[Y]++
        }

        var W int
        fmt.Fscanln(reader, &W)

        queue := make([]int, 0)
        buildTime := make([]int, N+1)

        for b := 1; b <= N; b++ {
            if inDegree[b] == 0 {
                queue = append(queue, b)
                buildTime[b] = times[b]
            }
        }

        idx := 0
        for idx < len(queue) {
            cur := queue[idx]
            idx++

            for _, next := range edges[cur] {
                buildTime[next] = max(buildTime[next], buildTime[cur]+times[next])
                inDegree[next]--
                if inDegree[next] == 0 {
                    queue = append(queue, next)
                }
            }
        }

        fmt.Fprintln(writer, buildTime[W])
    }
}
