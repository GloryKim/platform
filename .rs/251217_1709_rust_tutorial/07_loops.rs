// 07_loops.rs
// loop, while, for 반복문 예제입니다.

fn main() {
    // loop: break를 만나기 전까지 무한 반복
    let mut count = 0;
    loop {
        count += 1;
        println!("loop count = {}", count);

        if count == 3 {
            println!("loop 종료");
            break;
        }
    }

    // while 반복문
    let mut n = 3;
    while n > 0 {
        println!("while n = {}", n);
        n -= 1;
    }

    // for 반복문 (범위)
    for i in 0..5 {
        // 0 이상 5 미만
        println!("for i = {}", i);
    }

    // for 반복문 (컬렉션 순회)
    let numbers = [10, 20, 30];
    for num in numbers {
        println!("배열 원소: {}", num);
    }
}


