#include "mainwidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(nullptr),
    angularSpeed(0)



{
QTimer czas;
connect(&czas, SIGNAL(timeout()),this,SLOT(okres()));
czas.start(20);
}



MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

void MainWidget::okres(){



}


void MainWidget::abc(int x, int y){

    //qDebug()<<x<<endl;
    //qDebug()<<y<<endl;

    rotacja.setToIdentity();
    rotacja.rotate(y/100,QVector3D(1,0,0));
    rotacja.rotate(x/100,QVector3D(0,0,1));
     rotacja.scale(40.0,2.0,10.0);
    przesun.setToIdentity();
    przesun.scale(3,3,3);
    przesun.translate(0,2,0);
if(y>0){
    if(y<500)przesun.translate(QVector3D(-x/100,y/1000,-y/200));
  else przesun.translate(QVector3D(-x/100,y/1000,y/200));
}
else if(y<=0)przesun.translate(QVector3D(-x/100,y/1000,y/200));

// scale for ball
 geometries->ruch(przesun);

 qDebug()<<state;
 if(state == true){
 update();
 qDebug()<<"updating";
 }
}




void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1, 1, 1, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures()
{
    // Load plate.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored()); // plate texture
 //  texture = new QOpenGLTexture(QImage(":/ball.png").mirrored()); // ball texture
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();






    // Calculate model view transformation
    //QMatrix4x4 matrix;
    //matrix.translate(0.0, 0.0, 0.0);
    //matrix.rotate(rotation);
   // matrix.rotate(M_PI/6,QVector3D(0,1,0));
   //matrix.scale(40.0,4.0,25);// scale for plate

   QMatrix4x4 camera;
  camera.lookAt(QVector3D(0.0,0.3,-0.3),QVector3D(0.0,0.0,0.0),QVector3D(0.0,0.0,1.0));
    // Set modelview-projection matrix
 QMatrix4x4 projection;
 projection.ortho(-50,50,-50,50,-50,50);

 program.setUniformValue("mvp_projection", projection);
  program.setUniformValue("camera", camera);
program.setUniformValue("mvp_matrix", rotacja);



    //program.setUniformValue("matrix1", projection * matrix1);
    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
}
