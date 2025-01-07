# Copyright (c) Facebook, Inc. and its affiliates.

import os
import glob #240202_1654_glory : 파일 삭제를 위한 함수 출력
import sys
import os.path as osp
import torch
from torchvision.transforms import Normalize
import numpy as np
import cv2
import argparse
import json
import pickle
from datetime import datetime
import time  # time 모듈을 임포트
from demo.demo_options import DemoOptions# 240202_1131_glory demoOptions 코드 안에서 구현 완료
from bodymocap.body_mocap_api import BodyMocap
from bodymocap.body_bbox_detector import BodyPoseEstimator
import mocap_utils.demo_utils as demo_utils
import mocap_utils.general_utils as gnu
from mocap_utils.timer import Timer

import renderer.image_utils as imu
from renderer.viewer2D import ImShow


from flask_cors import CORS #240215_1154_glory

# Copyright (c) Facebook, Inc. and its affiliates.
# 240202_1139_glory : 코드 삽입 완료

import argparse
import requests

from flask import Flask, request, render_template_string, jsonify

#//import os
#os.environ['DISPLAY'] = ':99'
#from OpenGL.GL import * #쓸모없음 삭제 검토
#from OpenGL.GLUT import * #쓸모없음 삭제 검토
#from OpenGL.GLU import * #쓸모없음 삭제 검토
#import atexit #쓸모없음 삭제 검토
#from renderer import glRenderer
from renderer.p3d_renderer import Pytorch3dRenderer#glory : 이걸 꼭 써줘야지 pytorch3d가 정상작동된다. 단,   File "/home/zxc/glory/github/hpe_web/public/renderer/p3d_renderer.py", line 12, in <module>    from pytorch3d.renderer.mesh import Textures 이 오류가 뜨면 pytorch3d가 덜 설치 된거라고 한다.

#import pytorch3d#glory


