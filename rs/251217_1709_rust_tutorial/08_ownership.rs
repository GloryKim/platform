// 08_ownership.rs
// 소유권(ownership)과 이동(move)에 대한 기초 예제입니다.

fn takes_ownership(s: String) {
    // s는 이 함수에 넘어오면서 소유권이 이동했습니다.
    println!("함수 안에서 받은 문자열: {}", s);
} // 여기서 s가 드롭(drop)되며 메모리가 해제됩니다.

fn makes_copy(x: i32) {
    // i32는 Copy 트레이트를 구현하므로, 값이 복사됩니다.
    println!("함수 안에서 받은 값: {}", x);
}

fn main() {
    let s1 = String::from("hello");
    // String은 힙에 데이터를 저장하는 타입이라 이동(move)이 일어납니다.
    takes_ownership(s1);
    // println!("{}", s1); // 컴파일 에러! 이미 소유권이 이동해서 사용할 수 없습니다.

    let x = 5;
    makes_copy(x);
    // i32는 Copy 타입이라 여전히 사용할 수 있습니다.
    println!("함수 호출 후에도 x는 사용 가능: {}", x);
}


