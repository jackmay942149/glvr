#version 330
out vec4 FragColor;
in vec3 vertexColor;
in vec4 gl_FragCoord;

uniform vec2 resolution;

void main() {
	FragColor = vec4(gl_FragCoord.x/resolution.x, gl_FragCoord.y/resolution.y, 0.0f, 1.0f);
}
