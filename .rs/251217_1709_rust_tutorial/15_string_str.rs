// 15_string_str.rs
// String과 &str(문자열 슬라이스) 차이와 변환 예제입니다.

fn main() {
    // &str 리터럴 (불변, 프로그램 전체에서 고정)
    let s_literal: &str = "hello";

    // String: 힙에 저장되는 가변 문자열
    let mut s: String = String::from("hello");
    s.push_str(" world");

    println!("&str 리터럴: {}", s_literal);
    println!("String 값: {}", s);

    // &str -> String
    let s2 = "rust".to_string();
    // String -> &str
    let s2_slice: &str = &s2;
    println!("s2: {}, s2_slice: {}", s2, s2_slice);

    // 슬라이스 사용 (ASCII만 다루는 안전한 예제)
    let text = String::from("abcdef");
    let part = &text[1..4]; // "bcd"
    println!("원본문자열: {}, 슬라이스: {}", text, part);
}


