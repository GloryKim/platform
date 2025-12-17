// 04_operators.rs
// 기본 연산자(산술, 비교, 논리) 예제입니다.

fn main() {
    let x = 10;
    let y = 3;

    // 산술 연산
    println!("x + y = {}", x + y);
    println!("x - y = {}", x - y);
    println!("x * y = {}", x * y);
    println!("x / y = {}", x / y); // 정수 나눗셈
    println!("x % y = {}", x % y); // 나머지

    // 비교 연산 (결과는 bool)
    println!("x > y = {}", x > y);
    println!("x == y = {}", x == y);

    // 논리 연산
    let t = true;
    let f = false;
    println!("t && f = {}", t && f);
    println!("t || f = {}", t || f);
    println!("!t = {}", !t);
}


