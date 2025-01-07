def send_images_to_node(folder_name):
    # 이미지가 저장된 디렉터리 경로
    image_dir = Path(f'./savingimage/{folder_name}/rendered')
    image_files = list(image_dir.glob('*.jpg'))  # .png 확장자를 가진 파일만 가져옴

    # 멀티파트 폼 데이터 구성
    url = 'http://host.docker.internal:xxxx/receive-images'
    files = {'folder_name': (None, folder_name)}
    for i, file in enumerate(image_files):
        files[f'image_{i+1}'] = (file.name, open(file, 'rb'), 'image/png')

    response = requests.post(url, files=files)
    if response.status_code == 200:
        print("Successfully sent images and folder name to Node.js server.")
    else:
        print("Failed to send images and folder name to Node.js server.")


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


    args = original_args  # 원본 args를 복사
    args.input_path = f'./savingimage/{folder_name}'  # input_path 변경 #240213_1808 : 폴더명 불러오는게 잘 안되네...
    args.out_dir = f'./savingimage/{folder_name}'  # out_dir 변경 #240213_1808 : 폴더명 불러오는게 잘 안되네...
    print(f"Processing: {args.input_path}")

    print(f"ROG Processing: {folder_name}") #240220_1355_glory : 정상 출력이 잘 되는지 맥용 터미널로 출력하는 소스코드

    run_body_mocap(args, body_bbox_detector, body_mocap, visualizer)



    send_images_to_node(folder_name)


app = Flask(__name__) #240215_1113_glory : 필수
CORS(app)


@app.route('/upload', methods=['POST'])
def upload_files():
    folder_name = request.form['folderName']
    save_path = os.path.join('./savingimage', folder_name)
    os.makedirs(save_path, exist_ok=True)

    files = request.files.getlist('images')
    for file in files:
        filename = secure_filename(file.filename)
        file.save(os.path.join(save_path, filename))
        
    main(folder_name)
    return jsonify({"message": "Files uploaded successfully", "path": save_path})


def _build_cors_prelight_response():
    response = make_response()
    response.headers.add("Access-Control-Allow-Origin", "*")
    response.headers.add('Access-Control-Allow-Headers', "*")
    response.headers.add('Access-Control-Allow-Methods', "*")
    return response

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=1248)