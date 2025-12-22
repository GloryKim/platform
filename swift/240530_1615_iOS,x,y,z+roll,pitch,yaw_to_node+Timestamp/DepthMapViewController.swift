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
        configuration.frameSemantics.insert(.smoothedSceneDepth)
        arView.session.run(configuration, options: [])
        arView.session.delegate = self

        // Timer to send data 10 times per second
        timer = Timer.scheduledTimer(withTimeInterval: 0.1, repeats: true) { [weak self] _ in
            if let frame = self?.arView.session.currentFrame {
                let transform = frame.camera.transform
                let position = SIMD3<Float>(transform.columns.3.x, transform.columns.3.y, transform.columns.3.z)
                let angles = transform.orientationAngles()
                let timestamp = Date().timeIntervalSince1970
                print("Current device position: \(position)")
                print("Camera Orientation Angles: Pitch \(angles.pitch) degrees, Yaw \(angles.yaw) degrees, Roll \(angles.roll) degrees")
                
                // Send data to server
                self?.sendDataToServer(position: position, pitch: angles.pitch, yaw: angles.yaw, roll: angles.roll, timestamp: timestamp)
            }
        }
    }
    
    func sendDataToServer(position: SIMD3<Float>, pitch: Float, yaw: Float, roll: Float, timestamp: TimeInterval) {
        let url = URL(string: "http://XXX.XXX.XXX.XXX:XXX/data")!
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
            "roll": roll,
            "timestamp": timestamp
        ] as [String : Any]

        let jsonData = try? JSONSerialization.data(withJSONObject: data)
        request.httpBody = jsonData

        URLSession.shared.dataTask(with: request) { _, _, _ in
            // Handle success or failure
        }.resume()
    }

    func session(_ session: ARSession, didUpdate frame: ARFrame) {
        imageView.image = session.currentFrame?.depthMapTransformedImage(orientation: orientation, viewPort: self.imageView.bounds)
    }

    deinit {
        // Stop and release the timer
        timer?.invalidate()
    }
}

extension simd_float4x4 {
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

        return (pitch * (180 / .pi), yaw * (180 / .pi), roll * (180 / .pi))
    }
}


"""
const express = require('express');
const cors = require('cors');
const fs = require('fs');
const app = express();
const port = XXXX;

app.use(cors());
app.use(express.json());

app.post('/data', (req, res) => {
  const { position, pitch, yaw, roll, timestamp } = req.body;
  const logEntry = `Timestamp: ${new Date(timestamp * 1000).toISOString()}, Position: ${JSON.stringify(position)}, Pitch: ${pitch}, Yaw: ${yaw}, Roll: ${roll}\n`;
  
  console.log('Received data:');
  console.log(logEntry);
  
  // Append log entry to a file
  fs.appendFile('data.log', logEntry, (err) => {
    if (err) {
      console.error('Failed to write to log file:', err);
      res.sendStatus(500);
      return;
    }
    res.sendStatus(200);
  });
});

app.listen(port, () => {
  console.log(`Server listening at http://localhost:${port}`);
});
"""