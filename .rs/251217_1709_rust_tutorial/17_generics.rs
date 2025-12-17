// 17_generics.rs
// 제네릭 함수와 제네릭 제약(트레잇 바운드) 예제입니다.

// 슬라이스에서 가장 큰 값을 찾아 반환하는 제네릭 함수
fn largest<T: PartialOrd + Copy>(slice: &[T]) -> T {
    let mut max = slice[0];
    for &item in slice.iter() {
        if item > max {
            max = item;
        }
    }
    max
}

fn main() {
    let numbers = [10, 20, 5, 30];
    let max_num = largest(&numbers);
    println!("가장 큰 정수: {}", max_num);

    let chars = ['a', 'z', 'b', 'k'];
    let max_char = largest(&chars);
    println!("가장 큰 문자: {}", max_char);
}


