#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float time;
uniform sampler2D sampler;

void main()
{
    fragColor = texture(sampler, vtexCoord);
    if(fract(time) > 0.5 && distance(vtexCoord, vec2(0.393,0.652)) <= 0.025){
        fragColor = texture(sampler, vtexCoord + vec2(0.057, -0.172));
    }
}
