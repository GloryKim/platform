import keyboard
import pyautogui
import time

# 클릭을 시작할지 여부를 결정하는 플래그
clicking = False

def on_space_press(event):
    global clicking
    # 스페이스바가 눌리면 클릭 시작
    if event.name == 'space':
        clicking = True

def on_t_press(event):
    global clicking
    # 't' 키가 눌리면 클릭 중지
    if event.name == 't':
        clicking = False

# 키보드 이벤트에 함수를 연결
keyboard.on_press(on_space_press)
keyboard.on_press(on_t_press)

try:
    while True:
        # clicking 플래그가 True인 경우 클릭 수행
        while clicking:
            pyautogui.click()
            time.sleep(0.01)  # 1초에 10번 클릭하기 위한 대기 시간
except KeyboardInterrupt:
    print("프로그램이 사용자에 의해 중지되었습니다.")


'''
[Mac에서 동작하는 방법]
brew install python
python3 -m venv myenv
source myenv/bin/activate
pip install keyboard
pip install pyautogui

sudo python3 240506_1024_autoclick.py
'''