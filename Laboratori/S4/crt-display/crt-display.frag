#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
in vec2  vtexCoord;

uniform int n = 1;

void main()
{
    if(int(gl_FragCoord.y) % n == 0) fragColor = frontColor;
    else discard;
}