class DemoOptions():

    def __init__(self):
        parser = argparse.ArgumentParser()
        
        # parser.add_argument('--checkpoint', required=False, default=default_checkpoint, help='Path to pretrained checkpoint')
        default_checkpoint_body_smpl ='./extra_data/body_module/pretrained_weights/2020_05_31-00_50_43-best-51.749683916568756.pt'
        parser.add_argument('--checkpoint_body_smpl', required=False, default=default_checkpoint_body_smpl, help='Path to pretrained checkpoint')
        default_checkpoint_body_smplx ='./extra_data/body_module/pretrained_weights/smplx-03-28-46060-w_spin_mlc3d_46582-2089_2020_03_28-21_56_16.pt'
        parser.add_argument('--checkpoint_body_smplx', required=False, default=default_checkpoint_body_smplx, help='Path to pretrained checkpoint')
        default_checkpoint_hand = "./extra_data/hand_module/pretrained_weights/pose_shape_best.pth"
        parser.add_argument('--checkpoint_hand', required=False, default=default_checkpoint_hand, help='Path to pretrained checkpoint')

        # input options
        #parser.add_argument('--input_path', type=str, default='webcam', help="""Path of video, image, or a folder where image files exists""")            #240202_1509_glory : 해당 코드는 절대로 구현이 불가능한 코드 
        #240202_1551_glory : 여기 바로 아래에 경로에다가 Nodejs에서 전송받은 특정 문자열(일자관련된 내용을 삭 집어 넣는거지 그러면 시간대별로 primary 하니깐)을 집어넣어서 파일경로에 삭 추가해줘서 따로 이미지 관리해주는 것도 좋아 보인다.
        #240202_1553_glory : 마지막으로 데이터 받고나서 다끝나면 이미지 데이터 삭 다 없에주는 것도 필요할지도.
        #240202_1603_glory : 그런데 이미지를 입력받고 1초뒤에 파이썬 코드 작동하고 그다음 1초뒤에 NodeJS가 작동된다고도 해도 이게 끊임없이 계속 동작해야하는데, 기도하는 마음으로 한번 일단 구현 해보고 파일이 계속 생겨날때 파이썬 코드가 이를 인지하면서 계속 변환하는 방향으로 한번 해보자
        #240202_1606_glory : 그러니깐 즉 노드에서 파일을 계속 생성 시키는 코드를 작동 시킨다음에 바디캠에서 그냥 뿅 실행할때 이미지가 계속 정상 작동 되는지까지 확인해보자 제발 되었으면 좋겠네 -> 이게 구현이 안되면 ,,,, 팀장님께 말해보자
        #240202_1636_glory : 위에가 안된다. 일단 자동으로 유도리있게 계속 파일을 인식하는 행동 자체가 안되는듯 하다
        #240202_1638_glory : 그래서 마지막 해결책은 이거 한바퀴 돌고 특정 경로에 있던 이미지 다 삭제하고 다시 이코드를 실행하고를 특정 횟수로 루프
        #240205_0953_glory : 정확하게 설명하면 폴더를 생성함과 동시에 그 폴더명을 primary한 이름으로 json 타입으로 던져줘서 송수신 하고 해당 결과 완료를 client랑 server단과 같이 진행하도록 함이다.

        parser.add_argument('--input_path', type=str, default='./savingimage', help="""Path of video, image, or a folder where image files exists""") #240202_1327_glory : 잠깐 삭제  + 이걸로 가야함 무조건 + 추후에 경로 관련되어서 반복문 호출 해줘야 할듯 함
        #parser.add_argument('--input_path', type=str, default=None, help="""Path of video, image, or a folder where image files exists""") #240202_1120_glory : 이게 원래 오리지날 명령어 단 간소화 하기 위해서 저렇게 수정
        parser.add_argument('--start_frame', type=int, default=0, help='given a sequence of frames, set the starting frame')
        parser.add_argument('--end_frame', type=int, default=float('inf'), help='given a sequence of frames, set the last frame')
        parser.add_argument('--pkl_dir', type=str, help='Path of storing pkl files that store the predicted results')
        parser.add_argument('--openpose_dir', type=str, help='Directory of storing the prediction of openpose prediction')

        # output options
        #240202_1551_glory : 여기 바로 아래에 경로에다가 Nodejs에서 전송받은 특정 문자열을 집어넣어서 파일경로에 삭 추가해줘서 따로 이미지 관리해주는 것도 좋아 보인다.      
        #240202_1553_glory : 마지막으로 데이터 받고나서 다끝나면 이미지 데이터 삭 다 없에주는 것도 필요할지도.
        #240213_0930_glory : ./mocap_output/output/' 하기 폴더에 파일 생성
        parser.add_argument('--out_dir', type=str, default='./mocap_output/output/', help='Folder of output images.')
        # parser.add_argument('--pklout', action='store_true', help='Export mocap output as pkl file')
        parser.add_argument('--save_bbox_output', action='store_true', help='Save the bboxes in json files (bbox_xywh format)')
        parser.add_argument('--save_pred_pkl', action='store_true', help='Save the predictions (bboxes, params, meshes in pkl format')
        parser.add_argument("--save_mesh", action='store_true', help="Save the predicted vertices and faces")
        parser.add_argument("--save_frame", action='store_true', help='Save the extracted frames from video input or webcam')

        # Other options
        parser.add_argument('--single_person', action='store_true', help='Reconstruct only one person in the scene with the biggest bbox')
        parser.add_argument('--no_display', action='store_true', help='Do not visualize output on the screen')
        parser.add_argument('--no_video_out', action='store_true', help='Do not merge rendered frames to video (ffmpeg)')
        parser.add_argument('--smpl_dir', type=str, default='./extra_data/smpl/', help='Folder where smpl files are located.')
        parser.add_argument('--skip', action='store_true', help='Skip there exist already processed outputs')
        parser.add_argument('--video_url', type=str, default=None, help='URL of YouTube video, or image.')
        parser.add_argument('--download', '-d', action='store_true', help='Download YouTube video first (in webvideo folder), and process it')

        # Body mocap specific options
        parser.add_argument('--use_smplx', action='store_true', help='Use SMPLX model for body mocap')

        # Hand mocap specific options
        parser.add_argument('--view_type', type=str, default='third_view', choices=['third_view', 'ego_centric'],
            help = "The view type of input. It could be ego-centric (such as epic kitchen) or third view")
        parser.add_argument('--crop_type', type=str, default='no_crop', choices=['hand_crop', 'no_crop'],
            help = """ 'hand_crop' means the hand are central cropped in input. (left hand should be flipped to right). 
                        'no_crop' means hand detection is required to obtain hand bbox""")
        
        # Whole motion capture (FrankMocap) specific options
        parser.add_argument('--frankmocap_fast_mode', action='store_true', help="Use fast hand detection mode for whole body motion capture (frankmocap)")

        # renderer
        parser.add_argument("--renderer_type", type=str, default="pytorch3d", #240221_1131_glory : 예전건 opengl인데, 이게 반복 재생할때 문제가 발생한다. // opendr은 잘된다. 그런데 렌더링이 안된다. // pytorch3D로 가야만 한다.
            choices=['pytorch3d', 'opendr', 'opengl_gui', 'opengl'], help="type of renderer to use")

        self.parser = parser


    def parse(self):
        self.opt = self.parser.parse_args()
        return self.opt
