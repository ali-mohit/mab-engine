#version 330 core
			
layout(location = 0) in vec4  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_TexCoord;
layout(location = 3) in vec2  a_Tiling;
layout(location = 4) in float a_TextureId;
layout(location = 5) in float a_TextureMaskId;
layout(location = 6) in float a_TransformIndex;


uniform	mat4 u_ViewProjection;

out vec4  v_Position;
out vec4  v_Color;
out vec2  v_TexCoord;
out vec2  v_Tiling;
out float v_TextureId;
out float v_TextureMaskId;
out float v_TransformIndex;


void main() {
	v_Position = a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_Tiling = a_Tiling;
	v_TextureId = a_TextureId;
	v_TextureMaskId = a_TextureMaskId;
	v_TransformIndex = a_TransformIndex;

	gl_Position = u_ViewProjection * v_Position;
}