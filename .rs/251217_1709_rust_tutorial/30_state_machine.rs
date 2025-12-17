// 30_state_machine.rs
// enum을 이용한 간단한 상태 머신(state machine) 예제입니다.

#[derive(Debug)]
enum State {
    Init,
    Loading,
    Success(String),
    Error(String),
}

impl State {
    fn next(self) -> Self {
        match self {
            State::Init => {
                println!("초기 상태 → Loading");
                State::Loading
            }
            State::Loading => {
                // 여기서는 단순히 성공/실패를 결정하는 것처럼 시뮬레이션합니다.
                let success = true;
                if success {
                    println!("Loading → Success");
                    State::Success("데이터 로드 완료".to_string())
                } else {
                    println!("Loading → Error");
                    State::Error("네트워크 에러".to_string())
                }
            }
            State::Success(msg) => {
                println!("이미 성공 상태입니다: {}", msg);
                State::Success(msg)
            }
            State::Error(msg) => {
                println!("에러 상태에서 다시 시도합니다: {}", msg);
                State::Loading
            }
        }
    }
}

fn main() {
    let mut state = State::Init;
    println!("현재 상태: {:?}", state);

    state = state.next();
    println!("현재 상태: {:?}", state);

    state = state.next();
    println!("현재 상태: {:?}", state);
}


