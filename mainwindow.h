/*!
  *\file plik zawierający klasę mainWindow
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Dialog* dialog;

private slots:
    /*!
     * \brief readserial połaczony jest z sygnałem read, który po wywołaniu wykonuje metodę slot
     */
    void readserial();
    void handlePlay();
    void handleStop();
    void xyz(int x, int y);
};

#endif // MAINWINDOW_H
