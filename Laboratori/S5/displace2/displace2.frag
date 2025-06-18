#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float smoothness = 25.0;
uniform sampler2D heightMap;

uniform mat3 normalMatrix;

in vec2 st;
in vec2 vtexCoord;

float epsilon = 1.0/128;

void main()
{
	float fx =  texture(heightMap, st).r;
	
	vec2 stex = vec2(st.s + epsilon, st.t);
	vec2 stey = vec2(st.s, st.t + epsilon);
	
	float x = (texture(heightMap, stex).r - fx) / epsilon;
	float y = (texture(heightMap, stey).r - fx) / epsilon;
	vec2 G = vec2(x, y); 
	vec3 NG = normalize(normalMatrix * normalize(vec3(-G.x, -G.y, smoothness)));
	
    fragColor = vec4(NG.z);
}
