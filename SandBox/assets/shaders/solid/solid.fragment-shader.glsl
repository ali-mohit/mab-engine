#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec3 v_Position;
			
uniform vec4 u_UniqueColor;

void main() {
	color = u_UniqueColor;
}