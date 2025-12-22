// 16_traits.rs
// 트레잇(trait) 정의와 구현 예제입니다.

trait Greet {
    fn greet(&self);
}

struct Person {
    name: String,
}

impl Greet for Person {
    fn greet(&self) {
        println!("안녕하세요, 저는 {}입니다.", self.name);
    }
}

impl Greet for &str {
    fn greet(&self) {
        println!("문자열 인사: {}", self);
    }
}

fn main() {
    let p = Person {
        name: String::from("Alice"),
    };
    p.greet();

    let message = "Hello from &str";
    message.greet();
}


