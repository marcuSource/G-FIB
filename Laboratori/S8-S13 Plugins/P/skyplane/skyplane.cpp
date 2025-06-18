#include "skyplane.h"
#include "glwidget.h"

void Skyplane::onPluginLoad()
{
    GLWidget &w = *glwidget();
    w.makeCurrent();
    
    //sky shaders
    //sky.vert
    skyvs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    skyvs->compileSourceFile("sky.vert");
    cout << "VS log: " << skyvs->log().toStdString();
    
    //sky.frag
    skyfs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    skyfs->compileSourceFile("sky.frag");
    cout << "FS log: " << skyfs->log().toStdString();
    
    // Program
    skyProgram = new QOpenGLShaderProgram(this);
    skyProgram->addShader(skyvs);
    skyProgram->addShader(skyfs);
    skyProgram->link();
    
    //mirror shaders
    //mirror.vert
    mirvs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    mirvs->compileSourceFile("mirror.vert");
    cout << "VS log: " << mirvs->log().toStdString();
    
    //mirror.frag
    mirfs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    mirfs->compileSourceFile("mirror.frag");
    cout << "FS log: " << mirfs->log().toStdString();
    
    // Program
    mirrorProgram = new QOpenGLShaderProgram(this);
    mirrorProgram->addShader(mirvs);
    mirrorProgram->addShader(mirfs);
    mirrorProgram->link();
    
    //Load Texture 0
    QString filename = QFileDialog::getOpenFileName(0, "Open Image 1", "/Desktop/G/Viwer/plugins/reflection", "Image file (*.png *.jpg)");    
    QImage img0(filename);    
    QImage im0 = img0.convertToFormat(QImage::Format_RGB32).rgbSwapped().mirrored();
    w.makeCurrent();
    w.glActiveTexture(GL_TEXTURE0);
    w.glGenTextures(1, &textureId0);
    w.glBindTexture(GL_TEXTURE_2D, textureId0);
    w.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    w.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    w.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    w.glBindTexture(GL_TEXTURE_2D, 0);
}
 
void drawRect(GLWidget &w)
{
    // Crear el VAO per al rectangle
    GLuint VAOrect;
    w.glGenVertexArrays(1, &VAOrect);
    w.glBindVertexArray(VAOrect);
    
    // Coordenades dels vèrtexs del rectangle en ClipSpace
    // El rectangle estarà al far plane (z = 1.0 en clip space)
    float coords[] = {
        -1.0f, -1.0f, 1.0f,  // V0 - Inferior esquerra
         1.0f, -1.0f, 1.0f,  // V1 - Inferior dreta
        -1.0f,  1.0f, 1.0f,  // V2 - Superior esquerra
         1.0f,  1.0f, 1.0f   // V3 - Superior dreta
    };
    
    // Coordenades de textura
    float texCoords[] = {
        0.0f, 0.0f,  // V0
        1.0f, 0.0f,  // V1
        0.0f, 1.0f,  // V2
        1.0f, 1.0f   // V3
    };
    
    // VBO per a les coordenades
    GLuint VBOcoords;
    w.glGenBuffers(1, &VBOcoords);
    w.glBindBuffer(GL_ARRAY_BUFFER, VBOcoords);
    w.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    w.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    w.glEnableVertexAttribArray(0);
    
    // VBO per a les coordenades de textura
    GLuint VBOtexCoords;
    w.glGenBuffers(1, &VBOtexCoords);
    w.glBindBuffer(GL_ARRAY_BUFFER, VBOtexCoords);
    w.glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    w.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    w.glEnableVertexAttribArray(1);
    
    // Desenllaçar VAO
    w.glBindVertexArray(0);
    w.glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    w.glBindVertexArray(VAOrect);
    w.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    w.glBindVertexArray(0);
    
    // 3. Clean up
    w.glDeleteBuffers(1, &VBOcoords);
    w.glDeleteVertexArrays(1, &VAOrect);
}

void Skyplane::preFrame()
{
    
}

void Skyplane::postFrame()
{
    
}

void Skyplane::onObjectAdd()
{
    
}

bool Skyplane::drawScene()
{
    return false; // return true only if implemented
}

bool Skyplane::drawObject(int)
{
    return false; // return true only if implemented
}

bool Skyplane::paintGL()
{
    GLWidget &w = *glwidget();
    
    // Guardar l'estat actual del depth test
    GLboolean depthTestEnabled;
    w.glGetBooleanv(GL_DEPTH_TEST, &depthTestEnabled);
    
    // 1. Desactivar el depth test per dibuixar el cel (sempre al fons)
    w.glDisable(GL_DEPTH_TEST);
    
    // Utilitzar els shaders del cel (sky.vert i sky.frag)
    skyProgram->bind();
    
    // Configurar la textura pel cel
    w.glActiveTexture(GL_TEXTURE0);
    w.glBindTexture(GL_TEXTURE_2D, textureId0);
    skyProgram->setUniformValue("modelViewProjectionMatrix", w.camera()->projectionMatrix() * w.camera()->viewMatrix());
    skyProgram->setUniformValue("modelViewMatrix", w.camera()->viewMatrix());
    skyProgram->setUniformValue("sampler0", 0);
    
    // Dibuixar el rectangle del cel
    drawRect(w);
     
    skyProgram->release();
    
    // 2. Restaurar l'estat del depth test per dibuixar els objectes
    if (depthTestEnabled)
        w.glEnable(GL_DEPTH_TEST);
    
    // Utilitzar els shaders del mirall (mirror.vert i mirror.frag)
    mirrorProgram->bind();
    
    // Assignar els uniforms
    mirrorProgram->setUniformValue("modelViewProjectionMatrix", w.camera()->projectionMatrix() * w.camera()->viewMatrix());
    mirrorProgram->setUniformValue("modelViewMatrix", w.camera()->viewMatrix());
    mirrorProgram->setUniformValue("sampler0", 0);
     
    // Delegar el dibuix de l'escena a altres plugins si n'hi ha
    if (drawPlugin()) drawPlugin()->drawScene();
    
    mirrorProgram->release();
    
    // Desactivar la textura quan hagis acabat
    w.glBindTexture(GL_TEXTURE_2D, 0);
    
    return true;
}

void Skyplane::keyPressEvent(QKeyEvent *)
{
    
}

void Skyplane::mouseMoveEvent(QMouseEvent *)
{
    
}
