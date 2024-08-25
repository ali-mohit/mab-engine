#version 430 core
			
layout(location = 0) out vec4 color;
			
in vec4  v_Position;
in vec2  v_TextureCoordinate;
in vec4  v_Color;

uniform vec4 u_EdgeColor;
uniform int  u_ShowEdge;

void main() {
	
	color = (1 - u_ShowEdge) * v_Color + (u_ShowEdge * u_EdgeColor);
}