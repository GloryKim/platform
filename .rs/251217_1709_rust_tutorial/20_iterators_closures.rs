// 20_iterators_closures.rs
// 클로저(closure)와 이터레이터(iterator) 기초 예제입니다.

fn main() {
    // 클로저: 이름 없는 짧은 함수
    let add_one = |x: i32| x + 1;
    let result = add_one(5);
    println!("add_one(5) = {}", result);

    let numbers = vec![1, 2, 3, 4, 5];
    println!("원본 벡터: {:?}", numbers);

    // 이터레이터와 map, filter 사용
    let processed: Vec<i32> = numbers
        .iter()           // 이터레이터 생성 (&i32 순회)
        .map(|x| x * 2)   // 각 원소를 2배
        .filter(|x| *x > 5) // 5보다 큰 것만 남김
        .collect();       // Vec으로 수집

    println!("처리된 벡터: {:?}", processed);
}


