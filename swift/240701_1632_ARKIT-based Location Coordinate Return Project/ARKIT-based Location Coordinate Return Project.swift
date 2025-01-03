struct ARViewContainer: UIViewRepresentable {
    @Binding var imageCoordinates: SIMD3<Float>
    @Binding var modelCoordinates: SIMD3<Float>
    @Binding var deviceCoordinates: SIMD3<Float>
    @Binding var isScanning: Bool
    @Binding var uniqueID: String
    
    class Coordinator: NSObject, ARSessionDelegate {
        var arView: ARView?
        var imageAnchor: ARImageAnchor?
        var modelEntity: ModelEntity?
        var timer: Timer?
        @Binding var imageCoordinates: SIMD3<Float>
        @Binding var modelCoordinates: SIMD3<Float>
        @Binding var deviceCoordinates: SIMD3<Float>
        @Binding var isScanning: Bool
        @Binding var uniqueID: String
        var initialAnchorTransform: simd_float4x4?
        var modelOffset: SIMD3<Float> = SIMD3<Float>(0, 0.1, 0)

        init(imageCoordinates: Binding<SIMD3<Float>>, modelCoordinates: Binding<SIMD3<Float>>, deviceCoordinates: Binding<SIMD3<Float>>, isScanning: Binding<Bool>, uniqueID: Binding<String>) {
            self._imageCoordinates = imageCoordinates
            self._modelCoordinates = modelCoordinates
            self._deviceCoordinates = deviceCoordinates
            self._isScanning = isScanning
            self._uniqueID = uniqueID
            super.init()
            self.timer = Timer.scheduledTimer(timeInterval: 0.1, target: self, selector: #selector(updateCoordinates), userInfo: nil, repeats: true)
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
                        model.scale = SIMD3<Float>(0.4, 0.4, 0.4)
                        
                        self.initialAnchorTransform = imageAnchor.transform
                        let anchorEntity = AnchorEntity(world: imageAnchor.transform)
                        anchorEntity.addChild(model)
                        
                        arView.scene.addAnchor(anchorEntity)
                        
                        model.generateCollisionShapes(recursive: true)
                        arView.installGestures([.translation, .rotation, .scale], for: model)
                        
                        self.modelEntity = model
                        
                        updateModelPosition()
                    }
                }
            }
        }

        @objc func updateCoordinates() {
            guard let imageAnchor = imageAnchor,
                  let modelEntity = modelEntity,
                  let arView = arView,
                  let initialTransform = initialAnchorTransform else { return }
            
            let imagePosition = imageAnchor.transform.columns.3
            let imageCoords = SIMD3<Float>(imagePosition.x, imagePosition.y, imagePosition.z)
            
            let modelPosition = modelEntity.position(relativeTo: nil)
            let relativeModelPosition = simd_make_float4(modelPosition, 1)
            let adjustedModelPosition = simd_mul(simd_inverse(initialTransform), relativeModelPosition)
            
            if let frame = arView.session.currentFrame {
                let cameraTransform = frame.camera.transform
                let relativeDevicePosition = simd_mul(simd_inverse(initialTransform), cameraTransform.columns.3)
                
                DispatchQueue.main.async {
                    self.imageCoordinates = SIMD3<Float>(0, 0, 0)
                    self.modelCoordinates = SIMD3<Float>(adjustedModelPosition.x, adjustedModelPosition.y, adjustedModelPosition.z)
                    self.deviceCoordinates = SIMD3<Float>(relativeDevicePosition.x, relativeDevicePosition.y, relativeDevicePosition.z)
                    
                    if (self.modelCoordinates - self.deviceCoordinates).length() < 0.01 {
                        self.deviceCoordinates = self.modelCoordinates
                    }
                }
                
                print("Image Coordinates: \(self.imageCoordinates)")
                print("Model Entity Coordinates: \(self.modelCoordinates)")
                print("Device Coordinates: \(self.deviceCoordinates)")

                sendDataToServer(deviceCoordinates: self.deviceCoordinates, modelCoordinates: self.modelCoordinates)
            }
        }

        @objc func handleMoveModel(notification: Notification) {
            guard let offset = notification.userInfo?["offset"] as? SIMD3<Float> else { return }
            
            modelOffset += offset
            updateModelPosition()
        }

        func updateModelPosition() {
            guard let modelEntity = modelEntity,
                  let initialTransform = initialAnchorTransform else { return }
            
            let newPosition = simd_make_float4(modelOffset, 1)
            let worldPosition = simd_mul(initialTransform, newPosition)
            modelEntity.setPosition(SIMD3<Float>(worldPosition.x, worldPosition.y, worldPosition.z), relativeTo: nil)
            
            DispatchQueue.main.async {
                self.modelCoordinates = self.modelOffset
            }
        }

        func loadExperience(name: String) -> ModelEntity? {
            return loadUSDZModel(named: "abc.usdz")
        }
        
        func loadUSDZModel(named filename: String) -> ModelEntity? {
            do {
                let modelEntity = try ModelEntity.loadModel(named: filename)
                return modelEntity
            } catch {
                print("Failed to load \(filename): \(error)")
                return nil
            }
        }

        func sendDataToServer(deviceCoordinates: SIMD3<Float>, modelCoordinates: SIMD3<Float>) {
            let url = URL(string: "http://***.***.***.***:****/*****")!
            var request = URLRequest(url: url)
            request.httpMethod = "POST"
            
            let dateFormatter = ISO8601DateFormatter()
            dateFormatter.formatOptions = [.withInternetDateTime, .withFractionalSeconds]
            let timestamp = dateFormatter.string(from: Date())
            
            let data: [String: Any] = [
                "uniqueID": uniqueID,
                "timestamp": timestamp,
                "deviceCoordinates": [
                    "x": deviceCoordinates.x,
                    "y": deviceCoordinates.y,
                    "z": deviceCoordinates.z
                ],
                "modelCoordinates": [
                    "x": modelCoordinates.x,
                    "y": modelCoordinates.y,
                    "z": modelCoordinates.z
                ]
            ]
            let jsonData = try! JSONSerialization.data(withJSONObject: data, options: [])
            request.httpBody = jsonData
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            
            let task = URLSession.shared.dataTask(with: request) { data, response, error in
                if let error = error {
                    print("Error sending data to server: \(error)")
                    return
                }
                print("Data sent to server successfully at \(timestamp)")
            }
            task.resume()
        }
    }
}