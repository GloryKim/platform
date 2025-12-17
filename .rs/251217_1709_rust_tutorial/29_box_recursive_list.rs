// 29_box_recursive_list.rs
// Box<T>를 이용한 재귀적인 리스트 타입 예제입니다.

enum List {
    Cons(i32, Box<List>),
    Nil,
}

impl List {
    fn new() -> Self {
        List::Nil
    }

    fn prepend(self, value: i32) -> Self {
        List::Cons(value, Box::new(self))
    }

    fn len(&self) -> usize {
        match self {
            List::Cons(_, tail) => 1 + tail.len(),
            List::Nil => 0,
        }
    }

    fn print(&self) {
        match self {
            List::Cons(head, tail) => {
                print!("{} ", head);
                tail.print();
            }
            List::Nil => {
                println!();
            }
        }
    }
}

fn main() {
    let list = List::new().prepend(3).prepend(2).prepend(1);

    print!("리스트 내용: ");
    list.print();
    println!("리스트 길이: {}", list.len());
}


