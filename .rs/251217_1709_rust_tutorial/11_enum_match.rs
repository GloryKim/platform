// 11_enum_match.rs
// enum(열거형)과 match 패턴 매칭 기초 예제입니다.

enum Color {
    Red,
    Green,
    Blue,
}

fn print_color(color: Color) {
    match color {
        Color::Red => println!("색상: 빨강"),
        Color::Green => println!("색상: 초록"),
        Color::Blue => println!("색상: 파랑"),
    }
}

fn main() {
    let c1 = Color::Red;
    let c2 = Color::Green;
    let c3 = Color::Blue;

    print_color(c1);
    print_color(c2);
    print_color(c3);
}


