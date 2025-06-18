#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 1;
vec4 BLACK = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
	
	if (mode == 1) fragColor = frontColor;
	
	else if(mode == 2) fragColor = BLACK;
    
}
