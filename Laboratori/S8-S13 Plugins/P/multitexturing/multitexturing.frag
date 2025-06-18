#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;

void main()
{

    fragColor = mix(texture(sampler0, vtexCoord), texture(sampler1, vtexCoord), 0.5);
}
