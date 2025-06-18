#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform vec3 RED = vec3(1,0,0);
uniform vec3 WHITE = vec3(1,1,1);

void main()
{

    vec2 C = vec2(0.5, 0.5);
    float R = 0.2;
    float dist = distance(vtexCoord, C);
    
    float w = 0.7 * length(vec2(dFdx(dist), dFdy(dist)));
    
    float t = step(R,dist);
    
    vec3 color = mix(RED, WHITE, t);
    fragColor = vec4(color, 1);
    
}