#glory
def cleanup(): #쓸모없음 삭제 검토
    global shaderProgram #쓸모없음 삭제 검토
    glDeleteProgram(shaderProgram)  # 쉐이더 프로그램 삭제 #쓸모없음 삭제 검토
    glutLeaveMainLoop()  # GLUT 메인 루프 종료 #쓸모없음 삭제 검토


def run_body_mocap(args, body_bbox_detector, body_mocap, visualizer):
    #Setup input data to handle different types of inputs
    input_type, input_data = demo_utils.setup_input(args)

    cur_frame = args.start_frame
    video_frame = 0
    timer = Timer()
    while True:
        timer.tic()
        # load data
        load_bbox = False

        if input_type =='image_dir':
            if cur_frame < len(input_data):
                image_path = input_data[cur_frame]
                img_original_bgr  = cv2.imread(image_path)
            else:
                img_original_bgr = None

        elif input_type == 'bbox_dir':
            if cur_frame < len(input_data):
                print("Use pre-computed bounding boxes")
                image_path = input_data[cur_frame]['image_path']
                hand_bbox_list = input_data[cur_frame]['hand_bbox_list']
                body_bbox_list = input_data[cur_frame]['body_bbox_list']
                img_original_bgr  = cv2.imread(image_path)
                load_bbox = True
            else:
                img_original_bgr = None

        elif input_type == 'video':      
            _, img_original_bgr = input_data.read()
            if video_frame < cur_frame:
                video_frame += 1
                continue
            # save the obtained video frames
            image_path = osp.join(args.out_dir, "frames", f"{cur_frame:05d}.jpg")
            if img_original_bgr is not None:
                video_frame += 1
                if args.save_frame:
                    gnu.make_subdir(image_path)
                    cv2.imwrite(image_path, img_original_bgr)

        elif input_type == 'webcam':    
            _, img_original_bgr = input_data.read()

            if video_frame < cur_frame:
                video_frame += 1
                continue
            # save the obtained video frames
            image_path = osp.join(args.out_dir, "frames", f"scene_{cur_frame:05d}.jpg")
            if img_original_bgr is not None:
                video_frame += 1
                if args.save_frame:
                    gnu.make_subdir(image_path)
                    cv2.imwrite(image_path, img_original_bgr)
        else:
            assert False, "Unknown input_type"

        cur_frame +=1
        if img_original_bgr is None or cur_frame > args.end_frame:
            break   
        print("--------------------------------------")

        if load_bbox:
            body_pose_list = None
        else:
            body_pose_list, body_bbox_list = body_bbox_detector.detect_body_pose(
                img_original_bgr)
        hand_bbox_list = [None, ] * len(body_bbox_list)

        # save the obtained body & hand bbox to json file
        if args.save_bbox_output: 
            demo_utils.save_info_to_json(args, image_path, body_bbox_list, hand_bbox_list)

        if len(body_bbox_list) < 1: 
            print(f"No body deteced: {image_path}")
            continue

        #Sort the bbox using bbox size 
        # (to make the order as consistent as possible without tracking)
        bbox_size =  [ (x[2] * x[3]) for x in body_bbox_list]
        idx_big2small = np.argsort(bbox_size)[::-1]
        body_bbox_list = [ body_bbox_list[i] for i in idx_big2small ]
        if args.single_person and len(body_bbox_list)>0:
            body_bbox_list = [body_bbox_list[0], ]       

        # Body Pose Regression
        pred_output_list = body_mocap.regress(img_original_bgr, body_bbox_list)
        assert len(body_bbox_list) == len(pred_output_list)

        # extract mesh for rendering (vertices in image space and faces) from pred_output_list
        pred_mesh_list = demo_utils.extract_mesh_from_output(pred_output_list)

        # visualization
        res_img = visualizer.visualize(
            img_original_bgr,
            pred_mesh_list = pred_mesh_list, 
            body_bbox_list = body_bbox_list)
        
        # show result in the screen
        #glory
        #240202_1144_glory:여기서 부터 아래 3줄 죽여야 할 것 같음
        #if not args.no_display:
        #    res_img = res_img.astype(np.uint8)
        #    ImShow(res_img)

        # save result image
        if args.out_dir is not None:
            demo_utils.save_res_img(args.out_dir, image_path, res_img)

        # save predictions to pkl
        if args.save_pred_pkl:
            demo_type = 'body'
            demo_utils.save_pred_to_pkl(
                args, demo_type, image_path, body_bbox_list, hand_bbox_list, pred_output_list)

        timer.toc(bPrint=True,title="Time")
        print(f"Processed : {image_path}")

    #save images as a video
    if not args.no_video_out and input_type in ['video', 'webcam']:
        demo_utils.gen_video_out(args.out_dir, args.seq_name)

    if input_type =='webcam' and input_data is not None:
        input_data.release()
    cv2.destroyAllWindows()


