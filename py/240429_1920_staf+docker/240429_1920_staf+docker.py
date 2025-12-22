@app.route('/upload', methods=['POST'])
def process_video_endpoint():
    # JSON 데이터에서 필요한 정보 추출
    folder_name = request.form['fileName']
    selected_option = request.form['gender']
    video_file = request.files['video']

    # 파일을 저장
    video_path = f'video/{folder_name}.mp4'
    video_file.save(video_path)

    parser = argparse.ArgumentParser()

    parser.add_argument('--vid_file', type=str, default=f'video/{folder_name}.mp4', help='input video path or youtube link') #240318_1518_glory : 테스트를 위해서 기본값을 c.mp4로 변경
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




    output_folder = f'./output/demo_output/{folder_name}/meshes'
    zip_path = f'./output/demo_output/{folder_name}.zip'
    shutil.make_archive(zip_path.replace('.zip', ''), 'zip', output_folder)

    # 압축 파일을 Node.js 서버로 전송
    response = send_zip_to_node(zip_path)
    return jsonify(response)




def send_zip_to_node(zip_path):
    url = 'http://host.docker.internal:xxxx/receive_zip' #240426_1402_glory : localhost로 입력 보낼 포트번호 변경 진행
    with open(zip_path, 'rb') as f:
        files = {'file': (zip_path, f, 'application/zip')}
        response = requests.post(url, files=files)
        return response.json()



if __name__ == '__main__':
    app.run(host='0.0.0.0', port=yyyy, debug=True) #240426_1402_glory : localhost로 입력 받을 포트번호 변경 진행