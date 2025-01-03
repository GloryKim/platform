import UIKit
import RealityKit
import ARKit

class DepthMapViewController: UIViewController, ARSessionDelegate {
    
    @IBOutlet var arView: ARView!
    @IBOutlet weak var imageView: UIImageView!
    var timer: Timer?

    var orientation: UIInterfaceOrientation {
        guard let orientation = UIApplication.shared.windows.first?.windowScene?.interfaceOrientation else {
            fatalError()
        }
        return orientation
    }
    @IBOutlet weak var imageViewHeight: NSLayoutConstraint!
    lazy var imageViewSize: CGSize = {
        CGSize(width: view.bounds.size.width, height: imageViewHeight.constant)
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let configuration = ARWorldTrackingConfiguration()
        configuration.frameSemantics.insert(.smoothedSceneDepth) // LiDAR 사용 활성화
        arView.session.run(configuration, options: [])
        arView.session.delegate = self

        // 타이머 설정, 1초마다 카메라의 현재 위치와 각도를 출력
        timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) { [weak self] _ in
            if let frame = self?.arView.session.currentFrame {
                let transform = frame.camera.transform
                let position = SIMD3<Float>(transform.columns.3.x, transform.columns.3.y, transform.columns.3.z)
                let angles = transform.orientationAngles()
                print("Current device position: \(position)")
                print("Camera Orientation Angles: Pitch \(angles.pitch) degrees, Yaw \(angles.yaw) degrees, Roll \(angles.roll) degrees")
                
                //240528_1050_glory : 웹에 좌표값 뿌려주는 코드
                self?.sendDataToServer(position: position, pitch: angles.pitch, yaw: angles.yaw, roll: angles.roll)
                
            }
        }
    }
    
    //240528_1051_glory : 좌표값 발송 함수 추가
    func sendDataToServer(position: SIMD3<Float>, pitch: Float, yaw: Float, roll: Float) {
        //240528_1309_glory : 하기 IP 주소로 원하는 곳에 발송함
        let url = URL(string: "http://***.***.***.***:****/@@@@")!
        //let url = URL(string: "http://***.***.***.***:****/@@@@")!
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")

        let data = [
            "position": [
                "x": position.x,
                "y": position.y,
                "z": position.z
            ],
            "pitch": pitch,
            "yaw": yaw,
            "roll": roll
        ] as [String : Any]

        let jsonData = try? JSONSerialization.data(withJSONObject: data)
        request.httpBody = jsonData

        URLSession.shared.dataTask(with: request) { _, _, _ in
            // 요청 성공 또는 실패 처리
        }.resume()
    }
    
    
    

    func session(_ session: ARSession, didUpdate frame: ARFrame) {
        imageView.image = session.currentFrame?.depthMapTransformedImage(orientation: orientation, viewPort: self.imageView.bounds)
    }

    deinit {
        // 타이머를 정지하고 해제
        timer?.invalidate()
    }
}

extension simd_float4x4 {
    // 변환 매트릭스에서 오일러 각도를 계산하는 메소드
    func orientationAngles() -> (pitch: Float, yaw: Float, roll: Float) {
        let sy = sqrt(self.columns.0.x * self.columns.0.x + self.columns.1.x * self.columns.1.x)
        let singular = sy < 1e-6

        var pitch: Float, yaw: Float, roll: Float
        if !singular {
            pitch = atan2(self.columns.2.y, self.columns.2.z)
            yaw = atan2(-self.columns.2.x, sy)
            roll = atan2(self.columns.1.x, self.columns.0.x)
        } else {
            pitch = atan2(-self.columns.1.z, self.columns.1.y)
            yaw = atan2(-self.columns.2.x, sy)
            roll = 0
        }

        // 각도를 라디안에서 도로 변환
        return (pitch * (180 / .pi), yaw * (180 / .pi), roll * (180 / .pi))
    }
}


/*
//node main.js
//npm init
//npm install express
//npm install cors

const express = require('express');
const cors = require('cors');
const app = express();
const port = 3000;

app.use(cors());
app.use(express.json());

app.post('/data', (req, res) => {
  const { position, pitch, yaw, roll } = req.body;
  console.log('Received data:');
  console.log('Position:', position);
  console.log('Pitch:', pitch);
  console.log('Yaw:', yaw);
  console.log('Roll:', roll);
  res.sendStatus(200);
});

app.listen(port, () => {
  console.log(`Server listening at http://localhost:${port}`);
});

*/