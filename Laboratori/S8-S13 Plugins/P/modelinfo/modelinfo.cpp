#include "modelinfo.h"
#include "glwidget.h"

void Modelinfo::onPluginLoad()
{
	
}

void Modelinfo::preFrame()
{
	
}

void Modelinfo::postFrame()
{
	Scene *s = scene();
	int obj = s->objects().size();
	int pol = 0;
	int vert = 0;
	int percV = 0;
	
	for(int i = 0; i < obj; i++){
	    const Object &o = s->objects()[i];
	    for(int j = 0; j < (int)o.faces().size(); j++){
	        const Face &f = o.faces()[j];
	        int auxV = f.numVertices();
	        vert += auxV;
	        if(auxV == 3) ++percV;
	        ++pol;
	    }
	}
	cout << "Current Scene has:" << endl;
	cout << "Number of Objects = " << obj << endl;
	cout << "Number of Polygons = " << pol << endl;
	cout << "Number of Vertexs = " << vert << endl;
	cout << "Percentage of Vertex = " << float(percV)/pol << endl;
	
}

void Modelinfo::onObjectAdd()
{
	
}

bool Modelinfo::drawScene()
{
	return false; // return true only if implemented
}

bool Modelinfo::drawObject(int)
{
	return false; // return true only if implemented
}

bool Modelinfo::paintGL()
{
	return false; // return true only if implemented
}

void Modelinfo::keyPressEvent(QKeyEvent *)
{
	
}

void Modelinfo::mouseMoveEvent(QMouseEvent *)
{
	
}

