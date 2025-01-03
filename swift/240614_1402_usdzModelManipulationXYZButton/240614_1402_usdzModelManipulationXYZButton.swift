import SwiftUI
import RealityKit
import ARKit

struct ContentView: View {
    @State private var imageCoordinates: SIMD3<Float> = SIMD3<Float>(0, 0, 0)
    @State private var modelCoordinates: SIMD3<Float> = SIMD3<Float>(0, 0, 0)
    @State private var deviceCoordinates: SIMD3<Float> = SIMD3<Float>(0, 0, 0)
    @State private var isScanning: Bool = false

    var body: some View {
        ZStack(alignment: .topLeading) {
            ARViewContainer(imageCoordinates: $imageCoordinates, modelCoordinates: $modelCoordinates, deviceCoordinates: $deviceCoordinates, isScanning: $isScanning)
                .edgesIgnoringSafeArea(.all)
            VStack(alignment: .leading) {
                Text("Image Coordinates: \(imageCoordinates.x)m, \(imageCoordinates.y * 1.38461538462)m, \(imageCoordinates.z)m")
                    .foregroundColor(.white)
                    .padding()
                Text("Model Coordinates: \(modelCoordinates.x)m, \(modelCoordinates.y)m, \(modelCoordinates.z)m")
                    .foregroundColor(.white)
                    .padding()
                Text("Device Coordinates: \(deviceCoordinates.x)m, \(deviceCoordinates.y)m, \(deviceCoordinates.z)m")
                    .foregroundColor(.white)
                    .padding()
                Button(action: {
                    isScanning.toggle()
                }) {
                    Text(isScanning ? "Stop Scanning" : "Start Scanning")
                        .foregroundColor(.white)
                        .padding()
                        .background(Color.blue)
                        .cornerRadius(10)
                }
                .padding()
                
                HStack {
                    Button(action: {
                        moveModel(by: SIMD3<Float>(0.05, 0, 0))
                    }) {
                        Text("+X")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.green)
                            .cornerRadius(10)
                    }
                    Button(action: {
                        moveModel(by: SIMD3<Float>(-0.05, 0, 0))
                    }) {
                        Text("-X")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.red)
                            .cornerRadius(10)
                    }
                }
                .padding()

                HStack {
                    Button(action: {
                        moveModel(by: SIMD3<Float>(0, 0.05, 0))
                    }) {
                        Text("+Y")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.green)
                            .cornerRadius(10)
                    }
                    Button(action: {
                        moveModel(by: SIMD3<Float>(0, -0.05, 0))
                    }) {
                        Text("-Y")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.red)
                            .cornerRadius(10)
                    }
                }
                .padding()

                HStack {
                    Button(action: {
                        moveModel(by: SIMD3<Float>(0, 0, 0.05))
                    }) {
                        Text("+Z")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.green)
                            .cornerRadius(10)
                    }
                    Button(action: {
                        moveModel(by: SIMD3<Float>(0, 0, -0.05))
                    }) {
                        Text("-Z")
                            .foregroundColor(.white)
                            .padding()
                            .background(Color.red)
                            .cornerRadius(10)
                    }
                }
                .padding()
            }
            .background(Color.black.opacity(0.5))

            // A4 비율의 테두리 추가
            Rectangle()
                .stroke(Color.red, lineWidth: 2)
                .frame(width: UIScreen.main.bounds.width * 0.2, height: UIScreen.main.bounds.width * 0.2 * 1.414)
                .position(x: UIScreen.main.bounds.width / 2, y: UIScreen.main.bounds.height / 2)
        }
    }
    
    func moveModel(by offset: SIMD3<Float>) {
        NotificationCenter.default.post(name: .moveModel, object: nil, userInfo: ["offset": offset])
    }
}

struct ARViewContainer: UIViewRepresentable {
    @Binding var imageCoordinates: SIMD3<Float>
    @Binding var modelCoordinates: SIMD3<Float>
    @Binding var deviceCoordinates: SIMD3<Float>
    @Binding var isScanning: Bool
    
    func makeCoordinator() -> Coordinator {
        Coordinator(imageCoordinates: $imageCoordinates, modelCoordinates: $modelCoordinates, deviceCoordinates: $deviceCoordinates, isScanning: $isScanning)
    }

    func makeUIView(context: Context) -> ARView {
        let arView = ARView(frame: .zero)
        context.coordinator.arView = arView
        return arView
    }

