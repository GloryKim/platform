import random
import openpyxl
from collections import Counter

def generate_balanced_schedule():
    # 팀과 독창자 정의
    instrument_teams = ["악기A", "악기B", "악기C", "악기D", "악기E", "악기F", "악기G", "악기H", "악기I"]
    choir_teams = ["중창A", "중창B", "중창C", "중창D", "중창E"]
    soloists = [
        "독창A", "독창B", "독창C", "독창D", "독창E", "독창F", "독창G", "독창H", "독창I", "독창J", "독창K", "독창L", "독창M", "독창N",
        "독창O", "독창P", "독창Q", "독창R"
    ]

    # 슬롯 생성
    slots = []
    slots.extend(instrument_teams * 4)  # 악기팀 각 4회
    slots.extend(choir_teams * 4)       # 중창팀 각 4회
    slots.extend(soloists[:14] * 5)    # 독창팀 14명 각 5회
    slots.extend(soloists[14:] * 6)    # 독창팀 나머지 4명 각 6회

    random.shuffle(slots)

    # 스케줄 초기화
    schedule = [[None for _ in range(3)] for _ in range(50)]
    used_counts = Counter()

    def is_balanced(schedule, week, candidate):
        # 한 주에 동일 팀/독창자가 여러 번 등장하지 않도록 확인
        if candidate in schedule[week]:
            return False
        return True

    def evenly_distribute(used_counts, candidate):
        # 각 팀/독창자가 1부, 2부, 3부에 골고루 배치되도록 확인
        return used_counts[candidate]

    # 배치 로직
    for week in range(50):
        for service_index in range(3):
            if slots:
                candidates = [candidate for candidate in slots if is_balanced(schedule, week, candidate)]
                if candidates:
                    # 사용 횟수와 균등 분포를 고려하여 선택
                    selected = min(candidates, key=lambda x: (used_counts[x], evenly_distribute(used_counts, x)))
                    schedule[week][service_index] = selected
                    used_counts[selected] += 1
                    slots.remove(selected)

    # 주 단위로 스케줄 섞기
    for week in range(50):
        random.shuffle(schedule[week])

    return schedule, used_counts

def save_to_excel(schedule, counts, filename="balanced_schedule.xlsx"):
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "Schedule"

    # 헤더 추가
    ws.append(["Week", "1부", "2부", "3부"])

    # 스케줄 저장
    for week, services in enumerate(schedule, start=1):
        ws.append([f"{week}주"] + services)

    # 빈 줄 추가 후 팀별 횟수 저장
    ws.append([])
    ws.append(["Team", "Count"])
    for team, count in sorted(counts.items()):
        ws.append([team, count])

    wb.save(filename)
    print(f"Excel file saved as {filename}")

if __name__ == "__main__":
    schedule, counts = generate_balanced_schedule()
    save_to_excel(schedule, counts)