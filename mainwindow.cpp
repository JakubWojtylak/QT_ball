#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwidget.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    dialog = new Dialog(this);
    ui->setupUi(this);
    ui->osX_lcdnumber->display("-----");
    ui->osY_lcdnumber->display("-----");

    ui->plot->addGraph();
    ui->plot->graph(0)->addData(0, 0);
    ui->plot->graph(0)->setPen(QPen(QColor(50,100,100)));
    ui->plot->addGraph();
     ui->plot->graph(1)->addData(0, 0);
       ui->plot->graph(1)->setPen(QPen(QColor(100,50,250)));
   QObject::connect(dialog, SIGNAL(read()), this, SLOT(readserial()));
  QObject::connect(dialog,SIGNAL(odczytano(int,int)),ui->openGLWidget, SLOT(abc(int , int )));
   QObject::connect(dialog,SIGNAL(odczytano(int,int)),this, SLOT(xyz(int , int )));

ui->label->setText("połączono");
ui->openGLWidget->state=0;
QObject::connect(ui->play,SIGNAL(pressed()),this, SLOT(handlePlay()));
QObject::connect(ui->stop,SIGNAL(pressed()),this, SLOT(handleStop()));
QObject::connect(ui->reset,SIGNAL(pressed()),this, SLOT(handleReset()));


QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
timeTicker->setTimeFormat("%h:%m:%s");


 // create graph and assign data to it:

//ui->plot->graph(1)->setData(t,x);
ui->plot->xAxis->setTicker(timeTicker);
 // give the axes some labels:
 ui->plot->xAxis->setLabel("t");
 ui->plot->yAxis->setLabel("y");
 // set axes ranges, so we see all data:
//ui->plot->xAxis->setRange(-1, 1);
ui-> plot->yAxis->setRange(-10000, 10000);
//ui-> plot->replot();
// calculate two new data points:

// make key axis range scroll with the data (at a constant range size of 8):

//connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
//ui->plot->replot();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readserial()
{
// qDebug()<<"dziala";
    dialog->readSerial(ui);

//qDebug()<<dialog->x_Axis;



}

void MainWindow::xyz(int x,int y)
{
    static QTime time(QTime::currentTime());
    ui->plot->graph(0)->addData(time.elapsed()/1000,x);
    ui->plot->graph(1)->addData(time.elapsed()/1000,y);
ui->plot->xAxis->setRange(time.elapsed()/1000,20,Qt::AlignRight);
ui->plot->replot();
}

void MainWindow::handlePlay()
{
    ui->openGLWidget->state=true;

    qDebug()<<"wznawianie aplikacji";
}
void MainWindow::handleStop()
{
    ui->openGLWidget->state=false;
    qDebug()<<"Zatrzymywanie aplikacji";

}
void MainWindow::handleReset(){

    qDebug()<<"zresetowano"<<endl;
    ui->openGLWidget->reset=true;

}
