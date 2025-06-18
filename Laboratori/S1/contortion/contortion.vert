#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    float a = (vertex.y - 0.5) * sin(time);
    mat3 Rotate = mat3(
                    vec3(1, 0, 0),
                    vec3(0, cos(a), sin(a)),
                    vec3(0, -sin(a), cos(a)));
    frontColor = vec4(color,1.0);
    vec3 v = vertex + vec3(0, 1, 0);
    if(vertex.y > 0.5) v *= Rotate;
    v += vec3(0, 1, 0);
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
