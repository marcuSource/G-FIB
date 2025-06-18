#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float time;
uniform sampler2D fons;
uniform sampler2D noise1;

in vec2 vtexCoord;

void main()
{
    vec2 coordNoise;
    coordNoise.x = vtexCoord.s + 0.08 * time;
    coordNoise.y = vtexCoord.t + 0.07 * time;
    
    vec4 color = texture2D(noise1, coordNoise);
    float r, g;
    r = color.x;
    g = color.y;
    
    vec2 coordFons = vec2(vtexCoord) + vec2(r * 0.003, g * -0.005);
    
    
    fragColor =texture(fons, coordFons);
}
