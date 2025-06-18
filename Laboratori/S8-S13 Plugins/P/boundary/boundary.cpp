#include "boundary.h"
#include "glwidget.h"

void Boundary::onPluginLoad()
{
	sceneInfo();
}

void Boundary::sceneInfo(){
    Scene *s = scene();
    int obj = s->objects().size();
    
    // Process each object in the scene
    for(int i = 0; i < obj; i++){
        const Object &o = s->objects()[i];
        int objF = (int)o.faces().size();
        int objV = (int)o.vertices().size();
        
        // Map to count how many times each edge appears
        map<pair<int, int>, int> edgeCount;
        
        // For each face in this object
        for(int f = 0; f < objF; f++){
            const Face &face = o.faces()[f];
            int vertexInFace = face.numVertices();
            
            // Process each edge in the face
            for(int v = 0; v < vertexInFace; v++){
                int v0 = face.vertexIndex(v);
                int v1 = face.vertexIndex((v + 1) % vertexInFace);
                
                // Create edge with smaller vertex index first to avoid duplicates
                pair<int, int> edge;
                if(v0 < v1) {
                    edge = make_pair(v0, v1);
                } else {
                    edge = make_pair(v1, v0);
                }
                
                // Increment count for this edge
                edgeCount[edge]++;
            }
        }
        
        // Count total edges and boundary edges
        int totalEdges = edgeCount.size();
        int boundaryEdges = 0;
        
        for(const auto& entry : edgeCount){
            if(entry.second == 1){  // Edge appears in only one face
                boundaryEdges++;
            }
        }
        
        // Print results for this object
        cout << "E =" << totalEdges << endl;
        cout << "Border =" << boundaryEdges << endl;
    }
}

void Boundary::preFrame()
{
	
}

void Boundary::postFrame()
{
	
}

void Boundary::onObjectAdd()
{
	sceneInfo();
}

bool Boundary::drawScene()
{
	return false; // return true only if implemented
}

bool Boundary::drawObject(int)
{
	return false; // return true only if implemented
}

bool Boundary::paintGL()
{
	return false; // return true only if implemented
}

void Boundary::keyPressEvent(QKeyEvent *)
{
	
}

void Boundary::mouseMoveEvent(QMouseEvent *)
{
	
}

