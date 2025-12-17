// 09_borrowing.rs
// 참조(&)와 빌림(borrowing)에 대한 기초 예제입니다.

// 불변 참조를 받아서 문자열 길이를 계산하는 함수
fn calculate_length(s: &String) -> usize {
    // s는 소유권을 가지지 않고, 빌려서(read-only) 사용만 합니다.
    s.len()
}

// 가변 참조를 받아서 문자열을 수정하는 함수
fn add_suffix(s: &mut String) {
    s.push_str(" world");
}

fn main() {
    let s1 = String::from("hello");

    // 불변 참조
    let len = calculate_length(&s1);
    println!("'{}'의 길이: {}", s1, len); // s1은 여전히 사용 가능

    // 가변 참조
    let mut s2 = String::from("hello");
    add_suffix(&mut s2);
    println!("수정된 문자열: {}", s2);
}


