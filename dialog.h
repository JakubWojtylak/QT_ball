/*!
 * \file
 *
 * \brief Komunikacja
 * dialog.h to plik nagłówkowy zawierający deklarację klasy odpowiadającej za komunikację z mikrokontrolerem
 */

#ifndef DIALOG_H
#define DIALOG_H
#include <ui_mainwindow.h>
#include <QDialog>
#include <QSerialPort>
#include <QByteArray>



/*!
 * \brief The Dialog class
 * klasa zawierająca metody przesyłania danych z mikrokontrolera do aplikacji
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    /*!
     * \brief pobiera dane z portu szeregowego
     * pobiera dane z portu szeregowego
     * \param[in] ui - przekazanie wskaźnika na interfejs użytkownika pozwalający zmieniać wartość na nim
     */
    void readSerial(Ui::MainWindow*);
    /*!
     * \brief Pokazanie wartości na osi X
     *  \param[in] Ui - przekazanie wskaźnika na interfejs użytkownika pozwalający zmieniać wartość na
     *  \param[in] QString - przekazanie wartości na osi w postaci stringa
     */
    void updateAxisX(QString, Ui::MainWindow*);
    /*!
     * \brief Pokazanie wartości na osi Y
     *   \param[in] Ui - przekazanie wskaźnika na interfejs użytkownika pozwalający zmieniać wartość na
     *   \param[in] QString - przekazanie wartości na osi w postaci stringa
     */
    void updateAxisY(QString, Ui::MainWindow*);
double getAxisX(){return x_Axis;}
double getAxisY(){return y_Axis;}
  signals:
    /*!
     * \brief sygnał generowany przez dialog przy odberaniu nowych danych
     * sygnał generowany przez dialog przy odberaniu nowych danych
     */
    void read();
    void odczytano(int, int);
    void disco();


private:
    /*!
     * \brief wskaźnik na port COM
     */
    QSerialPort * discovery;
    /*!
     * \brief ID urządzenia
     */
    static const quint16 discovery_vendor_id = 1155;
    /*!
     * \brief ID produktu
     */
    static const quint16 discovery_product_id = 14155;
    /*!
     * \brief zmienna przechowująca dane pobrane z portu szeregowego
     */
    QByteArray serialData;
    /*!
     * \brief tablica przechowująca podzielone dane
     */
    QString serialBuffer;

   // QString parsed_data;
    /*!
     * \brief x_Axis - zmienna przechowująca obrót wokół osi X
     */
public:
    double x_Axis;
    /*!
     * \brief y_Axis zmienna przechowująca obrót wokół osi Y
     */
    double y_Axis;
};

#endif // DIALOG_H
