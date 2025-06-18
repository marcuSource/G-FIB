#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;


uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // (sempre estarà en eye space)
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

vec4 light(vec3 N, vec3 V, vec3 L){

	vec3 R = normalize( 2.0 * dot(N, L)*N - L );
	float NdotL= max( 0.0, dot(N, L) );
	float RdotV= max( 0.0, dot(R, V) );
	float Idiff= NdotL;
	float Ispec= 0;
	if (NdotL>0) Ispec=pow(RdotV, matShininess);
	return matAmbient * lightAmbient + matDiffuse * lightDiffuse * Idiff + matSpecular * lightSpecular * Ispec;
	
}

void main(){

	vec3 P = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
	vec3 N = normalize(normalMatrix* normal);
	vec3 V = normalize(-P);
	vec3 L = normalize(lightPosition.xyz - P);
	frontColor= light(N, V, L);
	gl_Position= modelViewProjectionMatrix * vec4(vertex, 1.);
	

}
