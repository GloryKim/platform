import bpy

# 기존 파일 초기화
bpy.ops.wm.read_factory_settings(use_empty=True)

# USD 파일 불러오기
bpy.ops.wm.usd_import(filepath="./input.usdz")

# 텍스처가 포함된 머티리얼을 보존하도록 설정
for material in bpy.data.materials:
    if material.use_nodes:  # 노드 기반 머티리얼 사용 시
        for node in material.node_tree.nodes:
            if node.type == 'TEX_IMAGE':  # 이미지 텍스처가 있는 노드일 때
                image = node.image
                if image is not None:
                    # 텍스처 이미지가 잘 불러와졌는지 확인
                    print(f"텍스처 이미지: {image.filepath}")

# FBX로 내보내기 (텍스처를 포함하여)
bpy.ops.export_scene.fbx(
    filepath="output.fbx", 
    path_mode='COPY',  # 텍스처 파일을 함께 복사
    embed_textures=True  # 텍스처를 FBX 파일에 포함
)