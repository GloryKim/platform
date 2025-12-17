// 05_functions.rs
// 함수 정의, 인자, 반환 값 예제입니다.

// 두 정수를 더해서 반환하는 함수
fn add(a: i32, b: i32) -> i32 {
    // 마지막 표현식에 세미콜론(;)이 없으면 그 값이 반환됩니다.
    a + b
}

fn main() {
    let result = add(5, 7);
    println!("5 + 7 = {}", result);

    // 블록 표현식을 사용한 예
    let x = 10;
    let y = {
        let temp = 2 * x;
        temp + 1 // 세미콜론 없음 → 이 값이 y가 됨
    };

    println!("x = {}, y = {}", x, y);
}


