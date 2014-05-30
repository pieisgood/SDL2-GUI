#version 330

layout (location=0) in vec2 vert_pos;
layout (location=1) in vec2 vert_texcoord;
uniform vec2 text_pos;
out vec2 st;

void main() {
	st = vert_texcoord;
	gl_Position = vec4(vert_pos + text_pos, -1.0, 1.0);
}