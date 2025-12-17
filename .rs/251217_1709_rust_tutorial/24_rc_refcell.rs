// 24_rc_refcell.rs
// Rc<T>와 RefCell<T>를 이용한 런타임 가변성 + 공유 소유권 예제입니다.

use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    // 문자열 벡터를 RefCell로 감싸서 내부 가변성을 허용하고,
    // Rc로 감싸서 여러 소유자가 공유하도록 합니다.
    let shared_list: Rc<RefCell<Vec<String>>> = Rc::new(RefCell::new(Vec::new()));

    let owner1 = Rc::clone(&shared_list);
    let owner2 = Rc::clone(&shared_list);

    owner1.borrow_mut().push(String::from("첫 번째"));
    owner2.borrow_mut().push(String::from("두 번째"));

    println!("shared_list: {:?}", shared_list.borrow());
    println!("참조 카운트: {}", Rc::strong_count(&shared_list));
}


