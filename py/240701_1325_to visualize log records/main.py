import matplotlib.pyplot as plt
import datetime
import re

# 데이터를 저장할 리스트들
data = []

# 로그 파일 경로
log_file_path = './server_log.txt'  # 실제 로그 파일 경로로 변경해주세요

# 로그 파일 읽기
with open(log_file_path, 'r') as file:
    current_timestamp = None
    current_error = None
    current_match = None
    current_mismatch = None

    for line in file:
        # 타임스탬프 추출
        timestamp_match = re.search(r'\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}Z', line)
        if timestamp_match:
            current_timestamp = datetime.datetime.strptime(timestamp_match.group(), '%Y-%m-%dT%H:%M:%S.%fZ')

        # 총 거리 오차 추출
        error_match = re.search(r'총 거리 오차: ([\d.]+)', line)
        if error_match:
            current_error = float(error_match.group(1))

        # 스코어 추출
        score_match = re.search(r'현재 스코어 - 일치: (\d+), 불일치: (\d+)', line)
        if score_match:
            current_match = int(score_match.group(1))
            current_mismatch = int(score_match.group(2))

        # 모든 데이터가 있으면 리스트에 추가
        if all([current_timestamp, current_error, current_match, current_mismatch]):
            data.append((current_timestamp, current_error, current_match, current_mismatch))
            current_timestamp = current_error = current_match = current_mismatch = None

# 데이터 분리
timestamps, total_errors, match_scores, mismatch_scores = zip(*data)

# 그래프 그리기
plt.figure(figsize=(12, 8))

# 총 거리 오차 그래프
plt.subplot(2, 1, 1)
plt.plot(timestamps, total_errors, label='총 거리 오차')
plt.title('시간에 따른 총 거리 오차')
plt.xlabel('시간')
plt.ylabel('오차')
plt.legend()

# 스코어 그래프
plt.subplot(2, 1, 2)
plt.plot(timestamps, match_scores, label='일치 스코어')
plt.plot(timestamps, mismatch_scores, label='불일치 스코어')
plt.title('시간에 따른 스코어')
plt.xlabel('시간')
plt.ylabel('스코어')
plt.legend()

plt.tight_layout()
plt.show()