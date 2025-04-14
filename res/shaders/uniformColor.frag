#version 330

struct VertexData {
	vec3 Position;
	vec3 Color;
};

struct Uniforms {
	vec2 Transform;
	vec3 Color;
};

in VertexData v;
uniform Uniforms u;
out vec4 FragColor;

void main() {
	FragColor = vec4(u.Color, 1.0f);
}
