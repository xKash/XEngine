#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

//out vec3 Normal;
//out vec2 TexCoords;
out vec4 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {

	gl_Position = proj * view * model * vec4(position, 1.0f);
	ourColor = vec4(color, 1.0f);
}
