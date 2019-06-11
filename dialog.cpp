#include "dialog.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
    {

    discovery = new QSerialPort(this);
    serialBuffer = "";
    //parsed_data = "";
    x_Axis = 0.0;
    y_Axis = 0.0;


//     *  Testing code, prints the description, vendor id, and product id of all ports.
//     *  Used it to determine the values for the discovery uno.
//     *
//     *
    //qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
 //   foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
   //     qDebug() << "Description: " << serialPortInfo.description() << "\n";
     //   qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
       // qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
       // qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
       // qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";

// }



    /*
     *   Identify the port the discovery uno is on.
     */
    bool discovery_is_available = false;
    QString discovery_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the discovery uno
            if((serialPortInfo.productIdentifier() == discovery_product_id)
                    && (serialPortInfo.vendorIdentifier() == discovery_vendor_id)){
                discovery_is_available = true; //    discovery uno is available on this port
                discovery_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the discovery port if available
     */
    if(discovery_is_available){
        qDebug() << "Found the discovery port...\n";
        discovery->setPortName(discovery_port_name);
        discovery->open(QSerialPort::ReadOnly);
        discovery->setBaudRate(QSerialPort::Baud115200);
        discovery->setDataBits(QSerialPort::Data8);
        discovery->setFlowControl(QSerialPort::NoFlowControl);
        discovery->setParity(QSerialPort::NoParity);
        discovery->setStopBits(QSerialPort::OneStop);

        QObject::connect(discovery, SIGNAL(readyRead()), this, SIGNAL(read()));
        qDebug()<<"po read";


    }else{
        qDebug() << "Couldn't find the correct port for the discovery.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to discovery.");
    }
}

Dialog::~Dialog()
{
    if(discovery->isOpen()){
        discovery->close(); //    Close the serial port if it's open.
    }

}

void Dialog::readSerial(Ui::MainWindow * ui)
{
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */

            serialData = discovery->readAll();

          serialBuffer += QString::fromStdString(serialData.toStdString());
        //  qDebug()<<(serialBuffer.end()-1)->cell();
          if((serialBuffer.end()-1)->cell() == 10){

          QStringList bufferSplit = serialBuffer.split(" ");
//    if(bufferSplit.length()<1){
//        serialData = discovery->readAll();
//        serialBuffer += QString::fromStdString(serialData.toStdString());
    for(int i = 0 ; i<bufferSplit.length(); i++){
if(bufferSplit[i] == 'X'){
       // qDebug()<<bufferSplit;
        updateAxisX(bufferSplit[i+1], ui);
        updateAxisY(bufferSplit[i+2], ui);
        x_Axis= bufferSplit[i+1].toInt();
        y_Axis= bufferSplit[i+2].toInt();
        odczytano(x_Axis,y_Axis);

        serialBuffer = " ";

        break;
}
}

}



}



void Dialog::updateAxisX(QString sensor_reading, Ui::MainWindow *ui)
{
    //  update the value displayed on the lcdNumber
    ui->osX_lcdnumber->display(sensor_reading);
}
void Dialog::updateAxisY(QString sensor_reading, Ui::MainWindow *ui)
{
    //  update the value displayed on the lcdNumber
    ui->osY_lcdnumber->display(sensor_reading);
}
