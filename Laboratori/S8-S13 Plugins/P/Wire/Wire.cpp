#include "Wire.h"
#include "glwidget.h"

void Wire::onPluginLoad()
{
	GLWidget & g = *glwidget();
	g.makeCurrent();
	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("wire.vert");
    
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("wire.frag");
    
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
}

void Wire::preFrame()
{
	/*program->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    program->setUniformValue("mode", 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
}

void Wire::postFrame()
{
	program->release();
}

void Wire::onObjectAdd()
{
	
}

bool Wire::drawScene()
{
	return false; // return true only if implemented
}

bool Wire::drawObject(int)
{
	return false; // return true only if implemented
}

bool Wire::paintGL()
{
    
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    
    // Primera passada: pintar l'objecte amb colors normals (blanc i negre basat en normals)
    program->setUniformValue("mode", 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawPlugin()->drawScene();
    
    // Segona passada: pintar les línies dels triangles en negre
    program->setUniformValue("mode", 2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonOffset(-1.0, -1.0);  // Negatiu per posar les línies per davant
    drawPlugin()->drawScene();
    
    // Restaurar estat
    glDisable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    program->release();
    
    return true;
}

void Wire::keyPressEvent(QKeyEvent *)
{
	
}

void Wire::mouseMoveEvent(QMouseEvent *)
{
	
}

