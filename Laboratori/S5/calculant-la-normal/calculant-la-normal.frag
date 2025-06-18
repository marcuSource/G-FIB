#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 vec;

void main()
{
    vec3 N = normalize(cross(dFdx(vec), dFdy(vec)));
    fragColor = frontColor * N.z;
}
