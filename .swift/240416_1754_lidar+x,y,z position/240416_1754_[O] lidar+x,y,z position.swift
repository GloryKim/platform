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
        configuration.frameSemantics.insert(.smoothedSceneDepth) // 라이다 사용 활성화
        arView.session.run(configuration, options: [])
        arView.session.delegate = self
        // 240416_1747_glory : 타이머 설정, 1초마다 카메라의 현재 위치를 출력
        timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) { [weak self] _ in
            if let frame = self?.arView.session.currentFrame {
                let transform = frame.camera.transform
                let position = SIMD3<Float>(transform.columns.3.x, transform.columns.3.y, transform.columns.3.z)
                print("Current device position: \(position)")
            }
        }
    }
    func session(_ session: ARSession, didUpdate frame: ARFrame) {
        imageView.image = session.currentFrame?.depthMapTransformedImage(orientation: orientation, viewPort: self.imageView.bounds)
    }
    deinit {
        // 타이머를 정지하고 해제
        timer?.invalidate()
    }
}