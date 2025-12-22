// 25_trait_objects.rs
// 트레잇 객체(Box<dyn Trait>)를 이용한 런타임 다형성 예제입니다.

trait Draw {
    fn draw(&self);
}

struct Button {
    label: String,
}

struct Label {
    text: String,
}

impl Draw for Button {
    fn draw(&self) {
        println!("[버튼] {}", self.label);
    }
}

impl Draw for Label {
    fn draw(&self) {
        println!("[레이블] {}", self.text);
    }
}

fn draw_all(components: &[Box<dyn Draw>]) {
    for c in components {
        c.draw();
    }
}

fn main() {
    let components: Vec<Box<dyn Draw>> = vec![
        Box::new(Button {
            label: String::from("확인"),
        }),
        Box::new(Label {
            text: String::from("상태: OK"),
        }),
    ];

    draw_all(&components);
}


