#ifndef _TEXTSPLATING_H
#define _TEXTSPLATING_H

#include "plugin.h" 

class TextSplating: public QObject, public Plugin
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
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
    GLuint textureId0, textureId1, textureId2;
};

#endif