    func updateUIView(_ uiView: ARView, context: Context) {
        if isScanning {
            let config = ARWorldTrackingConfiguration()
            config.detectionImages = ARReferenceImage.referenceImages(inGroupNamed: "AR Resources 1", bundle: Bundle.main)
            config.maximumNumberOfTrackedImages = 1
            config.environmentTexturing = .automatic
            config.frameSemantics = .sceneDepth

            uiView.session.run(config)
            uiView.session.delegate = context.coordinator
        } else {
            uiView.session.pause()
        }
    }
    
    class Coordinator: NSObject, ARSessionDelegate {
        var arView: ARView?
        var imageAnchor: ARImageAnchor?
        var modelEntity: ModelEntity?
        var timer: Timer?
        @Binding var imageCoordinates: SIMD3<Float>
        @Binding var modelCoordinates: SIMD3<Float>
        @Binding var deviceCoordinates: SIMD3<Float>
        @Binding var isScanning: Bool
        
        init(imageCoordinates: Binding<SIMD3<Float>>, modelCoordinates: Binding<SIMD3<Float>>, deviceCoordinates: Binding<SIMD3<Float>>, isScanning: Binding<Bool>) {
            self._imageCoordinates = imageCoordinates
            self._modelCoordinates = modelCoordinates
            self._deviceCoordinates = deviceCoordinates
            self._isScanning = isScanning
            super.init()
            self.timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(printCoordinates), userInfo: nil, repeats: true)
            NotificationCenter.default.addObserver(self, selector: #selector(handleMoveModel), name: .moveModel, object: nil)
        }
        
        deinit {
            timer?.invalidate()
            NotificationCenter.default.removeObserver(self)
        }

        func session(_ session: ARSession, didAdd anchors: [ARAnchor]) {
            guard let arView = arView else { return }
            
            for anchor in anchors {
                if let imageAnchor = anchor as? ARImageAnchor {
                    self.imageAnchor = imageAnchor
                    let imageName = imageAnchor.referenceImage.name
                    
                    if let model = loadExperience(name: imageName!) {
                        model.transform = Transform(scale: SIMD3<Float>(0.4, 0.4, 0.4))
                        
                        // Adjust the position of the model to be 10cm above the image
                        var imageTransform = imageAnchor.transform
                        imageTransform.columns.3.y += 0.1
                        
                        let anchorEntity = AnchorEntity(world: imageTransform)
                        anchorEntity.addChild(model)
                        
                        arView.scene.addAnchor(anchorEntity)
                        
                        // Enable gesture interactions
                        model.generateCollisionShapes(recursive: true)
                        arView.installGestures([.translation, .rotation, .scale], for: model)
                        
                        self.modelEntity = model
                    }
                }
            }
        }

        @objc func printCoordinates() {
            guard let imageAnchor = imageAnchor, let modelEntity = modelEntity, let arView = arView else { return }
            
            // Get image anchor position
            let imagePosition = imageAnchor.transform.columns.3
            let imageCoords = SIMD3<Float>(imagePosition.x, imagePosition.y, imagePosition.z)
            
            // Get model entity position
            let modelPosition = modelEntity.position(relativeTo: nil)
            
            // Get device position
            if let frame = arView.session.currentFrame {
                let devicePosition = frame.camera.transform.columns.3
                let deviceCoords = SIMD3<Float>(devicePosition.x, devicePosition.y, devicePosition.z)
                
                // Update coordinates
                DispatchQueue.main.async {
                    self.imageCoordinates = imageCoords
                    self.modelCoordinates = modelPosition
                    self.deviceCoordinates = deviceCoords
                }
                
                // Print positions to console
                print("Image Coordinates: \(imageCoords)")
                print("Model Entity Coordinates: \(modelPosition)")
                print("Device Coordinates: \(deviceCoords)")
            }
        }

        @objc func handleMoveModel(notification: Notification) {
            guard let offset = notification.userInfo?["offset"] as? SIMD3<Float>,
                  let modelEntity = modelEntity else { return }
            modelEntity.transform.translation += offset
            DispatchQueue.main.async {
                self.modelCoordinates = modelEntity.position(relativeTo: nil)
            }
        }

        // Load Experience model
        func loadExperience(name: String) -> ModelEntity? {
            return loadUSDZModel(named: "abc.usdz")
        }
        
        // Helper function to load USDZ model
        func loadUSDZModel(named filename: String) -> ModelEntity? {
            do {
                let modelEntity = try ModelEntity.loadModel(named: filename)
                return modelEntity
            } catch {
                print("Failed to load \(filename): \(error)")
                return nil
            }
        }
    }
}

extension Notification.Name {
    static let moveModel = Notification.Name("moveModel")
}
