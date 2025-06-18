#ifndef _WIRE_H
#define _WIRE_H

#include "plugin.h" 

class Wire: public QObject, public Plugin
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
	QOpenGLShader *vs, *fs;
	QOpenGLShaderProgram *program;
	
};

#endif
