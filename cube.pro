QT       += core gui widgets serialport printsupport

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    dialog.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    dialog.h \
    figure.h \
    mainwidget.h \
    geometryengine.h \
    mainwindow.h \
    wykres.h \
    qcustomplot.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

FORMS += \
    mainwindow.ui
