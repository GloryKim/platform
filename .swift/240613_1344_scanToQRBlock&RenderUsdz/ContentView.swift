import SwiftUI
import RealityKit
import ARKit
import SwiftUI

struct ContentView: View {
    var body: some View {
        ARViewContainer().edgesIgnoringSafeArea(.all)
    }
}

struct ARViewContainer: UIViewRepresentable {
    func makeCoordinator() -> Coordinator {
        Coordinator()
    }

    func makeUIView(context: Context) -> ARView {
        let arView = ARView(frame: .zero)
        
        let config = ARWorldTrackingConfiguration()
        config.detectionImages = ARReferenceImage.referenceImages(inGroupNamed: "AR Resources 1", bundle: Bundle.main)
        config.maximumNumberOfTrackedImages = 1
        
        arView.session.run(config)
        arView.session.delegate = context.coordinator
        context.coordinator.arView = arView
        
        return arView
    }

    func updateUIView(_ uiView: ARView, context: Context) {}
    
    class Coordinator: NSObject, ARSessionDelegate {
        var arView: ARView?

        func session(_ session: ARSession, didAdd anchors: [ARAnchor]) {
            guard let arView = arView else { return }
            
            for anchor in anchors {
                if let imageAnchor = anchor as? ARImageAnchor {
                    let imageName = imageAnchor.referenceImage.name
                    
                    if let model = loadExperience(name: imageName!) {
                        model.transform = Transform(scale: SIMD3<Float>(0.1, 0.1, 0.1))
                        
                        let anchorEntity = AnchorEntity(world: imageAnchor.transform)
                        anchorEntity.addChild(model)
                        
                        arView.scene.addAnchor(anchorEntity)
                        
                        // Enable gesture interactions
                        model.generateCollisionShapes(recursive: true)
                        arView.installGestures([.translation, .rotation, .scale], for: model)
                    }
                }
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
