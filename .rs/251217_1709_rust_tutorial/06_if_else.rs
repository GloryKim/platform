// 06_if_else.rs
// if, else if, else 조건문 예제입니다.

fn main() {
    let score = 82;

    if score >= 90 {
        println!("성적: A");
    } else if score >= 80 {
        println!("성적: B");
    } else if score >= 70 {
        println!("성적: C");
    } else {
        println!("성적: F");
    }

    // if는 표현식이기 때문에 값으로도 사용할 수 있습니다.
    let is_pass = if score >= 60 { true } else { false };
    println!("합격 여부: {}", is_pass);
}


