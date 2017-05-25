#ifndef UARTTHREAD_H
#define UARTTHREAD_H
#include <iostream>

#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

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

    QTimer *timer;
    QSerialPort *my_serialport;

private:
    QString message;
    QByteArray CommandData;
    volatile bool stopped;


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
    CMD_SET_SERVER   = 0X06,

    CMD_SET_ERROR    = 0X99
} CMD_TYPE;

#endif // UARTTHREAD_H

