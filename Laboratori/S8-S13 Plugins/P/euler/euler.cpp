#include "euler.h"
#include "glwidget.h"


void Euler::onPluginLoad()
{
    Scene *s = scene();
    int obj = s->objects().size();
    
    int F = 0;  // Total faces
    int V = 0;  // Total vertices
    int E = 0;  // Total edges
    
    // Process each object in the scene
    for(int i = 0; i < obj; i++){
        const Object &o = s->objects()[i];
        int objF = (int)o.faces().size();
        int objV = (int)o.vertices().size();
        int objE = 0;  // Initialize edge count for this object
        
        // Calculate edges using adjacency matrix approach
        vector<vector<bool>> adjacencyMatrix(objV, vector<bool>(objV, false));
        
        // For each face in this object
        for(int f = 0; f < objF; f++){
            const Face &face = o.faces()[f];
            int vertexInFace = face.numVertices();
            
            // Connect consecutive vertices in the face
            for(int v = 0; v < vertexInFace; v++){
                int v0 = face.vertexIndex(v);
                int v1 = face.vertexIndex((v + 1) % vertexInFace);
                
                // Mark edge if not already counted
                if(adjacencyMatrix[v0][v1] == false){
                    adjacencyMatrix[v0][v1] = true;
                    adjacencyMatrix[v1][v0] = true;
                    objE++;
                }
            }
        }
        
        // Add to totals
        F += objF;
        V += objV;
        E += objE;
    }
    
    // Calculate Euler characteristic
    int X = V - E + F;
    
    cout << "The scene currently has: " << endl;
    cout << F << " Faces" << endl;
    cout << V << " Vertices" << endl;
    cout << E << " Edges" << endl;
    cout << "And an Euler's characteristic of " << X << endl;
}

void Euler::preFrame()
{
	
}

void Euler::postFrame()
{
	
}

void Euler::onObjectAdd()
{
    Scene *s = scene();
    int obj = s->objects().size();
    
    int F = 0;  // Total faces
    int V = 0;  // Total vertices
    int E = 0;  // Total edges
    
    // Process each object in the scene
    for(int i = 0; i < obj; i++){
        const Object &o = s->objects()[i];
        int objF = (int)o.faces().size();
        int objV = (int)o.vertices().size();
        int objE = 0;  // Initialize edge count for this object
        
        // Calculate edges using adjacency matrix approach
        vector<vector<bool>> adjacencyMatrix(objV, vector<bool>(objV, false));
        
        // For each face in this object
        for(int f = 0; f < objF; f++){
            const Face &face = o.faces()[f];
            int vertexInFace = face.numVertices();
            
            // Connect consecutive vertices in the face
            for(int v = 0; v < vertexInFace; v++){
                int v0 = face.vertexIndex(v);
                int v1 = face.vertexIndex((v + 1) % vertexInFace);
                
                // Mark edge if not already counted
                if(adjacencyMatrix[v0][v1] == false){
                    adjacencyMatrix[v0][v1] = true;
                    adjacencyMatrix[v1][v0] = true;
                    objE++;
                }
            }
        }
        
        // Add to totals
        F += objF;
        V += objV;
        E += objE;
        
    }
    
    // Calculate Euler characteristic
    int X = V - E + F;
    
    cout << "The scene currently has: " << endl;
    cout << F << " Faces" << endl;
    cout << V << " Vertices" << endl;
    cout << E << " Edges" << endl;
    cout << "And an Euler's characteristic of " << X << endl;
    
}

bool Euler::drawScene()
{
    return false; // return true only if implemented
}

bool Euler::drawObject(int)
{
	return false; // return true only if implemented
}

bool Euler::paintGL()
{
	return false; // return true only if implemented
}

void Euler::keyPressEvent(QKeyEvent *)
{
	
}

void Euler::mouseMoveEvent(QMouseEvent *)
{
	
}

