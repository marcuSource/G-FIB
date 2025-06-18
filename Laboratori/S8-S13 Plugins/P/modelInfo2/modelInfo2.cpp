#include "modelInfo2.h"
#include "glwidget.h"

void ModelInfo2::onPluginLoad()
{
	
}

void ModelInfo2::updateModelInfo()
{

}

void ModelInfo2::preFrame()
{
	
}

void ModelInfo2::postFrame()
{
	Scene* s = scene();
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
	        if(f.numVertices() % 3 == 0) ++percV;
	        ++pol;
	    }
	}
	
	painter.begin(glwidget());
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);
    //painter.setPen(QColor(255,0,0));
    int x = 20;
    int y = 350;

    painter.drawText(x, y, QString("INFO:"));
    painter.drawText(x, y+20, QString(" - Objectes: %1").arg(obj));
    painter.drawText(x, y+40, QString(" - Polígons: %1").arg(pol));
    painter.drawText(x, y+60, QString(" - Vèrtexs: %1").arg(vert));
    painter.drawText(x, y+80, QString(" - Triangles: %1").arg(percV));
    if (nPol!=0) painter.drawText(x, y+100, QString(" - Percentatge de triangles: %1%").arg(double(nTri/nPol) * 100));
    else painter.drawText(x, y+100, QString(" - Percentatge de triangles: NULL"));
    painter.end();
	
	
}

void ModelInfo2::onObjectAdd()
{
	
}

bool ModelInfo2::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo2::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo2::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo2::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo2::mouseMoveEvent(QMouseEvent *)
{
	
}

