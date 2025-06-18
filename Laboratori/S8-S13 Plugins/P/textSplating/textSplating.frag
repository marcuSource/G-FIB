#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;

void main()
{

    fragColor = mix(texture(sampler0, vtexCoord), texture(sampler1, vtexCoord), texture(sampler2, vtexCoord));
}
