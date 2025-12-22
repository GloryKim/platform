// 03_basic_types.rs
// 기본 타입들: 정수, 부동소수점, 불리언, 문자 타입 예제입니다.

fn main() {
    // 정수 타입 (기본: i32)
    let a: i32 = -10;
    let b: u32 = 20; // 부호 없는 정수

    // 부동소수점 타입 (기본: f64)
    let c: f64 = 3.14;

    // 불리언
    let is_rust_fun: bool = true;

    // 문자 (유니코드 문자 1개)
    let ch: char = '한';

    println!("a = {}, b = {}", a, b);
    println!("c = {}", c);
    println!("is_rust_fun = {}", is_rust_fun);
    println!("ch = {}", ch);
}


