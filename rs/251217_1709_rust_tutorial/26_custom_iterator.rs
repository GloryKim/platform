// 26_custom_iterator.rs
// Iterator 트레잇을 직접 구현하는 예제입니다.

struct Counter {
    current: u32,
    max: u32,
}

impl Counter {
    fn new(max: u32) -> Self {
        Counter { current: 0, max }
    }
}

impl Iterator for Counter {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.current < self.max {
            self.current += 1;
            Some(self.current)
        } else {
            None
        }
    }
}

fn main() {
    let counter = Counter::new(5);

    // 커스텀 이터레이터를 일반 이터레이터처럼 사용
    for value in counter {
        println!("Counter 값: {}", value);
    }
}


