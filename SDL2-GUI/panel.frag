#version 330
in vec2 texture_coords;
uniform sampler2D panel_texture;
uniform int sub;
out vec4 fragColor;


void main(){
	vec4 texel = texture2D(panel_texture, texture_coords);
	if(texel.a == 0.0){
		discard;
	}
	if(sub == 1){
		texel = texel + texture_coords.y*(vec4(1.0,1.0,1.0,1.0));
	}
	if(sub == 2){
		texel = texel - (1-texture_coords.y)*(vec4(1.0,1.0,1.0,0.0));
	}

	fragColor = texel; 
}