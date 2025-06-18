#include "highlightObject.h"
#include "glwidget.h"

void HighlightObject::onPluginLoad()
{
	
}

void HighlightObject::preFrame()
{
	
}

void HighlightObject::postFrame()
{
	Scene *s = scene();
	int oSize = s->objects().size();
	seleccionat = scene()->selectedObject();
	
	if(seleccionat >= 0 && seleccionat < oSize){
	    // Get the selected object
        const Object& obj = s->objects()[seleccionat];
        
        // Get the bounding box
        Box box = obj.boundingBox();
        
	}

    //cout << "Objecte seleccionat: Obj[" << seleccionat << "]" << endl;

}

void HighlightObject::onObjectAdd()
{
	cout << "Objecte seleccionat: Obj[" << seleccionat << "]" << endl;
}

bool HighlightObject::drawScene()
{
	return false; // return true only if implemented
}

bool HighlightObject::drawObject(int)
{
	return false; // return true only if implemented
}

bool HighlightObject::paintGL()
{
	return false; // return true only if implemented
}

void HighlightObject::keyPressEvent(QKeyEvent *)
{
	
}

void HighlightObject::mouseMoveEvent(QMouseEvent *)
{
	
}

