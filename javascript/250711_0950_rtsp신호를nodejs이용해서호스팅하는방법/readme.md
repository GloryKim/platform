# 상식 1

하기 명령어를 치면 h265인지 h264인지 알수 있다.

ffplay -loglevel debug rtsp://13.1.1.1:1/streamA

핵심 확인 포인트:
> a=rtpmap:96 H265/90000
RTSP SDP에서 비디오 스트림이 H265로 선언되어 있음.

> [rtsp @ 0x146f0aef0] video codec set to: hevc
FFmpeg이 HEVC(H.265) 코덱으로 세팅함.

> Stream #0:0: Video: hevc (Main), ...
실제 디코딩된 스트림이 hevc (Main profile) 로 인식됨.

> [hevc @ 0x1470046a0] nal_unit_type: 32(VPS) ...
H.265의 VPS/SPS/PPS 등 구조적 요소가 디코딩 로그에 나타남. (이건 H.264에는 없는 VPS 포함)

참고:
> hevc = High Efficiency Video Coding = H.265

> h264 = Advanced Video Coding = H.264

FFmpeg 로그에서 hevc라는 이름으로 나타나면 H.265입니다.


# 상식 2
- ffplay 수신측 안정화가 필요하면, 기본값 10초를 유지한 상태로 안정적인 스트리밍을 볼 수 있다.

명령어 : ffplay -fflags nobuffer -flags low_delay -infbuf -analyzeduration 0 -rtsp_transport tcp rtsp://1.1.1.1:8/streamA


| 옵션                   | 설명                       |
| -------------------- | ------------------------ |
| `-fflags nobuffer`   | 내부 디코딩 버퍼를 최소화하여 실시간성 보장 |
| `-infbuf`            | 무제한 입력 버퍼 허용             |
| `-flags low_delay`   | 낮은 지연                    |
| `-analyzeduration 0` | 스트림 분석 없이 바로 디코딩 시작      |

# 상식 3
- 상식 2에서 명령어 유지한 상태로


rtsp:
  tcp: yes
  udp: no
  readtimeout: 3s
  writetimeout: 3s

하면 나이스