def main(folder_name):
# 노드JS 프라이머리키를 받아오기
    original_args = DemoOptions().parse()  # 원본 args를 저장
    device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')
    assert torch.cuda.is_available(), "Current version only supports GPU"

    # Set bbox detector
    body_bbox_detector = BodyPoseEstimator()

    # Set mocap regressor
    use_smplx = original_args.use_smplx
    checkpoint_path = original_args.checkpoint_body_smplx if use_smplx else original_args.checkpoint_body_smpl
    print("use_smplx", use_smplx)
    body_mocap = BodyMocap(checkpoint_path, original_args.smpl_dir, device, use_smplx)

    if original_args.renderer_type in ['pytorch3d', 'opendr']:
        from renderer.screen_free_visualizer import Visualizer
    else:
        #from renderer.visualizer import Visualizer# 240221_1132_glory : 이전에있던 코드인데, 이걸 안쓰려고 한다.
        from renderer.screen_free_visualizer import Visualizer #glory
    visualizer = Visualizer(original_args.renderer_type)

    '''
    # Set Visualizer
    if original_args.renderer_type in ['pytorch3d', 'opendr']:
        from renderer.screen_free_visualizer import Visualizer
    else:
        from renderer.visualizer import Visualizer
    '''
    args = original_args  # 원본 args를 복사
    args.input_path = f'./savingimage/{folder_name}'  # input_path 변경 #240213_1808 : 폴더명 불러오는게 잘 안되네...
    args.out_dir = f'./savingimage/{folder_name}'  # out_dir 변경 #240213_1808 : 폴더명 불러오는게 잘 안되네...
    print(f"Processing: {args.input_path}")

    print(f"ROG Processing: {folder_name}") #240220_1355_glory : 정상 출력이 잘 되는지 맥용 터미널로 출력하는 소스코드

    # 인증키와 함께 Node.js 서버에 folder_name을 전송
    auth_key = "@@@@@@@@"
    payload = {
        'folder_name': folder_name,
        'auth_key': auth_key
    }

    try:
        #response = requests.post('https://localhost:1234567/receive-folder-name', json=payload, verify=False)
        response = requests.post('http://localhost:1234567/receive-folder-name', json=payload, verify=False) #240220_2049_glory : 맥에서는 없었는데, 우분투 pc 에서는 requests를 별도로 호출해야함
        '''
        #240220_1402_glory : 상기 두번째 줄에 있는 verify=False의 심각한 문제점
        Flask 애플리케이션에서 Node.js 서버로 요청을 보낼 때 https://localhost:1234567/receive-folder-name 주소를 사용하고 있습니다.
        이 주소가 https로 시작하는 것으로 보아 HTTPS 서버를 가정하고 있는 것 같습니다.
        하지만, 개발 환경에서 자체 서명된 인증서를 사용하는 경우, requests 라이브러리가 SSL 인증서를 검증하려고 시도하고, 이로 인해 실패할 수 있습니다.
        개발 목적으로 이 검증을 우회하려면 verify=False 옵션을 추가할 수 있습니다.
        그러나 이는 보안상 좋지 않으므로 실제 운영 환경에서는 사용하지 마십시오.
        '''
        if response.status_code == 200:
            print("Folder name and auth key successfully sent to Node.js server")
        else:
            print("Failed to send folder name and auth key to Node.js server")
    except Exception as e:
        print(f"Error sending folder name and auth key to Node.js server: {e}")
    #time.sleep(3)  # 1초 동안 실행을 일시 중지
    run_body_mocap(args, body_bbox_detector, body_mocap, visualizer)
    #if hasattr(visualizer, 'renderer') and isinstance(visualizer.renderer, glRenderer):
    #visualizer.renderer.cleanupGLResources()#glory
    #glRender.renderer.self.cleanupGLResources()#glory
    #if hasattr(visualizer, 'renderer') and visualizer.renderer.__class__.__name__ == 'glRenderer':
    #    print(f"Error sending folder name and auth key to Node.js server")
    #    visualizer.renderer.cleanupGLResources()#glory



    # 추가적으로 필요한 리소스 해제 또는 정리 작업
    #glDeleteTextures(1, [textureID])
    #os.system("killall Xvfb")
    #atexit.register(cleanup)
    #destroyWindow()



