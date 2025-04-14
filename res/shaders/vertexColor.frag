#version 330

struct VertexData {
	vec3 Position;
	vec3 Color;
};

in VertexData v;
out vec4 FragColor;

void main() {
	FragColor = vec4(v.Color, 1.0f);
}
