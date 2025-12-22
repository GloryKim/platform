// 10_struct_basic.rs
// 구조체(struct)와 impl 블록의 기초 예제입니다.

// 사용자 정의 타입: 구조체
struct User {
    name: String,
    age: u8,
}

// 구조체에 메서드를 구현하는 impl 블록
impl User {
    fn new(name: String, age: u8) -> Self {
        Self { name, age }
    }

    fn introduce(&self) {
        println!("안녕하세요, 저는 {}이고 나이는 {}살입니다.", self.name, self.age);
    }
}

fn main() {
    let user = User::new(String::from("Alice"), 30);
    user.introduce();
}


