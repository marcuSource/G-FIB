#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D colormap;

//Cada coordenada correspondra a una figura
const vec2 segm = vec2(1/4.0, 1/4.0);


void main()
{
    int Cx = int(vtexCoord.s * 15.0);
	int Cy = int(vtexCoord.t * 15.0);
	
	float x, y, figura;
    x = fract(vtexCoord.s * 15.0);
	y = fract(vtexCoord.t * 15.0);
    vec2 coord;
    
    //Nau
    if(Cx == 6.0 && Cy == 2.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x + 0.75, y + 0.25);
        
        fragColor = texture(colormap, coord);
    }
    
    //Bunker
    else if(Cx % 4 == 1 && Cy == 3.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x + 0.75, y);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (0,0)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 5.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x, y);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (0,1)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 6.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x, y + 0.25);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (0,2)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 7.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x, y + 0.5);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (0,3)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 8.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x, y + 0.75);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (1,0)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 9.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x+0.25, y);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (1,1)
    else if(Cx >= 1.0 && Cx <= 13 && Cy == 10.0){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x+0.25, y+0.25);
        
        fragColor = texture(colormap, coord);
    }
    
    //Alien (2,3)
    else if(Cx >= 1.0 && Cx <= 13 && Cy >= 11.0 && Cy <= 13 && ((Cx % 2 == 1 && Cy % 2 == 1) || ((Cx % 2 == 0 && Cy % 2 == 0))) ){
        x = x/4.0;
        y = y/4.0;
        coord = vec2(x+0.5, y+0.75);
        
        fragColor = texture(colormap, coord);
    }
    
    
       
    else fragColor = vec4(0,0,0,1);
    
    
}
