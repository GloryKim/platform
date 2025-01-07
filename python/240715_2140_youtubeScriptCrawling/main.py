'''
ubuntu
- pip install google-api-python-client youtube-transcript-api nltk
- python main.py

mac
- python3 -m venv myenv
- source myenv/bin/activate
- pip install google-api-python-client youtube-transcript-api nltk
- python main.py

important
YOUR_YOUTUBE_API_KEY 부분을 실제 유효한 API 키로 대체해야 합니다.
방법은 아래와 같습니다. 
Google Cloud Console에 로그인합니다: Google Cloud Console
프로젝트를 선택하거나 새 프로젝트를 생성합니다.
왼쪽 메뉴에서 API 및 서비스 > 라이브러리를 클릭합니다.
YouTube Data API v3를 검색하고 활성화합니다.
왼쪽 메뉴에서 API 및 서비스 > 사용자 인증 정보를 클릭합니다.
사용자 인증 정보 만들기를 클릭하고, API 키를 선택합니다.
생성된 API 키를 복사합니다.
'''

import os
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
from youtube_transcript_api import YouTubeTranscriptApi, TranscriptsDisabled
import nltk
from nltk.tokenize import word_tokenize
from collections import Counter

# 필요한 NLTK 데이터 다운로드
nltk.download('punkt')

# 유튜브 API 설정
API_KEY = '********'  # 실제 API 키로 대체하세요.
youtube = build('youtube', 'v3', developerKey=API_KEY)

# 한국어 불용어 리스트
korean_stopwords = [
    '이', '그', '저', '것', '수', '등', '들', '및', '그것', '그러나', '그리고', '더구나', '또한',
    '하지만', '그러면서', '그래서', '즉', '따라서', '그러므로', '다만', '그런데', '만약', '만일', '비록',
    '설령', '만약', '만일', '때문에', '왜냐하면', '어디', '어떤', '어느', '누구', '무엇', '어떻게', '왜',
    '하면', '그래도', '조차', '따위', '이랑', '서로', '모두', '각', '매', '한', '단지', '오직', '뿐', '그리하여'
]

def search_youtube_videos(query, max_results=5):
    try:
        request = youtube.search().list(
            q=query,
            part='snippet',
            type='video',
            maxResults=max_results,
            order='date',
            relevanceLanguage='ko'  # 한국어 영상 우선 검색
        )
        response = request.execute()
        video_ids = [item['id']['videoId'] for item in response['items']]
        return video_ids
    except HttpError as e:
        print(f"An error occurred: {e}")
        return []

def get_video_transcripts(video_ids):
    transcripts = []
    for video_id in video_ids:
        try:
            transcript = YouTubeTranscriptApi.get_transcript(video_id, languages=['ko'])
            transcripts.append((video_id, ' '.join([item['text'] for item in transcript])))
        except TranscriptsDisabled:
            print(f"Transcripts are disabled for video {video_id}")
        except Exception as e:
            print(f"Could not retrieve transcript for video {video_id}: {e}")
    return transcripts

def extract_keywords(text, num_keywords=10):
    words = word_tokenize(text.lower())
    filtered_words = [word for word in words if word.isalnum() and word not in korean_stopwords]
    word_counts = Counter(filtered_words)
    keywords = word_counts.most_common(num_keywords)
    return keywords

def save_transcripts(transcripts, directory='transcripts'):
    if not os.path.exists(directory):
        os.makedirs(directory)
    for video_id, transcript in transcripts:
        with open(os.path.join(directory, f"{video_id}.txt"), 'w', encoding='utf-8') as f:
            f.write(transcript)

def main(search_query):
    video_ids = search_youtube_videos(search_query)
    transcripts = get_video_transcripts(video_ids)
    if not transcripts:
        print("No transcripts found for the given search query.")
        return
    
    save_transcripts(transcripts)
    all_text = ' '.join([transcript for _, transcript in transcripts])
    keywords = extract_keywords(all_text)
    
    print(f"Top keywords for '{search_query}':")
    for word, count in keywords:
        print(f"{word}: {count}")

if __name__ == "__main__":
    search_query = input("Enter the search query: ")
    main(search_query)
