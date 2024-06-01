#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec3 v_Position;
in vec2 v_TexCoord;
			
uniform vec4 u_UniqueColor;
uniform sampler2D u_Texture;

void main() {
	color = texture(u_Texture, v_TexCoord * 10) * u_UniqueColor;
}