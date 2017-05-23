#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uartthread.h"
#include "dialog.h"

#include <QTextStream>
#include <string.h>

#include <QInputDialog>


extern QByteArray ReadData;
extern QVector<double> time;
extern QVector<double> value[16];
extern QFile file;

extern bool isChannal[16];
extern int samplerate;
extern bool isSTART;

static QByteArray CommandData;

unsigned int timeCount = 0;

UartThread::UartThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CommandProc()), Qt::DirectConnection);
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

void UartThread::run()
{
    exec();
}

void UartThread::usart_proc(QByteArray ReadBuf)
{
    int data[16] = {0};
    int data1,data2,data3;

    timeCount++;

    for(int j = 0; j < 2;j++)
    {
        for(int i = 0; i < 8; i++)
        {
            if(ReadBuf[j + 2] & (0x01<<(7-i)))
            {
                isChannal[j * 8 + i] = 0;
            }
            else
            {
                isChannal[j * 8 + i] = 1;
            }
        }
    }

    for(int i = 0;i < 16;i++)
    {
        data1 = ReadBuf[i * 3 + 4 + 0];
        data1 = data1<<16;
        data2 = ReadBuf[i * 3 + 4 + 1];
        data2 = data2<<8;
        data3 = ReadBuf[i * 3 + 4 + 2];

        data[i] = (data1&0x00ff0000)|(data2&0x0000ff00)|(data3&0x000000ff);

        if(data[i]&0x00800000)
        {
            data[i] = -(((~data[i])&0x00ffffff) + 1);
        }
    }

    if(time[time.length()-1] < MAX_SHOW_TIME)
    {
        time.append(timeCount*1000.0/samplerate);
        for(int i = 0;i < 16;i++)
        {
            value[i].append(data[i]*5.0/0x780000);
        }
    }
    else
    {
        time_MoveLeftInsert(timeCount*1000.0/samplerate);
        for(int i = 0;i < 16;i++)
        {
            data_MoveLeftInsert(i,data[i]*5.0/0x780000);
        }
    }

    if(file.isOpen())
    {
        QTextStream steam(&file);
        steam<<QTime::currentTime().toString()<<",";
        for(int i = 0;i < 16;i++)
        {
            if(isChannal[i])
                steam<<data[i]<<",";
            else
                steam<<"-,";
        }
        steam<<endl;
    }
}

void UartThread::UART_RX_Handler()
{
    if(!pMainWindow->isStart)
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
                    if(CommandData.length() < 3){
                        return;//length is not enough
                    }
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置参数成功!\n"));
                }

                if(CommandData[2] == CMD_GET_PARAM)
                {
                    if(CommandData.length() < 10)
                    {
                        return;//length is not enough
                    }
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
                        this->timer->start(2000);
                    }
                }
                if(CommandData[2] == CMD_SEND_START)
                {
                    if(CommandData.length() < 3){
                        return;//length is not enough
                    }
                    pMainWindow->isStart = true;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经开始采集!\n"));
                }
                if(CommandData[2] == CMD_SEND_STOP)
                {
                    if(CommandData.length() < 3){
                        return;//length is not enough
                    }
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经结束采集!\n"));
                }
                if(CommandData[2] == CMD_SET_FACTORY)
                {
                    if(CommandData.length() < 3){
                        return;//length is not enough
                    }
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设备恢复出厂设置成功!\n"));
                }
                if(CommandData[2] == CMD_SET_SERVER)
                {
                    if(CommandData.length() < 3){
                        return;//length is not enough
                    }
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置服务器成功!\n"));
                }

                CommandData.clear();
                break;
            }
            else
            {
                CommandData.remove(0,1);
            }
        }
    }
    else
    {
        int i = 0;
        ReadData.append(my_serialport->readAll());
        qDebug()<<ReadData.toHex();
        while(1)//remove the nothing header
        {
            if(i >= ReadData.length()){
                i=0;
                break;
            }
            if(ReadData[i] == 0XA5 && ReadData[i+1] == 0XA5){
                break;
            }
            i++;
        }
        if(i != 0)
        {
            ReadData.remove(0,i);
        }

        while(1)//proc
        {

            if(ReadData.length() < 54)break;
            if(ReadData[0] == 0XA5 && ReadData[1] == 0XA5)
            {
                if(ReadData[52] == 0XA5 && ReadData[53] == 0XA5)
                {
                    usart_proc(ReadData);
                    ReadData.remove(0,52);
                }
                else
                {
                    ReadData.remove(0,2);
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
}

void UartThread::time_MoveLeftInsert(double data)
{
    for(int i = 0;i < time.length()-1;i++)
    {
        time[i] = time[i+1];
    }
    time[time.length()-1] = data;
}

void UartThread::data_MoveLeftInsert(int channal, double data)
{
    for(int i = 0;i < time.length()-1;i++)
    {
        value[channal][i] = value[channal][i+1];
    }
    value[channal][time.length()-1] = data;
}

void UartThread::CommandProc()
{
    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("                设备无响应\n\n请检查设备电源或者串口是否连接正常!\n"));
    CommandData.clear();
    timer->stop();
}
