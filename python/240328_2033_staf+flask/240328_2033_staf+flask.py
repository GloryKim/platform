#240319_1403_glory : 플라스크 기본 함수 추가
from flask import Flask, request, jsonify

import os
import os.path as osp
from lib.core.config import BASE_DATA_DIR
from lib.models.staf import STAF
from lib.models.smpl import SMPL, SMPL_MODEL_DIR
##os.environ['PYOPENGL_PLATFORM'] = 'egl'
import requests  # requests 라이브러리를 임포트합니다.
import cv2
import time
import torch
import joblib
import shutil
import colorsys
import argparse
import random
import numpy as np
from pathlib import Path
from tqdm import tqdm
from multi_person_tracker import MPT
from torch.utils.data import DataLoader

from lib.utils.renderer import Renderer
from lib.dataset._dataset_demo import CropDataset, FeatureDataset
from lib.utils.demo_utils import (
    download_youtube_clip,
    convert_crop_cam_to_orig_img,
    prepare_rendering_results,
    video_to_images,
    images_to_video,
)

MIN_NUM_FRAMES = 25
random.seed(1)
torch.manual_seed(1)
np.random.seed(1)



app = Flask(__name__)


#def main(args):
def process_video(args):
    device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')

    """ Prepare input video (images) """
    video_file = args.vid_file#240319_1424_glory : 코드삭제
    if video_file.startswith('https://www.youtube.com'):
        print(f"Donwloading YouTube video \'{video_file}\'")
        video_file = download_youtube_clip(video_file, '/tmp')
        if video_file is None:
            exit('Youtube url is not valid!')
        print(f"YouTube Video has been downloaded to {video_file}...")

    if not os.path.isfile(video_file):
        exit(f"Input video \'{video_file}\' does not exist!")

    output_path = osp.join('./output/demo_output', os.path.basename(video_file).replace('.mp4', ''))#glory:mp4 ->obj
    Path(output_path).mkdir(parents=True, exist_ok=True)
    image_folder, num_frames, img_shape = video_to_images(video_file, return_info=True)

    print(f"Input video number of frames {num_frames}\n")
    orig_height, orig_width = img_shape[:2]

    """ Run tracking """
    total_time = time.time()
    bbox_scale = 1.1  #
    # run multi object tracker
    mot = MPT(
        device=device,
        batch_size=args.tracker_batch_size,
        display=args.display,
        detector_type=args.detector,
        output_format='dict',
        yolo_img_size=args.yolo_img_size,
    )
    tracking_results = mot(image_folder)

    # remove tracklets if num_frames is less than MIN_NUM_FRAMES
    for person_id in list(tracking_results.keys()):
        if tracking_results[person_id]['frames'].shape[0] < MIN_NUM_FRAMES:
            del tracking_results[person_id]

    """ Get STAF model """
    seq_len = 9
    model = STAF(
        seqlen=seq_len,
    ).to(device)

    # Load pretrained weights
    pretrained_file = args.model
    ckpt = torch.load(pretrained_file)
    print(f"Load pretrained weights from \'{pretrained_file}\'")
    ckpt = ckpt['gen_state_dict']
    model.load_state_dict(ckpt, strict=False)

    # Change mesh gender
    gender = args.gender  # 'neutral', 'male', 'female'
    model.regressor.smpl = SMPL(
        SMPL_MODEL_DIR,
        batch_size=64,
        create_transl=False,
        gender=gender
    ).cuda()

    model.eval()

    # Get feature_extractor
    from lib.models.pymaf_resnet import PyMAF_ResNet
    hmr = PyMAF_ResNet().to(device)
    checkpoint = torch.load('./data/basedata/base_model.pt')#240314_1728_glory : 경로 수정
    hmr.load_state_dict(checkpoint['model'], strict=False)
    hmr.eval()

    """ Run STAF on each person """
    print("\nRunning STAF on each person tracklet...")
    running_time = time.time()
    running_results = {}
    for person_id in tqdm(list(tracking_results.keys())):
        bboxes = joints2d = None
        bboxes = tracking_results[person_id]['bbox']
        frames = tracking_results[person_id]['frames']
        # Prepare static image features
        dataset = CropDataset(
            image_folder=image_folder,
            frames=frames,
            bboxes=bboxes,
            joints2d=joints2d,
            scale=bbox_scale,
        )

        bboxes = dataset.bboxes
        frames = dataset.frames
        has_keypoints = True if joints2d is not None else False

        crop_dataloader = DataLoader(dataset, batch_size=256, num_workers=0)  # 16

        with torch.no_grad():
            feature_list = []
            for i, batch in enumerate(crop_dataloader):
                if has_keypoints:
                    batch, nj2d = batch
                    norm_joints2d.append(nj2d.numpy().reshape(-1, 21, 3))

                batch = batch.to(device)
                feature = hmr(batch.reshape(-1, 3, 224, 224))
                feature_list.append(feature.cpu())

            del batch

            feature_list = torch.cat(feature_list, dim=0)

        # Encode temporal features and estimate 3D human mesh
        dataset = FeatureDataset(
            image_folder=image_folder,
            frames=frames,
            seq_len=seq_len,
        )
        dataset.feature_list = feature_list

        dataloader = DataLoader(dataset, batch_size=16, num_workers=0)  # 32
        with torch.no_grad():
            pred_cam, pred_verts, pred_pose, pred_betas, pred_joints3d, norm_joints2d = [], [], [], [], [], []

            for i, batch in enumerate(dataloader):
                if has_keypoints:
                    batch, nj2d = batch
                    norm_joints2d.append(nj2d.numpy().reshape(-1, 21, 3))

                batch = batch.to(device)
                output = model(batch)[0][-1]

                pred_cam.append(output['theta'][:, :3])
                pred_verts.append(output['verts'])
                pred_pose.append(output['theta'][:, 3:75])
                pred_betas.append(output['theta'][:, 75:])
                pred_joints3d.append(output['kp_3d'])

            pred_cam = torch.cat(pred_cam, dim=0)
            pred_verts = torch.cat(pred_verts, dim=0)
            pred_pose = torch.cat(pred_pose, dim=0)
            pred_betas = torch.cat(pred_betas, dim=0)
            pred_joints3d = torch.cat(pred_joints3d, dim=0)

            del batch

        # ========= Save results to a pickle file ========= #
        pred_cam = pred_cam.cpu().numpy()
        pred_verts = pred_verts.cpu().numpy()
        pred_pose = pred_pose.cpu().numpy()
        pred_betas = pred_betas.cpu().numpy()
        pred_joints3d = pred_joints3d.cpu().numpy()
        bboxes[:, 2:] = bboxes[:, 2:] * 1.2
        # if args.render_plain:
        #     pred_cam[:, 0], pred_cam[:, 1:] = 1, 0  # np.array([[1, 0, 0]])
        orig_cam = convert_crop_cam_to_orig_img(
            cam=pred_cam,
            bbox=bboxes,
            img_width=orig_width,
            img_height=orig_height
        )

        output_dict = {
            'pred_cam': pred_cam,
            'orig_cam': orig_cam,
            'verts': pred_verts,
            'pose': pred_pose,
            'betas': pred_betas,
            'joints3d': pred_joints3d,
            'joints2d': joints2d,
            'bboxes': bboxes,
            'frame_ids': frames,
        }

        running_results[person_id] = output_dict

    del model

    end = time.time()
    fps = num_frames / (end - running_time)
    print(f'STAF FPS: {fps:.2f}')
    total_time = time.time() - total_time
    print(f'Total time spent: {total_time:.2f} seconds (including model loading time).')
    print(f'Total FPS (including model loading time): {num_frames / total_time:.2f}.')

    if args.save_pkl:
        print(f"Saving output results to \'{os.path.join(output_path, 'staf_output.pkl')}\'.")
        joblib.dump(running_results, os.path.join(output_path, "staf_output.pkl"))

    """ Render results as a single video """
    renderer = Renderer(resolution=(orig_width, orig_height), orig_img=True, wireframe=args.wireframe)

    output_img_folder = f'{image_folder}_output'
    input_img_folder = f'{image_folder}_input'
    os.makedirs(output_img_folder, exist_ok=True)
    os.makedirs(input_img_folder, exist_ok=True)

    print(f"\nRendering output video, writing frames to {output_img_folder}")
    # prepare results for rendering
    frame_results = prepare_rendering_results(running_results, num_frames)
    mesh_color = {k: colorsys.hsv_to_rgb(np.random.rand(), 0.5, 1.0) for k in running_results.keys()}

    image_file_names = sorted([
        os.path.join(image_folder, x)
        for x in os.listdir(image_folder)
        if x.endswith('.png') or x.endswith('.jpg')
    ])

    for frame_idx in tqdm(range(len(image_file_names))):
        img_fname = image_file_names[frame_idx]
        img = cv2.imread(img_fname)
        input_img = img.copy()
        if args.render_plain:
            img[:] = 0

        if args.sideview:
            side_img = np.zeros_like(img)

        for person_id, person_data in frame_results[frame_idx].items():
            frame_verts = person_data['verts']
            frame_cam = person_data['cam']

            mesh_filename = None
            if args.save_obj:
                mesh_folder = os.path.join(output_path, 'meshes', f'{person_id:04d}')
                Path(mesh_folder).mkdir(parents=True, exist_ok=True)
                mesh_filename = os.path.join(mesh_folder, f'{frame_idx:06d}.obj')

            mc = mesh_color[person_id]

            img = renderer.render(
                img,
                frame_verts,
                cam=frame_cam,
                color=mc,
                mesh_filename=mesh_filename,
            )
            if args.sideview:
                side_img = renderer.render(
                    side_img,
                    frame_verts,
                    cam=frame_cam,
                    color=mc,
                    angle=270,
                    axis=[0, 1, 0],
                )

        if args.sideview:
            img = np.concatenate([img, side_img], axis=1)

        # save output frames
        cv2.imwrite(os.path.join(output_img_folder, f'{frame_idx:06d}.jpg'), img)
        cv2.imwrite(os.path.join(input_img_folder, f'{frame_idx:06d}.jpg'), input_img)

        if args.display:
            cv2.imshow('Video', img)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    if args.display:
        cv2.destroyAllWindows()

    """ Save rendered video """
    vid_name = os.path.basename(video_file)
    save_name = f'STAF_{vid_name.replace(".mp4", "")}_output.mp4'#glory:mp4 ->obj
    save_path = os.path.join(output_path, save_name)

    images_to_video(img_folder=output_img_folder, output_vid_file=save_path)
    images_to_video(img_folder=input_img_folder, output_vid_file=os.path.join(output_path, vid_name))
    print(f"Saving result video to {os.path.abspath(save_path)}")
    shutil.rmtree(output_img_folder)
    shutil.rmtree(input_img_folder)
    shutil.rmtree(image_folder)

