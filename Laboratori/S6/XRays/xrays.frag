#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D foot0;
uniform sampler2D foot1;
uniform sampler2D foot2;
uniform sampler2D foot3;

const float R = 80.0;

uniform int layer = 3;

uniform vec2 mousePosition;
uniform bool virtualMouse = false;
uniform float mouseX, mouseY; 

vec2 mouse()
{
	if (virtualMouse) return vec2(mouseX, mouseY);
	else return mousePosition;
}

void main(){

	vec4 C, D;

	float d = distance(mouse(), gl_FragCoord.xy);
	
	if(d >= R){
		C = texture(foot0, vtexCoord);
		fragColor = C;
	}
	
	else if(d < R){
		
		if(layer == 1){
			D = texture(foot1, vtexCoord);
		}
		
		else if(layer == 2){
			D = texture(foot2, vtexCoord);
		}
		
		else if(layer == 3){
			D = texture(foot3, vtexCoord);
		}
		
		fragColor = mix(C, D, d/R);
	}
	
	

}

