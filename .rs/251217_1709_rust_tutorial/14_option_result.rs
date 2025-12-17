// 14_option_result.rs
// Option, Result를 이용한 기본적인 에러 처리 예제입니다.

// 짝수이면 Some(값), 홀수이면 None 반환
fn get_even(n: i32) -> Option<i32> {
    if n % 2 == 0 {
        Some(n)
    } else {
        None
    }
}

fn parse_number(s: &str) -> Result<i32, std::num::ParseIntError> {
    s.parse::<i32>()
}

fn main() {
    // Option 사용
    let n = 5;
    match get_even(n) {
        Some(value) => println!("짝수입니다: {}", value),
        None => println!("{}는 홀수입니다.", n),
    }

    // Result 사용
    let good = "42";
    let bad = "not_a_number";

    match parse_number(good) {
        Ok(v) => println!("파싱 성공: {}", v),
        Err(e) => println!("파싱 실패: {}", e),
    }

    match parse_number(bad) {
        Ok(v) => println!("파싱 성공: {}", v),
        Err(e) => println!("파싱 실패: {}", e),
    }
}


