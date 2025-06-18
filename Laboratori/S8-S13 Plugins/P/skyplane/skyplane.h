#ifndef SKYPLANE_H
#define SKYPLANE_H
#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Skyplane: public QObject, public Plugin
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
    QOpenGLShader *skyvs, *skyfs, *mirvs, *mirfs;
    QOpenGLShaderProgram *skyProgram, *mirrorProgram;
    GLuint textureId0;
};
#endif
