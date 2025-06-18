#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;

in vec4 vfrontColor[];
in vec3 N[];
out vec4 gfrontColor;

uniform float speed = 1.2;
uniform float time;

void main( void )
{
	vec3 N2 = N[0] + N[1] + N[2];
	N2 /= 3;
	//N2 = normalize(N2);
	
	for( int i = 0 ; i < 3 ; i++ )
	{
	
		gfrontColor = vfrontColor[i];
			
		float F = speed * time;
		
		vec4 vTransp = vec4(F * N2, 0) + gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix * vTransp;
		EmitVertex();
	}
    EndPrimitive();
}
