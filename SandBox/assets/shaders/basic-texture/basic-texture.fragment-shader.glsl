#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec3 v_Position;
in vec2 v_TexCoord;
			
uniform sampler2D u_Texture;

void main() {
	//color = u_Color;
	//color = vec4(v_Position, 1.0f);
	//color = vec4(v_TexCoord, 0.0f, 1.0f);
	color = texture(u_Texture, v_TexCoord);
}