#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform vec3 RED = vec3(1,0,0);
uniform vec3 WHITE = vec3(1,1,1);
uniform bool classic;
uniform int rays = 16;

const float PI = 3.14159265;


void main()
{

    vec2 C = vec2(0.5, 0.5);
    float R = 0.2;
    float dist = distance(vtexCoord, C);
    
    float w = 0.7 * length(vec2(dFdx(dist), dFdy(dist)));
    
    float t = step(R,dist);
    
    vec3 color = mix(RED, WHITE, t);
    fragColor = vec4(color, 1);
    
    if(!classic){
        float phi = PI/rays;
        vec2 u = vtexCoord - C;
        float theta = atan(u.s, u.t);
        if( mod((theta/phi + 0.5), 2) < 1) fragColor = vec4(RED, 1);
    }
}
