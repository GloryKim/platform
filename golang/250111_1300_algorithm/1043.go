package main

import (
    "bufio"
    "fmt"
    "os"
)

type UnionFind struct {
    parent []int
    rank   []int
}

func NewUnionFind(size int) *UnionFind {
    uf := &UnionFind{
        parent: make([]int, size+1),
        rank:   make([]int, size+1),
    }
    for i := range uf.parent {
        uf.parent[i] = i
    }
    return uf
}

func (uf *UnionFind) Find(x int) int {
    if uf.parent[x] != x {
        uf.parent[x] = uf.Find(uf.parent[x])
    }
    return uf.parent[x]
}

func (uf *UnionFind) Union(x, y int) {
    rootX := uf.Find(x)
    rootY := uf.Find(y)
    
    if rootX != rootY {
        if uf.rank[rootX] < uf.rank[rootY] {
            uf.parent[rootX] = rootY
        } else if uf.rank[rootX] > uf.rank[rootY] {
            uf.parent[rootY] = rootX
        } else {
            uf.parent[rootY] = rootX
            uf.rank[rootX]++
        }
    }
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    writer := bufio.NewWriter(os.Stdout)
    defer writer.Flush()

    var N, M int
    fmt.Fscan(reader, &N, &M)

    // 진실을 아는 사람들 입력
    var truthCount int
    fmt.Fscan(reader, &truthCount)
    
    truthPeople := make([]int, truthCount)
    for i := 0; i < truthCount; i++ {
        fmt.Fscan(reader, &truthPeople[i])
    }

    // Union-Find 초기화
    uf := NewUnionFind(N)

    // 파티 정보 저장
    parties := make([][]int, M)
    for i := 0; i < M; i++ {
        var count int
        fmt.Fscan(reader, &count)
        parties[i] = make([]int, count)
        
        for j := 0; j < count; j++ {
            fmt.Fscan(reader, &parties[i][j])
        }

        // 같은 파티에 참석한 사람들을 하나의 그룹으로 만듦
        for j := 1; j < count; j++ {
            uf.Union(parties[i][0], parties[i][j])
        }
    }

    // 진실을 아는 사람들의 루트를 저장
    truthRoots := make(map[int]bool)
    for _, person := range truthPeople {
        truthRoots[uf.Find(person)] = true
    }

    // 각 파티에서 거짓말을 할 수 있는지 확인
    result := 0
    for _, party := range parties {
        if len(party) == 0 {
            continue
        }
        
        // 파티의 첫 번째 사람의 루트를 확인
        root := uf.Find(party[0])
        if !truthRoots[root] {
            result++
        }
    }

    fmt.Fprintln(writer, result)
}