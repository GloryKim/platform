// 13_vec_slice.rs
// Vec(가변 길이 벡터)와 슬라이스(slice) 예제입니다.

fn main() {
    // 벡터 생성
    let mut numbers: Vec<i32> = Vec::new();
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);

    println!("벡터 전체: {:?}", numbers);

    // 슬라이스: 벡터의 일부를 빌려오기
    let slice = &numbers[1..3]; // 1번 인덱스 이상, 3번 미만 → [20, 30]
    println!("슬라이스: {:?}", slice);

    // for 반복문으로 순회
    for num in &numbers {
        println!("원소: {}", num);
    }

    // 변경 가능한 슬라이스 (부분 변경)
    let slice_mut = &mut numbers[0..2];
    slice_mut[0] = 99;
    println!("수정 후 벡터: {:?}", numbers);
}


