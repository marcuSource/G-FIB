#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 

class DrawBoundingBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
	QOpenGLShaderProgram *program;
	QOpenGLShader *fs, *vs;
	GLuint VAO_box;
	
	void createBox(GLWidget &w);
	void linkShaders();
	void drawBox(GLWidget &w, const Box &box);
	
};

#endif
