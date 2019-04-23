#version 330 core

layout (location = 0) in vec2 position;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {

	gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
	TexCoords = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0) * 80.0f;
}