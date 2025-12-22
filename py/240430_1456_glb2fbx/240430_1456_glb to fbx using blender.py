import bpy

def simplify_uv_mapping(obj, threshold=500):
    """
    Simplify the UV mapping process based on mesh complexity.
    Args:
    obj (bpy.types.Object): The mesh object to process.
    threshold (int): The number of faces threshold to decide the UV mapping method.
    """
    if obj.type == 'MESH':
        # 전체 면의 수를 계산
        face_count = len(obj.data.polygons)
        
        # 물체 선택 및 에디트 모드 진입
        bpy.context.view_layer.objects.active = obj
        obj.select_set(True)
        bpy.ops.object.mode_set(mode='EDIT')
        
        # 모든 면 선택
        bpy.ops.mesh.select_all(action='SELECT')
        
        # 면의 수에 따라 UV 매핑 방법 결정
        if face_count > threshold:
            # 복잡한 메쉬의 경우 Smart UV Project 사용
            bpy.ops.uv.smart_project()
        else:
            # 단순한 메쉬의 경우 Unwrap 사용
            bpy.ops.uv.unwrap(method='ANGLE_BASED', margin=0.001)
        
        # 오브젝트 모드로 돌아가기
        bpy.ops.object.mode_set(mode='OBJECT')
        obj.select_set(False)

# 파일 경로 설정
input_file = './sampleGLB.glb'
output_file = './outputModel10.fbx'

# 기존 데이터 삭제
bpy.ops.wm.read_factory_settings(use_empty=True)

# GLB 파일 임포트
bpy.ops.import_scene.gltf(filepath=input_file)

# 모든 객체에 대해 UV 매핑 간소화 적용
for obj in bpy.context.scene.objects:
    simplify_uv_mapping(obj)

# 모든 객체 선택
bpy.ops.object.select_all(action='SELECT')

bpy.ops.export_scene.fbx(
    filepath=output_file,
    use_selection=True,
    apply_scale_options='FBX_SCALE_ALL',
    axis_forward='-Z',
    axis_up='Y',
    global_scale=1.0,
    apply_unit_scale=True,
    bake_space_transform=True,
    embed_textures=True,  # 텍스처를 FBX 파일에 포함
    path_mode='COPY',  # 텍스처 파일을 FBX 파일과 같은 위치에 복사
    bake_anim=True,
    bake_anim_use_all_bones=True,
    bake_anim_use_nla_strips=True,
    bake_anim_use_all_actions=True,
    bake_anim_force_startend_keying=True,
    bake_anim_step=1.0,
    bake_anim_simplify_factor=0.0
)

print("Export complete")