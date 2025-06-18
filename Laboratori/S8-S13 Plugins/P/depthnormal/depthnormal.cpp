#include "depthnormal.h"
#include "glwidget.h"

void Depthnormal::onPluginLoad()
{
	GLWidget &w = *glwidget();
	w.makeCurrent();

	//Depth Shaders
	//VS
	vsD = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsD->compileSourceFile("depth.vert");
	cout << "VS log: " << vsD->log().toStdString();
	
	//FS 
	fsD = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fsD->compileSourceFile("depth.frag");
	cout << "FS log: " << fsD->log().toStdString();
	
	//Program
	programD = new QOpenGLShaderProgram(this);
	programD->addShader(vsD);
	programD->addShader(fsD);
	programD->link();
	cout << "Program log: " << programD->log().toStdString();
	
	//Normal Shaders
	//VS
	vsN = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsN->compileSourceFile("normal.vert");
	cout << "VS log: " << vsN->log().toStdString();
	
	//FS 
	fsN = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fsN->compileSourceFile("normal.frag");
	cout << "FS log: " << fsN->log().toStdString();
	
	//Program
	programN = new QOpenGLShaderProgram(this);
	programN->addShader(vsN);
	programN->addShader(fsN);
	programN->link();
	cout << "Program log: " << programN->log().toStdString();
}

void Depthnormal::preFrame()
{
	
}

void Depthnormal::postFrame()
{
	
}

void Depthnormal::onObjectAdd()
{
	
}

bool Depthnormal::drawScene()
{
	return false; // return true only if implemented
}

bool Depthnormal::drawObject(int)
{
	return false; // return true only if implemented
}

bool Depthnormal::paintGL()
{
    GLWidget &w = *glwidget();
    w.makeCurrent();
    
    // Redefinir la relació d'aspecte de la càmera
    float ar = (float)w.width() / w.height();
    camera()->setAspectRatio(ar);
    
    // Primer pas: Dibuixar amb shader de profunditat a la meitat esquerra
    glViewport(0, 0, w.width() / 2, w.height());
    
    // Activar el shader de profunditat
    programD->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programD->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 N = camera()->viewMatrix().normalMatrix();
    programD->setUniformValue("normalMatrix", N);
    
    // Dibuixar l'escena
    if (scene()) {
        for (int i = 0; i < (int)scene()->objects().size(); ++i) {
            const Object &obj = scene()->objects()[i];
            glPolygonMode(GL_FRONT_AND_BACK, obj.faces().size() < 1000 ? GL_LINE : GL_FILL);
            drawPlugin()->drawObject(i);
        }
    }
    
    // Segon pas: Dibuixar amb shader de normals a la meitat dreta
    glViewport(w.width() / 2, 0, w.width() / 2, w.height());
    
    // Activar el shader de normals
    programN->bind();
    programN->setUniformValue("modelViewProjectionMatrix", MVP);
    programN->setUniformValue("normalMatrix", N);
    
    // Dibuixar l'escena
    if (scene()) {
        for (int i = 0; i < (int)scene()->objects().size(); ++i) {
            const Object &obj = scene()->objects()[i];
            glPolygonMode(GL_FRONT_AND_BACK, obj.faces().size() < 1000 ? GL_LINE : GL_FILL);
            drawPlugin()->drawObject(i);
        }
    }
    
    // Restaurar el viewport complet
    glViewport(0, 0, w.width(), w.height());
    
    return true;
}

void Depthnormal::keyPressEvent(QKeyEvent *)
{
	
}

void Depthnormal::mouseMoveEvent(QMouseEvent *)
{
	
}

