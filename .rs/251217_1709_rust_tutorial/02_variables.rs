// 02_variables.rs
// 변수, 가변성(mut), 상수(const)의 기초 예제입니다.

fn main() {
    // 기본적으로 변수는 불변(immutable)입니다.
    let x = 5;
    println!("x의 값: {}", x);

    // 가변 변수는 `mut` 키워드를 사용합니다.
    let mut y = 10;
    println!("y의 초기 값: {}", y);
    y = 20;
    println!("y의 변경된 값: {}", y);

    // 상수는 `const` 키워드를 사용하며, 타입을 반드시 명시해야 합니다.
    const MAX_POINTS: u32 = 100_000;
    println!("MAX_POINTS: {}", MAX_POINTS);
}


