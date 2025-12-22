// 19_modules.rs
// 모듈(mod)과 공개 범위(pub) 기초 예제입니다.

mod math {
    // 모듈 밖에서 사용하려면 pub로 공개해야 합니다.
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }

    pub fn sub(a: i32, b: i32) -> i32 {
        a - b
    }

    fn hidden_mul(a: i32, b: i32) -> i32 {
        a * b
    }

    pub fn show_hidden_mul(a: i32, b: i32) {
        let result = hidden_mul(a, b);
        println!("hidden_mul 결과: {}", result);
    }
}

fn main() {
    let sum = math::add(3, 5);
    let diff = math::sub(10, 4);

    println!("3 + 5 = {}", sum);
    println!("10 - 4 = {}", diff);

    math::show_hidden_mul(2, 6);
}


