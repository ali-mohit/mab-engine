#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec4  v_Position;
in vec4  v_Color;
in vec2  v_TexCoord;
in vec2  v_Tiling;
in float v_TextureId;
in float v_TextureMaskId;
in float v_TransformIndex;
			
uniform sampler2D u_Textures[32];

void main() {
	color = texture(u_Textures[int(v_TextureId)], v_TexCoord * v_Tiling) * v_Color;
	//color = v_Color;
}