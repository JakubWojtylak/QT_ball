/*!
  *\file
  * \brief Plik z metodami do generowania figur

*/

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "figure.h"
/*!
 * \brief Klasa generowanej płytki i kuli
 */
class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();
    /*!
     * \brief drawCubeGeometry - powoduje wyrysowanie obiektu na scenie 3D
     * \param program - wskaźnik na shader, z którym ma się połaczyć aplikacja
     */
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void ruch(QMatrix4x4 a){przesun = a;}

private:
    /*!
     * \brief initCubeGeometry - stworzenie obiektów grafiki 3D
     */
    void initCubeGeometry();

    /*!
     * \brief array - bufor przechowujący punkty kuli
     */
    QOpenGLBuffer array;
    /*!
     * \brief arrayBuf - bufor przechowujący punkty płytki
     */
    QOpenGLBuffer arrayBuf;
    /*!
     * \brief indexBuf - bufor określający kolejność rysowania punktów
     */
    QOpenGLBuffer indexBuf;
    QMatrix4x4 przesun;

};

#endif // GEOMETRYENGINE_H
