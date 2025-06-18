#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 N;

void main()
{
	vec3 newColor = (N + 1) / 2;
    fragColor = vec4(newColor, 1);
}
