// 28_macro_rules.rs
// macro_rules!를 이용한 간단한 매크로 예제입니다.

// 인자를 여러 개 받아서 Vec<T>를 만드는 매크로
macro_rules! vec_of_strings {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x.to_string());
            )*
            temp_vec
        }
    };
}

fn main() {
    let v = vec_of_strings!["rust", "is", "fun"];
    println!("매크로로 생성한 벡터: {:?}", v);
}


