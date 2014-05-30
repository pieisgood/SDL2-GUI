#version 330

layout (location=0) in vec2 vertex_position; 
uniform  vec2 pos;
uniform  vec2 scale;
uniform int check;
out vec2 texture_coords;

void main() {
	texture_coords = (vertex_position + 1.0) * 0.5;
	gl_Position = vec4((vertex_position * scale) + pos, -1.0, 1.0);
}

