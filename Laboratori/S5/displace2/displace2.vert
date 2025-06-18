#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform sampler2D heightMap;
uniform float scale = 0.05;

out vec2 st;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    
    st = 0.49 * vertex.xy + vec2(0.5);
    float desp = texture(heightMap, st).r * scale;
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex + (normalize(normal) * desp), 1.0);
}