#240318_1529_glory : 실행 명령어는 (staf2) hi@bye:~/glory/240315_1613_hpe_web/public/staf$ python demo.py --save_obj
#업무테이블
'''
1. 이미지를 영상으로 변환하기 - node
2. 해당이미지를 랜덤으로 변환해서 저장하기 - node
3. 변환된 이름+성별 flask로 던지기 - node
4. 본 코드 플라스크로 변환하기
5. 완료되면 노드에 신호 보내기
6. 노드에서 다운로드 버튼 구현하기
7. 파이썬 동시접속 되는지 확인하기 or 순차접속 -> 안된다면 명령어를 실행하는 플라스크를 작동하고 그걸 순차로 하는걸로 하기
'''






@app.route('/process-video', methods=['POST'])
def process_video_endpoint():
    data = request.json
    folder_name = data['folderName']
    selected_option = data['selectedOption']
    print(f'Received folder name: {folder_name}, Selected option: {selected_option}')

    parser = argparse.ArgumentParser()

    parser.add_argument('--vid_file', type=str, default=f'video/{folder_name}/{folder_name}.mp4', help='input video path or youtube link') #240318_1518_glory : 테스트를 위해서 기본값을 c.mp4로 변경
    #240318_1530_glory : [필수] 나중에 여기 부분에서 디폴트 부분을 json 형태로 받아야 할 듯 함
    parser.add_argument('--model', type=str, default='./data/basedata/3dpw_model_best.pth.tar',
                        help='path to pretrained model weight')

    parser.add_argument('--detector', type=str, default='maskrcnn', choices=['yolo', 'maskrcnn'], #240314_1719_glory : [고정] yolo가 기본값인데, maskrcnn으로 변경함
                        help='object detector to be used for bbox tracking')

    parser.add_argument('--yolo_img_size', type=int, default=416,
                        help='input image size for yolo detector')

    parser.add_argument('--tracker_batch_size', type=int, default=12,
                        help='batch size of object detector used for bbox tracking')

    parser.add_argument('--display', action='store_true',
                        help='visualize the results of each step during demo')

    parser.add_argument('--save_pkl', action='store_true',
                        help='save results to a pkl file')

    parser.add_argument('--save_obj', action='store_true',
                        help='save results as .obj files.')

    parser.add_argument('--gender', type=str, default=selected_option,
                        help='set gender of people from (neutral, male, female)')
    #240318_1531_glory : [필수] 성별 던지는것도 json 형태로 잘 받아야 할듯


    parser.add_argument('--wireframe', action='store_true',
                        help='render all meshes as wireframes.')

    parser.add_argument('--sideview', action='store_true',
                        help='render meshes from alternate viewpoint.')

    parser.add_argument('--render_plain', action='store_true',
                        help='render meshes on plain background')

    parser.add_argument('--gpu', type=int, default='0', help='gpu num') #240318_1528_glory : titan pc gpu 할당 번호는 0번으로 고정해야할 듯 함 아직 세팅이 안된건지 1번은 안됨

    args = parser.parse_args()
    os.environ['CUDA_VISIBLE_DEVICES'] = str(args.gpu)

    process_video(args)

    try:
        # process_video 함수를 성공적으로 호출하는 로직을 구현합니다.
        # 예: process_video(args)
        # 여기에서는 단순화를 위해 호출 과정을 생략합니다.

        # process_video 호출이 성공한 후 localhost:1234567으로 요청을 보냅니다.
        url = 'http://localhost:1234567/receive-folder-name2'
        payload = {'folderName': folder_name}
        response = requests.post(url, json=payload)
        if response.status_code == 200:
            print('Successfully sent the folder name to localhost:1234567')
        else:
            print('Failed to send the folder name to localhost:1234567')
            
        return jsonify({'message': 'Video processing started and folder name sent successfully', 'folderName': folder_name}), 202
    
    except Exception as e:
        print(f"Error processing video or sending data: {e}")
        return jsonify({'error': str(e)}), 500
 

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3030, debug=True)