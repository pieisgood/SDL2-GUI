#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;
smooth out vec4 theColor;
uniform vec2 offset;
uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;
uniform mat4 transMatrix;

void main(){
	vec4 cameraPos = vec4(position, 1.0);
	//vec4 cameraPos = position;
	gl_Position = perspectiveMatrix * viewMatrix  * cameraPos;
	theColor =  vec4(norm, 1.0); 
}