def main2(folder_name): #240219_2039_glory : 맥북에서 개발하기 위한 플라스크 단순 서버용 함수 개발

    print(f"Mac Processing: {folder_name}") #240220_1355_glory : 정상 출력이 잘 되는지 맥용 터미널로 출력하는 소스코드
    # main2 함수의 나머지 로직...

    # 인증키와 함께 Node.js 서버에 folder_name을 전송
    auth_key = "!!!!!!!!!!!"
    payload = {
        'folder_name': folder_name,
        'auth_key': auth_key
    }

    try:
        #response = requests.post('https://localhost:1234567/receive-folder-name', json=payload, verify=False)
        response = requests.post('http://localhost:1234567/receive-folder-name', json=payload, verify=False)
        '''
        #240220_1402_glory : 상기 두번째 줄에 있는 verify=False의 심각한 문제점
        Flask 애플리케이션에서 Node.js 서버로 요청을 보낼 때 https://localhost:1234567/receive-folder-name 주소를 사용하고 있습니다.
        이 주소가 https로 시작하는 것으로 보아 HTTPS 서버를 가정하고 있는 것 같습니다.
        하지만, 개발 환경에서 자체 서명된 인증서를 사용하는 경우, requests 라이브러리가 SSL 인증서를 검증하려고 시도하고, 이로 인해 실패할 수 있습니다.
        개발 목적으로 이 검증을 우회하려면 verify=False 옵션을 추가할 수 있습니다.
        그러나 이는 보안상 좋지 않으므로 실제 운영 환경에서는 사용하지 마십시오.
        '''
        if response.status_code == 200:
            print("Folder name and auth key successfully sent to Node.js server")
        else:
            print("Failed to send folder name and auth key to Node.js server")
    except Exception as e:
        print(f"Error sending folder name and auth key to Node.js server: {e}")







app = Flask(__name__) #240215_1113_glory : 필수
CORS(app)

@app.route('/')
def index():
    # HTML 폼을 렌더링합니다.
    return render_template_string('''
        <!DOCTYPE html>
        <html>
        <head>
            <title>Button Click Example</title>
        </head>
        <body>
            <!-- 버튼 클릭 시 /receive-data 엔드포인트로 요청을 보냅니다. -->
            <form action="/receive-data" method="post">
                <button type="submit">Print Message</button>
            </form>
        </body>
        </html>
    ''')


@app.route('/print-message', methods=['POST'])
def print_message():
    if request.method == 'OPTIONS':  # Preflight request 처리
        return _build_cors_prelight_response()
    elif request.method == 'POST':
        if not request.is_json:
            return jsonify({"error": "Request data must be JSON"}), 400

        data = request.get_json()
        folder_name = data.get('folderName')
        auth_key = data.get('authKey')

        if auth_key == "***********":
            print(f"Authorized access. Folder name: {folder_name}")  # 서버 로그에 출력
            main(folder_name) #240220_2021_glory : 핵심코드
            #main(1)
            #os.system("xvfb-run python3 server.py")
            #main2(folder_name) #240220_2020_glory : 맥북전용 main 함수
            return jsonify({"message": "Data processed successfully"}), 200
        else:
            return jsonify({"error": "Unauthorized access attempt"}), 401

def _build_cors_prelight_response():
    response = make_response()
    response.headers.add("Access-Control-Allow-Origin", "*")
    response.headers.add('Access-Control-Allow-Headers', "*")
    response.headers.add('Access-Control-Allow-Methods', "*")
    return response



'''
#240215_1114_glory : 아래 코드는 이전에 썼던 코드
@app.route('/receive-data', methods=['POST'])
def receive_data():
    data = request.json
    folder_name = data.get('folderName')
    auth_key = data.get('authKey')

    if auth_key == "***********":
        print(f"Authorized access. Folder name: {folder_name}")
    else:
        print("Unauthorized access attempt.")
    
    return "Data received"
'''

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)