#ifndef GRAPHTHREAD
#define GRAPHTHREAD

#include <QThread>
#include <iostream>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class UartThread;
}

class MainWindow;

class UartThread : public QThread
{
    Q_OBJECT
public:
    UartThread(QString message = "", QObject *parent = NULL);
    ~UartThread();
    MainWindow  *pMainWindow;
    void setMessage(QString);
    QString getMessage();

    QSerialPort *my_serialport;



protected:
    void run();

private:
    QString message;
    volatile bool stopped;
    void usart_proc(QByteArray ReadBuf);
    void time_MoveLeftInsert(double data);
    void data_MoveLeftInsert(int channal, double data);


private slots:
    void UART_RX_Handler();

};

#endif // GRAPHTHREAD

