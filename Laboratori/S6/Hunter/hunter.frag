#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform vec2 mousePosition;
uniform vec2 viewport;

uniform sampler2D jungla;
uniform float magnific = 3;

vec4 blurImage( in vec2 coords )
{
    float Pi = 6.28318530718; // Pi*2
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 10.0; // BLUR SIZE (Radius)
   
    vec2 Radius = Size/viewport;

    vec4 Color = texture(jungla, coords);
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        float cd = cos(d);
        float sd = sin(d);
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture(jungla, coords+vec2(cd,sd)*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    return  Color;
}

void main()
{

   
    // Textura sin blurr
    if( (distance(mousePosition + vec2(80, 0), gl_FragCoord.xy) <= 105) || distance(mousePosition - vec2(80, 0), gl_FragCoord.xy) <= 105){
        
        fragColor = vec4(0,0,0,1);
        
        if( (distance(mousePosition + vec2(80, 0), gl_FragCoord.xy) <= 100) || distance(mousePosition - vec2(80, 0), gl_FragCoord.xy) <= 100){
            
            vec2 F = vtexCoord;
            vec2 mouseTexCoord = mousePosition / viewport;
            vec2 P = mix(mouseTexCoord, F,  1/magnific);
            fragColor = texture(jungla, P);
        }
        
    }
        
    // Textura con blurr
    else fragColor = blurImage(vtexCoord);
}
