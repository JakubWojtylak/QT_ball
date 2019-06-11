/*!
  *\file plik przechowujący funkcje z bilbioteki OpenGL
  */

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>



class GeometryEngine;
/*!
 * \brief The MainWidget class
 */
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
        bool state;
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:


    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QOpenGLTexture *texture;
    float predkoscX;
    float predkoscY;
    QMatrix4x4 projection;
    QMatrix4x4 rotacja;
    QMatrix4x4 przesun;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

public slots:
    void okres();
    void abc(int x,int y);
};

#endif // MAINWIDGET_H
