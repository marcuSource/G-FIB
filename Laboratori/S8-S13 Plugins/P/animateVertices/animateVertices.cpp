#include "animateVertices.h"
#include "glwidget.h"
#include <QCoreApplication>

const int SHADOW_MAP_WIDTH = 512;
const int SHADOW_MAP_HEIGHT = 512;

void AnimateVertices::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("/../animate-vertices1/animate-vertices1.vert");
    //cout << "vs" << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("/../animate-vertices1/animate-vertices1.frag");
    //cout << "fs" << endl;
 
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    if (!program->isLinked()) cout << "Shader link error" << endl;

    elapsedTimer.start();
}


void AnimateVertices::preFrame()
{
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0));
    program->setUniformValue("amplitude", 0.1f);
    program->setUniformValue("freq", 1);

}

void AnimateVertices::postFrame()
{
    program->release();
}

void AnimateVertices::onObjectAdd()
{
	
}

bool AnimateVertices::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{
	
}

