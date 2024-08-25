#version 430 core
			
layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TextureCoordinate;
layout(location = 2) in vec4  a_Color;

uniform	mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3  v_Position;
out vec2  v_TextureCoordinate;
out vec4  v_Color;

void main() {
	v_Position = a_Position;
	v_TextureCoordinate = a_TextureCoordinate;
	v_Color = a_Color;

	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}