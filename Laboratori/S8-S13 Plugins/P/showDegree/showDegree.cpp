#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	Scene *s = scene();
	Object &o = s->objects()[0];
	int nVert = (int)o.vertices().size();
	int nFace = (int)o.faces().size();
	int sumatoryVertices = 0;
	
	for(int i = 0; i < nFace; i++){
	    const Face &f = o.faces()[i];
	    int vertex = f.numVertices();
	    sumatoryVertices += vertex;
	}
	
	degree = float(sumatoryVertices) / nVert;
	
	cout << "El grau mitjà de cada vertex és " << degree << endl;
}


void ShowDegree::preFrame()
{
	
}

void ShowDegree::postFrame()
{
	painter.begin(glwidget());
    QFont font;
    font.setPixelSize(25);
    painter.setFont(font);
    //painter.setPen(QColor(255,0,0));
    int x = 20;
    int y = 20;
    painter.drawText(x, y+40, QString(" - Grau Mitjà: %1").arg(degree));
    painter.end();
}

void ShowDegree::onObjectAdd()
{
	
}

bool ShowDegree::drawScene()
{
	return false; // return true only if implemented
}

bool ShowDegree::drawObject(int)
{
	return false; // return true only if implemented
}

bool ShowDegree::paintGL()
{
	return false; // return true only if implemented
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{
	
}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{
	
}

