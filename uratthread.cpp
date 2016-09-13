#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uartthread.h"

#include <QTextStream>



extern QVector<double> time;
extern QVector<double> value[16];
extern bool isChannal[16];
extern QByteArray ReadData;
extern const char tag[2];
extern QFile file;

UartThread::UartThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);
}

UartThread::~UartThread()
{
    this->wait();
    qDebug() << this<<"over";
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
    static unsigned int timeCount = 0;
    QString UartBuf, TmpBuf;
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

        /*data[i] |= ReadBuf[i * 3 + 4 + 0];
        data[i] <<= 8;
        data[i] &= 0x00ffff00;
        data[i] |= ReadBuf[i * 3 + 4 + 1];
        data[i] <<= 8;
        data[i] &= 0x00ffff00;
        data[i] |= ReadBuf[i * 3 + 4 + 2];*/

        if(data[i]&0x00800000)
        {
            data[i] = -(((~data[i])&0x00ffffff) + 1);
        }
    }

    for(int i = 0;i < 16;i++)
    {
        TmpBuf.clear();
        TmpBuf.sprintf("%d:%d\r\n",i,data[i]);
        UartBuf.append(TmpBuf);
    }
    pMainWindow->ui->TextPlain->appendPlainText(UartBuf);

    if(time[time.length()-1] < MAX_SHOW_TIME)
    {
        time.append(timeCount*1000.0/pMainWindow->ui->comboBox_SampleRate->currentText().toInt());
        for(int i = 0;i < 16;i++)
        {
            value[i].append(data[i]*5.0/0x780000);
        }
    }
    else
    {
        time_MoveLeftInsert(timeCount*1000.0/pMainWindow->ui->comboBox_SampleRate->currentText().toInt());
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
    int i = 0;
    ReadData.append(my_serialport->readAll());
    while(1)
    {
        if(i >= ReadData.length()){i=0;break;}
        if(ReadData[i] == 0XA5 && ReadData[i+1] == 0XA5)break;
        i++;
    }
    if(i != 0)
    {
        ReadData.remove(0,i);
    }

    while(1)
    {
        if(ReadData.length() < 52)break;;
        usart_proc(ReadData);
        ReadData.remove(0,52);
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
