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
    /*!
     * \brief state - zmienna odpowiadająca za zatrzymanie aplikacji
     */
        bool state;
        /*!
         * \brief reset - zmienna odpowiadająca za reset aplikacji
         */
        bool reset;
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void timerEvent(QTimerEvent *e) override;


    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;
    /*!
     * \brief obiekt tekstur
     */
    QOpenGLTexture *texture;
    /*!
     * \brief prędkość kulki wzdłuż osi X
     */
    float vX=0;
    /*!
     * \brief prędkość kulki wzdłuż osi y
     */
    float vY=0;
    /*!
     * \brief prędkość kulki wzdłuż osi y
     */
    float vZ=0;
    /*!
     * \brief Macierz widoku kamery
     */
    QMatrix4x4 projection;
    /*!
     * \brief Macierz rotacji płytki
     */
    QMatrix4x4 rotacja;
    /*!
     * \brief Macierz przesunięca kulki
     */
public:

    QMatrix4x4 przesun;

    QVector2D mousePressPosition;
    /*!
     * \brief wektor obrotu kamery
     */
    QVector3D rotationAxis;
    /*!
     * \brief prędkość obrotu kamery
     */
    qreal angularSpeed;
    QQuaternion rotation;


public slots:

    void abc(int x,int y);
};

#endif // MAINWIDGET_H
