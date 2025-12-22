// 12_pattern_matching.rs
// 패턴 매칭: 튜플, 구조체 분해 예제입니다.

struct Point {
    x: i32,
    y: i32,
}

fn main() {
    // 튜플 패턴
    let pair = (10, -5);
    match pair {
        (0, y) => println!("x는 0, y는 {}", y),
        (x, 0) => println!("x는 {}, y는 0", x),
        (x, y) => println!("둘 다 0이 아님: x = {}, y = {}", x, y),
    }

    // 구조체 패턴
    let p = Point { x: 3, y: 7 };
    let Point { x, y } = p;
    println!("Point 분해: x = {}, y = {}", x, y);

    // match에서 구조체 분해
    let p2 = Point { x: 0, y: 10 };
    match p2 {
        Point { x: 0, y } => println!("x는 0이고, y는 {}", y),
        Point { x, y: 0 } => println!("y는 0이고, x는 {}", x),
        Point { x, y } => println!("일반 좌표: ({}, {})", x, y),
    }
}


