#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform vec2 transform;
out vec3 vertexColor;

void main() {
	gl_Position = vec4(aPos.x + transform.x, aPos.y + transform.y, aPos.z, 1.0f);
	vertexColor = aColor;
}
