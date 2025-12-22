/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Main view controller for the AR experience.
*/

/*
240327_1649_glory
본 코드는 ARKit과 RealityKit을 이용하여 LiDAR 스캔 데이터를 OBJ 파일로 내보내는 기능을 포함함

이 기능은 특히 아이패드 프로와 같이 LiDAR 센서가 탑재된 iOS 장치에서 사용됨


viewDidLoad: 앱이 시작할 때 초기 설정을 수행
이 메서드에서는 AR 세션의 대리자(delegate)를 설정하고, ARKit의 여러 옵션을 설정
여기에는 화면에 메쉬를 시각화하는 옵션과, 사람의 몸을 투명하게 처리하는 옵션 등이 포함


viewDidAppear: 이 메서드는 뷰 컨트롤러의 뷰가 사용자에게 보이게 될 때 호출
이 메서드에서는 앱이 AR 경험 동안 화면이 어두워지는 것을 방지


resetButtonPressed: 사용자가 리셋 버튼을 누르면 호출되어, AR 세션을 리셋

togglePlaneDetectionButtonPressed: 사용자가 평면 감지 시작/정지 버튼을 누를 때 호출되어, 평면 감지 기능을 토글

saveButtonPressed: 사용자가 저장 버튼을 누를 때 호출 현재 AR 세션의 프레임에서 스캔한 메쉬 데이터를 가져와서 OBJ 파일로 내보내고, 이 파일을 사용자와 공유
*/



import Foundation
import RealityKit
import ARKit
import ModelIO
import MetalKit
import QuickLook


class ViewController: UIViewController, ARSessionDelegate {
    
    @IBOutlet var arView: ARView!
    @IBOutlet weak var resetButton: UIButton!
    @IBOutlet weak var planeDetectionButton: UIButton!
    @IBOutlet weak var saveButton: RoundedButton!
    
