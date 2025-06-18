#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::linkShaders()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("drawBoundingBox.vert");
	cout << "VS log: " << vs->log().toStdString();
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("drawBoundingBox.frag");
	cout << "FS log: " << fs->log().toStdString();
	
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Program log: " << program->log().toStdString();
}

void DrawBoundingBox::createBox(GLWidget &w)
{
	w.glGenVertexArrays(1, &VAO_box);
	w.glBindVertexArray(VAO_box);
	float coords[] = {
		1, 1, 0,	 0, 1, 0,
		1, 0, 0,	 0, 0, 0,
		0, 0, 1,	 0, 1, 0,
		0, 1, 1,	 1, 1, 0,
		1, 1, 1,	 1, 0, 0,
		1, 0, 1,	 0, 0, 1,
		1, 1, 1,	 0, 1, 1
	};
	
	GLuint VBO_coords;
	w.glGenBuffers(1, &VBO_coords);
	w.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	w.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	w.glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	w.glEnableVertexAttribArray(0);
	w.glBindVertexArray(0);
}

void DrawBoundingBox::drawBox(GLWidget &w, const Box &box)
{
	const Point &translate = box.min();
	const Point & scale = box.max() - box.min();
	program->bind();
	QMatrix4x4 MVP = w.camera()->projectionMatrix() *w.camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	program->setUniformValue("translate", translate);
	program->setUniformValue("scale", scale);
	w.glBindVertexArray(VAO_box);
	w.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	w.glBindVertexArray(0);
}

void DrawBoundingBox::onPluginLoad()
{
	GLWidget &w = * glwidget();
	w.makeCurrent();
	createBox(w);
	linkShaders();
	for (Object &o: w.scene()->objects())
		o.computeBoundingBox();
}

void DrawBoundingBox::preFrame()
{
	
}

void DrawBoundingBox::postFrame()
{
	GLWidget & w = * glwidget();
	w.makeCurrent();
	GLint polygonMode;
	w.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
	w.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (Object &o : w.scene()->objects())
		drawBox(w, o.boundingBox());
	w.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void DrawBoundingBox::onObjectAdd()
{
	GLWidget &w = *glwidget();
	w.makeCurrent();
	for (Object &o : w.scene()->objects())
		o.computeBoundingBox();
}

bool DrawBoundingBox::drawScene()
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::drawObject(int)
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::paintGL()
{
	return false; // return true only if implemented
}

void DrawBoundingBox::keyPressEvent(QKeyEvent *)
{
	
}

void DrawBoundingBox::mouseMoveEvent(QMouseEvent *)
{
	
}

