#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec3 v_Position;
in vec2 v_TexCoord;
			
uniform vec4 u_UniqueColor;
uniform sampler2D u_Texture;
uniform vec2 u_Tiling;

void main() {
	color = texture(u_Texture, v_TexCoord * u_Tiling) * u_UniqueColor;
}