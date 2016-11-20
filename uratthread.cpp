#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uartthread.h"

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
    if(!isSTART)
    {
        CommandData.append(my_serialport->readAll());
        //qDebug()<<CommandData;
        while(1)
        {
            if(CommandData.length() <= 2)break;
            if(CommandData[0] == 0XA6 && CommandData[1] == 0XA6)
            {
                timer->stop();
                if(CommandData[2] == 0X10)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("采样频率设置成功!\n"));
                }
                if(CommandData[2] == 0X11)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设备ID设置成功!\n"));
                }
                if(CommandData[2] == 0X12)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("采样类型设置成功!\n"));
                }
                if(CommandData[2] == 0X13)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("服务器地址设置成功!\n"));
                }
                if(CommandData[2] == 0X14)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经开始采集!\n"));
                }
                if(CommandData[2] == 0X15)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经结束采集!\n"));
                }
                if(CommandData[2] == 0X16)
                {
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设备恢复出厂设置成功!\n"));
                }
                if(CommandData[2] == 0X17)
                {
                    if(CommandData.length() < 4)break;
                    bool isOK;
                    QStringList list;
                    char str[5] = {0};
                    snprintf(str,5,"%d",CommandData[3]&0xff);
                    list<<tr(str)<<tr("200")<<tr("100")<<tr("50")<<tr("20")<<tr("10")<<tr("5")<<tr("2")<<tr("1");
                    QString SampleRate=QInputDialog::getItem(pMainWindow,tr("设置采样频率"),tr("请选择采样频率:"),list,0,false,&isOK);
                    if(isOK)
                    {
                        if(my_serialport->baudRate() == QSerialPort::Baud38400 && SampleRate.toInt() >= 20)
                        {
                            QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("无线串口仅支持 20 以下的采样率!\n"));
                        }
                        else
                        {
                            my_serialport->write("SampleRate:"+SampleRate.toLatin1()+"\r\n");
                            timer->start(2000);
                            samplerate = SampleRate.toInt();
                        }
                    }
                }
                if(CommandData[2] == 0X18)
                {
                    unsigned short ctrl = 0;
                    int data1,data2;
                    if(CommandData.length()<5)break;
                    data1 = CommandData[3]&0xff;
                    data2 = CommandData[4]&0xff;
                    ctrl |= data1;
                    ctrl <<= 8;
                    ctrl |= data2;
                    emit SendchangeShow(ctrl);
                    pMainWindow->setCTRL->setModal(true);
                    pMainWindow->setCTRL->show();
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
        /*static int count;
        qDebug()<<count++<<ReadData;*/
        while(1)//remove the nothing header
        {
            if(i >= ReadData.length())
            {
                i=0;
                break;
            }
            if(ReadData[i] == 0XA5 && ReadData[i+1] == 0XA5)
            {
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
