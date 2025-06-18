#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2  vtexCoord;

uniform vec4 BLACK = vec4(0,0,0,1);
uniform vec4 LIGHT_GRAY = vec4(0.8);

void main()
{
    float x = int(mod(fract(vtexCoord.x) * 8, 2));
    float y = int(mod(fract(vtexCoord.y) * 8, 2));
    
    if(x == y)
    fragColor = LIGHT_GRAY;
    
    else fragColor = BLACK ;
}
