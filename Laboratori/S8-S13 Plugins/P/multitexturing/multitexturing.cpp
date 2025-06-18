#include "multitexturing.h"
#include "glwidget.h"

void Multitexturing::onPluginLoad()
{
	GLWidget &w = *glwidget();
	w.makeCurrent();
	
	//VS
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("multitexturing.vert");
	cout << "VS log: " << vs->log().toStdString();
	
	//FS
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("multitexturing.frag");
	cout << "FS log: " << fs->log().toStdString();
	
	//Program
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Program log: " << program->log().toStdString();
	
	//Load Texture0
	QString filename = QFileDialog::getOpenFileName(0, "Open Image 1", "/Desktop/G/Viwer/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        w.makeCurrent();
	w.glActiveTexture(GL_TEXTURE0);
	w.glGenTextures( 1, &textureId0);
	w.glBindTexture(GL_TEXTURE_2D, textureId0);
	w.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	w.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	w.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	w.glBindTexture(GL_TEXTURE_2D, 0);
	
	// Load Texture1
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "//Desktop/G/Viwer/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        w.makeCurrent();
	w.glActiveTexture(GL_TEXTURE1);
	w.glGenTextures( 1, &textureId1);
	w.glBindTexture(GL_TEXTURE_2D, textureId1);
	w.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	w.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	w.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	w.glBindTexture(GL_TEXTURE_2D, 0);
}

void Multitexturing::preFrame()
{
    GLWidget &w = *glwidget();
	w.makeCurrent();

	// bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
    program->setUniformValue("modelViewProjectionMatrix", w.camera()->projectionMatrix() * w.camera()->viewMatrix());
    // bind textures
    w.glActiveTexture(GL_TEXTURE0);
    w.glBindTexture(GL_TEXTURE_2D, textureId0);
    w.glActiveTexture(GL_TEXTURE1);
    w.glBindTexture(GL_TEXTURE_2D, textureId1);
}

void Multitexturing::postFrame()
{
	GLWidget &w = *glwidget();
    w.makeCurrent();

    // bind default shaders
    w.defaultProgram()->bind();
    // unbind textures
    w.glActiveTexture(GL_TEXTURE0);
    w.glBindTexture(GL_TEXTURE_2D, 0);
    w.glActiveTexture(GL_TEXTURE1);
    w.glBindTexture(GL_TEXTURE_2D, 0);
}

void Multitexturing::onObjectAdd()
{
	
}

bool Multitexturing::drawScene()
{
	return false; // return true only if implemented
}

bool Multitexturing::drawObject(int)
{
	return false; // return true only if implemented
}

bool Multitexturing::paintGL()
{
	return false; // return true only if implemented
}

void Multitexturing::keyPressEvent(QKeyEvent *)
{
	
}

void Multitexturing::mouseMoveEvent(QMouseEvent *)
{
	
}

