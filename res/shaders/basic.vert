#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

struct VertexData {
	vec3 Position;
	vec3 Color;
};

struct Uniforms {
	vec3 Transform;
	vec3 Color;
};

uniform Uniforms u;
out VertexData v;

void main() {
	v.Position = vec3(aPos.x * u.Transform.z + u.Transform.x, aPos.y*u.Transform.z + u.Transform.y, aPos.z);
	v.Color = vec3(aColor.r, aColor.g, aColor.b);
	gl_Position = vec4(v.Position, 1.0f);
}
