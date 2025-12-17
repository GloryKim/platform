// 18_lifetimes.rs
// 참조의 라이프타임(lifetime) 기초 예제입니다.

// 두 문자열 슬라이스 중 더 긴 쪽을 반환하는 함수
// 반환값의 라이프타임이 입력 참조들 중 최소 라이프타임과 같다는 것을
// 컴파일러에 알려주기 위해 'a 라이프타임 파라미터를 사용합니다.
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() >= y.len() {
        x
    } else {
        y
    }
}

fn main() {
    let s1 = String::from("hello");
    let s2 = String::from("rust");

    let result = longest(&s1, &s2);
    println!("더 긴 문자열: {}", result);
}


