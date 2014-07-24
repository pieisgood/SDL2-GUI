#version 330

in vec2 st;

uniform sampler2D tex;
uniform vec4 text_color;
out vec4 frag_color;

const float smoothing = 1.0/16.0;

void main() {
    float distance = texture2D(tex, st).a;
    float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
	frag_color = vec4(text_color.rgb, alpha*text_color.a);

	//frag_color.a *= smoothstep(1.0, 0.99, distance);
}