    let coachingOverlay = ARCoachingOverlayView()
    
    
    /// - Tag: ViewDidLoad
    override func viewDidLoad() {
        super.viewDidLoad()
        
        arView.session.delegate = self
        
        setupCoachingOverlay()

        arView.environment.sceneUnderstanding.options = []
        
        // Turn on occlusion from the scene reconstruction's mesh.
        arView.environment.sceneUnderstanding.options.insert(.occlusion)
        
        // Turn on physics for the scene reconstruction's mesh.
        arView.environment.sceneUnderstanding.options.insert(.physics)

        // Display a debug visualization of the mesh.
        arView.debugOptions.insert(.showSceneUnderstanding)
        
        // For performance, disable render options that are not required for this app.
        arView.renderOptions = [.disablePersonOcclusion, .disableDepthOfField, .disableMotionBlur]
        
        // Manually configure what kind of AR session to run
        arView.automaticallyConfigureSession = false
        let configuration = ARWorldTrackingConfiguration()
        configuration.sceneReconstruction = .mesh

        configuration.environmentTexturing = .automatic
        arView.session.run(configuration)
    }
    
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // Prevent the screen from being dimmed to avoid interrupting the AR experience.
        UIApplication.shared.isIdleTimerDisabled = true
    }
    
    
    override var prefersHomeIndicatorAutoHidden: Bool {
        return true
    }
    
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    
    @IBAction func resetButtonPressed(_ sender: Any) {
        if let configuration = arView.session.configuration {
            arView.session.run(configuration, options: .resetSceneReconstruction)
        }
    }
    
    
    
    /// - Tag: TogglePlaneDetection
    @IBAction func togglePlaneDetectionButtonPressed(_ button: UIButton) {
        guard let configuration = arView.session.configuration as? ARWorldTrackingConfiguration else {
            return
        }
        if configuration.planeDetection == [] {
            configuration.planeDetection = [.horizontal, .vertical]
            button.setTitle("Stop Plane Detection", for: [])
        } else {
            configuration.planeDetection = []
            button.setTitle("Start Plane Detection", for: [])
        }
        arView.session.run(configuration)
    }
    
    
    /// - Tag: Export Mesh
    /// ***********************************************************************************************
    /// Exporting the LIDAR scan as OBJ file
    /// - Author: Stefan Pfeifer
    @IBAction func saveButtonPressed(_ sender: UIButton) {
        
        guard let frame = arView.session.currentFrame else {
            fatalError("Couldn't get the current ARFrame")
        }
        
        // Fetch the default MTLDevice to initialize a MetalKit buffer allocator with
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("Failed to get the system's default Metal device!")
        }
        
        // Using the Model I/O framework to export the scan, so we're initialising an MDLAsset object,
        // which we can export to a file later, with a buffer allocator
        let allocator = MTKMeshBufferAllocator(device: device)
        let asset = MDLAsset(bufferAllocator: allocator)
        
        // Fetch all ARMeshAncors
        let meshAnchors = frame.anchors.compactMap({ $0 as? ARMeshAnchor })
        
        // Convert the geometry of each ARMeshAnchor into a MDLMesh and add it to the MDLAsset
        for meshAncor in meshAnchors {
            
            // Some short handles, otherwise stuff will get pretty long in a few lines
            let geometry = meshAncor.geometry
            let vertices = geometry.vertices
            let faces = geometry.faces
            let verticesPointer = vertices.buffer.contents()
            let facesPointer = faces.buffer.contents()
            
            // Converting each vertex of the geometry from the local space of their ARMeshAnchor to world space
            for vertexIndex in 0..<vertices.count {
                
                // Extracting the current vertex with an extension method provided by Apple in Extensions.swift
                let vertex = geometry.vertex(at: UInt32(vertexIndex))
                
                // Building a transform matrix with only the vertex position
                // and apply the mesh anchors transform to convert into world space
                var vertexLocalTransform = matrix_identity_float4x4
                vertexLocalTransform.columns.3 = SIMD4<Float>(x: vertex.0, y: vertex.1, z: vertex.2, w: 1)
                let vertexWorldPosition = (meshAncor.transform * vertexLocalTransform).position
                
                // Writing the world space vertex back into it's position in the vertex buffer
                let vertexOffset = vertices.offset + vertices.stride * vertexIndex
                let componentStride = vertices.stride / 3
                verticesPointer.storeBytes(of: vertexWorldPosition.x, toByteOffset: vertexOffset, as: Float.self)
                verticesPointer.storeBytes(of: vertexWorldPosition.y, toByteOffset: vertexOffset + componentStride, as: Float.self)
                verticesPointer.storeBytes(of: vertexWorldPosition.z, toByteOffset: vertexOffset + (2 * componentStride), as: Float.self)
            }
            
            // Initializing MDLMeshBuffers with the content of the vertex and face MTLBuffers
            let byteCountVertices = vertices.count * vertices.stride
            let byteCountFaces = faces.count * faces.indexCountPerPrimitive * faces.bytesPerIndex
            let vertexBuffer = allocator.newBuffer(with: Data(bytesNoCopy: verticesPointer, count: byteCountVertices, deallocator: .none), type: .vertex)
            let indexBuffer = allocator.newBuffer(with: Data(bytesNoCopy: facesPointer, count: byteCountFaces, deallocator: .none), type: .index)
            
            // Creating a MDLSubMesh with the index buffer and a generic material
            let indexCount = faces.count * faces.indexCountPerPrimitive
            let material = MDLMaterial(name: "mat1", scatteringFunction: MDLPhysicallyPlausibleScatteringFunction())
            let submesh = MDLSubmesh(indexBuffer: indexBuffer, indexCount: indexCount, indexType: .uInt32, geometryType: .triangles, material: material)
            
            // Creating a MDLVertexDescriptor to describe the memory layout of the mesh
            let vertexFormat = MTKModelIOVertexFormatFromMetal(vertices.format)
            let vertexDescriptor = MDLVertexDescriptor()
            vertexDescriptor.attributes[0] = MDLVertexAttribute(name: MDLVertexAttributePosition, format: vertexFormat, offset: 0, bufferIndex: 0)
            vertexDescriptor.layouts[0] = MDLVertexBufferLayout(stride: meshAncor.geometry.vertices.stride)
            
            // Finally creating the MDLMesh and adding it to the MDLAsset
            let mesh = MDLMesh(vertexBuffer: vertexBuffer, vertexCount: meshAncor.geometry.vertices.count, descriptor: vertexDescriptor, submeshes: [submesh])
            asset.add(mesh)
        }
        
        // Setting the path to export the OBJ file to
        let documentsPath = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let urlOBJ = documentsPath.appendingPathComponent("scan.obj")

        // Exporting the OBJ file
        if MDLAsset.canExportFileExtension("obj") {
            do {
                try asset.export(to: urlOBJ)
                
                // Sharing the OBJ file
                let activityController = UIActivityViewController(activityItems: [urlOBJ], applicationActivities: nil)
                activityController.popoverPresentationController?.sourceView = sender
                self.present(activityController, animated: true, completion: nil)
            } catch let error {
                fatalError(error.localizedDescription)
            }
        } else {
            fatalError("Can't export OBJ")
        }
    }
    /// ***********************************************************************************************

    
    func session(_ session: ARSession, didFailWithError error: Error) {
        guard error is ARError else { return }
        let errorWithInfo = error as NSError
        let messages = [
            errorWithInfo.localizedDescription,
            errorWithInfo.localizedFailureReason,
            errorWithInfo.localizedRecoverySuggestion
        ]
        let errorMessage = messages.compactMap({ $0 }).joined(separator: "\n")
        DispatchQueue.main.async {
            // Present an alert informing about the error that has occurred.
            let alertController = UIAlertController(title: "The AR session failed.", message: errorMessage, preferredStyle: .alert)
            let restartAction = UIAlertAction(title: "Restart Session", style: .default) { _ in
                alertController.dismiss(animated: true, completion: nil)
                self.resetButtonPressed(self)
            }
            alertController.addAction(restartAction)
            self.present(alertController, animated: true, completion: nil)
        }
    }
    
}
