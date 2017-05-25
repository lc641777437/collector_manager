#include <string.h>
#include <QTextStream>
#include <QInputDialog>

#include "dialog.h"
#include "uartthread.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

UartThread::UartThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CommandProc()));
}

UartThread::~UartThread()
{
    this->wait();
    qDebug() << this<<"over";
    this->exit();
}

void UartThread::setMessage(QString message)
{
    this->message = message;
}

QString UartThread::getMessage()
{
    return this->message;
}

void UartThread::UART_RX_Handler()
{
    CommandData.append(my_serialport->readAll());
    qDebug()<<CommandData.toHex();

    while(1)
    {
        if(CommandData.length() <= 2)break;
        if(CommandData[0] == 0XA6 && CommandData[1] == 0XA6)
        {
            timer->stop();
            if(CommandData[2] == CMD_SET_PARAM)
            {
                if(CommandData.length() < 3)return;//length is not enough
                QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置参数成功!\n"));
            }

            if(CommandData[2] == CMD_GET_PARAM)
            {
                if(CommandData.length() < 10)return;//length is not enough
                Dialog event(pMainWindow, CommandData[3], CommandData[4], CommandData[5], CommandData[6], CommandData[7], CommandData[8], CommandData[9]);
                int rc = event.exec();
                if(rc == 0)
                {
                    QByteArray message;
                    message.append(QString("SetParam"));
                    message.append(event.pDevIDH);
                    message.append(event.pDevIDL);
                    message.append(event.pCtrlH);
                    message.append(event.pCtrlL);
                    message.append(event.pFre);
                    message.append(event.pSendTimeServer);
                    message.append(event.pSendTimeDynamic);
                    message.append(QString("\r\n"));

                    my_serialport->write(message);
                    this->timer->start(TIMEOUTTIME);
                }
            }
            if(CommandData[2] == CMD_SEND_START)
            {
                if(CommandData.length() < 3)return;//length is not enough
                pMainWindow->isStartCollect = true;
                QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经开始采集!\n"));
            }
            if(CommandData[2] == CMD_SEND_STOP)
            {
                if(CommandData.length() < 3)return;//length is not enough
                QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经结束采集!\n"));
            }
            if(CommandData[2] == CMD_SET_FACTORY)
            {
                if(CommandData.length() < 3)return;//length is not enough
                QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设备恢复出厂设置成功!\n"));
            }
            if(CommandData[2] == CMD_SET_SERVER)
            {
                if(CommandData.length() < 3)return;//length is not enough
                QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置服务器成功!\n"));
            }

            CommandData.clear();
            break;
        }else{
            CommandData.remove(0,1);
        }
    }
}

void UartThread::CommandProc()
{
    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("                设备无响应\n\n请检查设备电源或者串口是否连接正常!\n"));
    CommandData.clear();
    timer->stop();
}
