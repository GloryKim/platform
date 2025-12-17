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

> 이럴 경우 10초이상의 버퍼가 생기게 된다.

# 상식 3
- 상식 2에서 명령어 유지한 상태로 3초이내의 버퍼만 유지


rtsp:
  tcp: yes
  udp: no
  readtimeout: 3s
  writetimeout: 3s

하면 3초 딜레이로 줄어드네


# 상식 4

그럼에도 불구하고 mediamtx쪽 터미널에서 

02:12:46 INF [RTSP] [session 2c90ed0e] created by 211.198.178.225:57764
2025/07/11 02:12:46 INF [RTSP] [session 2c90ed0e] is reading from path 'streamA', with TCP, 2 tracks (H265, MPEG-4 Audio)
2025/07/11 02:12:52 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 398 frames
2025/07/11 02:12:53 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 383 frames
2025/07/11 02:13:02 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 206 frames
2025/07/11 02:13:03 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 434 frames
2025/07/11 02:13:04 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 333 frames
2025/07/11 02:13:10 WAR [RTSP] [session 2c90ed0e] connection is too slow, discarding 223 frames

이런게 뜬다면????

MediaMTX가 RTSP 클라이언트(예: ffplay 등)에게 데이터를 제때 전송하지 못해서, 내부 버퍼에서 프레임을 버리고 있다는 경고이다.

주된 원인
| 원인                          | 설명                                     |
| --------------------------- | -------------------------------------- |
| ✅ 클라이언트 PC 디코딩이 느림          | H.265 디코딩 성능 부족 (특히 ffplay, CPU 디코딩 시) |
| ✅ 네트워크 속도/지연 문제             | Wi-Fi 사용, 패킷 손실, 대역폭 부족                |
| ✅ 클라이언트가 버퍼를 많이 쌓고 있음       | `ffplay`가 기본적으로 내부 버퍼를 사용함             |
| ❗ MediaMTX의 write queue가 작음 | `write_queue_size` 기본값이 낮음 (512)       |


✅ 요약
1. mediamtx.yml에서 read_queue_size 확장 프레임 버리는 현상 줄임
2. ffplay에서 실시간 최적화 인자 추가 -fflags nobuffer, -framedrop, -sync ext 등
3. 네트워크 안정화	유선 연결 사용 권장
4. 클라이언트 디코딩 성능 확인	GPU 디코딩 안되면 ffplay 말고 mpv, VLC 등 고려