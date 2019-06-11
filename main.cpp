
#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <math.h>
#ifndef QT_NO_OPENGL
#include <QTimer>

#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#endif

int main(int argc, char *argv[])
{
//   std:: cout<<"ello"<<std::endl;
    QApplication app(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
        w.show();
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
   // MainWidget widget;
  // widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif


    return app.exec();
}
