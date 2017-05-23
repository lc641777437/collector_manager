#ifndef GRAPHTHREAD
#define GRAPHTHREAD

#include <QThread>
#include <iostream>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

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

    QTimer *timer;



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

public slots:
    void CommandProc();

};

typedef enum{
    CMD_SET_PARAM    = 0X01,
    CMD_GET_PARAM    = 0X02,
    CMD_SEND_START   = 0X03,
    CMD_SEND_STOP    = 0X04,
    CMD_SET_FACTORY  = 0X05,

    CMD_SET_ERROR    = 0X99
} CMD_TYPE;

#endif // GRAPHTHREAD

