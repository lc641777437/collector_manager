#include <string.h>
#include <QTextStream>
#include <QInputDialog>

#include "dialog.h"
#include "uartthread.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QVector<double> times;
extern QVector<double> value[16];

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
    if(false == pMainWindow->isStartCollect){
        CommandData.append(my_serialport->readAll());
        qDebug()<<CommandData.toHex();
        while(1){
            if(CommandData.length() <= 2)break;
            if(CommandData[0] == 0XA6 && CommandData[1] == 0XA6)
            {
                timer->stop();
                if(CommandData[2] == CMD_SET_PARAM)
                {
                    if(CommandData.length() < 3)return;//length is not enough
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置参数成功!\n"));
                    if(pMainWindow->samplerateTmp != 0)pMainWindow->samplerate = pMainWindow->samplerateTmp;
                }

                if(CommandData[2] == CMD_GET_PARAM)
                {
                    if(CommandData.length() < 10)return;//length is not enough
                    QString tmp[16];
                    Dialog event(pMainWindow, CommandData[3], CommandData[4], CommandData[5], CommandData[6], CommandData[7], CommandData[8], CommandData[9],
                                 "","",tmp);
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
                        pMainWindow->samplerateTmp = event.pFre;
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
    }else{
        int i = 0;
        ReadData.append(my_serialport->readAll());
        qDebug()<<"here";
        //qDebug()<<ReadData.toHex();

        while(1){//remove the nothing header
            if(i >= ReadData.length()){
                i=0;
                break;
            }
            if(ReadData[i] == 0XA5 && ReadData[i+1] == 0XA5){
                break;
            }
            i++;
        }
        if(i != 0){
            ReadData.remove(0,i);
        }

        while(1){//proc
            if(ReadData.length() < 54)break;
            if(ReadData[0] == 0XA5 && ReadData[1] == 0XA5) {
                if(ReadData[52] == 0XA5 && ReadData[53] == 0XA5) {
                    ADValue_proc(ReadData);
                    ReadData.remove(0,52);
                }else {
                    ReadData.remove(0,2);
                    break;
                }
            }else {
                break;
            }
        }
    }
}

void UartThread::ADValue_proc(QByteArray &ReadBuf)
{
    double V[16] = {0};
    int data[16] = {0};
    int data1,data2,data3;

    pMainWindow->timeCount++;

    for(int j = 0; j < 2;j++){
        for(int i = 0; i < 8; i++){
            if(ReadBuf[j + 2] & (0x01<<(7-i))){
                pMainWindow->isChannal[j * 8 + i] = 0;
            }else{
                pMainWindow->isChannal[j * 8 + i] = 1;
            }
        }
    }

    for(int i = 0;i < 16;i++){
        data1 = ReadBuf[i * 3 + 4 + 0];
        data1 = data1<<16;
        data2 = ReadBuf[i * 3 + 4 + 1];
        data2 = data2<<8;
        data3 = ReadBuf[i * 3 + 4 + 2];

        data[i] = (data1&0x00ff0000)|(data2&0x0000ff00)|(data3&0x000000ff);

        if(data[i]&0x00800000){
            data[i] = -(((~data[i])&0x00ffffff) + 1);
        }

        // 计算H值
        double tmp = 0;
        double coefficient = 0.0;
        double values = data[i];
        for(int i = 0; i < 10; i++){
            double tempValue = values - i * 786432.0;
            switch(i){
            case 0:
                coefficient = pMainWindow->coefficient1;
                break;
            case 1:
                coefficient = pMainWindow->coefficient2;
                break;
            case 2:
                coefficient = pMainWindow->coefficient3;
                break;
            case 3:
                coefficient = pMainWindow->coefficient4;
                break;
            case 4:
                coefficient = pMainWindow->coefficient5;
                break;
            case 5:
                coefficient = pMainWindow->coefficient6;
                break;
            case 6:
                coefficient = pMainWindow->coefficient7;
                break;
            case 7:
                coefficient = pMainWindow->coefficient8;
                break;
            case 8:
                coefficient = pMainWindow->coefficient9;
                break;
            case 9:
                coefficient = pMainWindow->coefficient10;
                break;
            }

            if(tempValue > 786432.0){
                tmp += 786432 * coefficient;
            } else if(tempValue > 0){
                tmp += tempValue * coefficient;
            } else{
                break;
            }
        }
        data[i] = tmp;
        V[i] = tmp / 786432;
    }

    if(times[times.length()-1] < MAX_SHOW_TIME){
        times.append(pMainWindow->timeCount * 1000.0 / pMainWindow->samplerate);
        for(int i = 0;i < 16;i++){
            value[i].append(data[i]*5.0/0x780000);
        }
    }else{
        time_MoveLeftInsert(pMainWindow->timeCount * 1000.0 / pMainWindow->samplerate);
        for(int i = 0;i < 16;i++){
            data_MoveLeftInsert(i,data[i]*5.0/0x780000);
        }
    }

    if(!pMainWindow->file.isOpen())pMainWindow->file.open( QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text);
    QTextStream steam(&pMainWindow->file);
    steam<<QTime::currentTime().toString()<<",";
    for(int i = 0; i < 16; i++){
        if(pMainWindow->isChannal[i])
            steam<<data[i]<<",";
        else
            steam<<"-,";
    }
    steam<<endl;
}

void UartThread::time_MoveLeftInsert(double data)
{
    for(int i = 0;i < times.length()-1;i++){
        times[i] = times[i+1];
    }
    times[times.length()-1] = data;
}

void UartThread::data_MoveLeftInsert(int channal, double data)
{
    for(int i = 0;i < times.length()-1;i++){
        value[channal][i] = value[channal][i+1];
    }
    value[channal][times.length()-1] = data;
}


void UartThread::CommandProc()
{
    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("                设备无响应\n\n请检查设备电源或者串口是否连接正常!\n"));
    CommandData.clear();
    timer->stop();
}
