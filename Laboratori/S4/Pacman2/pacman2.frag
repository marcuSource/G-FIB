#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D colormap;


// Textura: [0.0 -> Ghost, 1.0 -> Pac-Man, 2.0 -> Empty, 3.0 -> Wall, 4.0 -> Corner, 5.0 -> Dot]
const float segm = 1.0/6.0;

bool corner(int x, int y) {
	return (x == 0 && y == 0) || (x == 12 && y == 0) || (x == 0 && y == 12) || (x == 12 && y == 12);
}

void main()
{
    // Passant del rang [0..1] a [0..13]
	int Cx = int(vtexCoord.s * 13.0);
	int Cy = int(vtexCoord.t * 13.0);
    
    float x, y, figura;
    x = fract(vtexCoord.s * 13.0);
	y = fract(vtexCoord.t * 13.0);
    vec2 coord;
    
    if(corner(Cx, Cy)){
        // Bottom-Left Corner
        if(Cx == 0 && Cy == 0){
            x = 1 - x;
            y = 1 - y/6.0;
            figura = 5.0/6.0;
            coord = vec2(y + figura, x);
        }
        
        // Bottom-Right Corner
        else if(Cx == 12 && Cy == 0){
            x = x/6.0;
            y = 1 - y;
            figura = 4.0/6.0;
            coord = vec2(x + figura , y);
        }
        
        // Top-Left Corner
        else if(Cx == 0 && Cy == 12){
            x = - x/6.0;
            y = y;
            figura = 5.0/6.0;
            coord = vec2(x + figura, y);
        }
        
        // Top-Right Corner
        else if(Cx == 12 && Cy == 12){
            x = x/6.0;
            y = y;
            figura = 4.0/6.0;
            coord = vec2(x + figura, y);
        }
        
        fragColor = texture(colormap, coord);
    }
    
    // Vertical Border
    else if(Cx == 0 || Cx == 12){
        x = x;
        y = y/6.0;
        figura = 3.0/6.0;
        coord = vec2(y + figura, x);
        fragColor = texture(colormap, coord);
    }
    
    // Horizontal Border
    else if(Cy == 0 || Cy == 12){
        x = x/6.0;
        y = y;
        figura = 3.0/6.0;
        coord = vec2(x + figura, y);
        fragColor = texture(colormap, coord);
    }
    
    // Ghosts
    else if(Cy == 4 && (Cx == 1 || Cx == 5)){
        
        // Face Right
        if(Cx == 1){
            x = -x/6.0;
            y = y;
            figura = 1.0/6.0;
            coord = vec2(x + figura, y);
            fragColor = texture(colormap, coord);
        }
        
        // Face Left
        if(Cx == 5){
            x = x/6.0;
            y = y;
            figura = 0.0/6.0;
            coord = vec2(x + figura, y);
            fragColor = texture(colormap, coord);
        }
    }
    
    // Pac-Man
    else if(Cy == 4 && Cx == 4){
            x = x/6.0;
            y = y;
            figura = 1.0/6.0;
            coord = vec2(x + figura, y);
            fragColor = texture(colormap, coord);
    }
    
    // Map Walls
    else if(Cy % 2 == 1 && ((Cx >= 2 && Cx <= 5) || (Cx >= 7 && Cx <= 10))){
        x = x/6.0;
        y = y;
        figura = 3.0/6.0;
        coord = vec2(x + figura, y);
        fragColor = texture(colormap, coord);
    }
    
    else if(Cy == 4 && (Cx >= 6)){
        x = x/6.0;
        y = y;
        figura = 2.0/6.0;
        coord = vec2(x + figura, y);
        fragColor = texture(colormap, coord);
    }  
    
    // Fill with dots
    else{
        x = x/6.0;
        y = y;
        figura = 5.0/6.0;
        coord = vec2(x + figura, y);
        fragColor = texture(colormap, coord);
    }
   
}
