#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpclientthread.h"

extern QVector<double> time;
extern QVector<double> value[16];   // value是一个vector的数组,即二维数组

extern int samplerate;

/***************** 初始化 ********************************/
TcpClientThread::TcpClientThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);
    id = 0;
    last_second = -1;
}

TcpClientThread::~TcpClientThread()
{
    this->wait();
    qDebug() <<"(tcpclientthread.cpp)"<< this<<"over";
    this->exit();
}

/***************** 回掉函数 ******************************/
// 设备连接到了网络 回掉函数:
void TcpClientThread::socketconnected()
{
    timer->stop();
    pMainWindow->changeState(STATE_CONNECT_SOCKET);
    pMainWindow->ui->pushButton_SocketConnect->setText("断开连接");
}
// 接收设备的回复  回掉函数:
void TcpClientThread::socketreadyread()
{
    // 设备 对下发的命令字的回复
    if(false == pMainWindow->isStartCollect)
    {
        CommandData.append(socket->readAll());
        while(1){
            if(CommandData.length() <= 2)break;
            // 格式匹配: 找到开始位置
            if(CommandData[0] == 0XA6 && CommandData[1] == 0XA6){
                timer->stop();
                // 设备对 "设置参数" 的回复: 弹出对话框提示ok
                if(CommandData[2] == CMD_SET_PARAM){
                    if(CommandData.length() < 3)return;//length is not enough
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '设置参数' 的回复: ================="<<endl<<endl;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置参数成功!\n"));
                    if(pMainWindow->samplerateTmp != 0)pMainWindow->samplerate = pMainWindow->samplerateTmp;
                }
                // 设备对 "获取参数" 的回复: 设备回复上传设置的参数,然后打开 “设置参数” 对话框
                else if(CommandData[2] == CMD_GET_PARAM){
                    if(CommandData.length() < 10)return;//length is not enough
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '获取参数' 的回复: ================="<<endl<<endl;

                    /********** 工程流水号 ************************/
                    QByteArray proId;
                    for(int i = 10;i<58;i++){
                        proId.append(CommandData.at(i));
                    }
                    QString proIdStr = QString(proId);
                    qDebug()<<"qByte: "<<proId<<endl<<"str: "<<proIdStr<<endl;
                    /********** 项目名称 ************************/
                    QByteArray proName;
                    for(int i = 58;i<58+48;i++){
                        proName.append(CommandData.at(i));
                    }
                    QString proNameStr = QString(proName);
                    qDebug()<<"qByte: "<<proName<<endl<<"str: "<<proNameStr<<endl;
                    /********** 测试点的名称 ************************/
                    QString testPointNameList[16];
                    for(int j = 0;j<16;j++){
                        QByteArray testPointName;
                        for(int i = 10+48*2 + 24*j;i<10+48*2 + 24*(j+1);i++){
                            testPointName.append(CommandData.at(i));
                        }
                        QString testPointName_str = QString(testPointName);
                        testPointNameList[j] = testPointName_str;
                        qDebug()<<"测试点"<<j<<"原数据: "<<testPointName<<endl<<"测试点名称: "<<testPointName_str<<endl;
                    }

                    // 根据设备的回复 打开"设置参数"的对话框
                    Dialog* event = new Dialog(pMainWindow, CommandData[3],
                                               CommandData[4], CommandData[5],
                                               CommandData[6], CommandData[7],
                                               CommandData[8], CommandData[9],
                                               proIdStr,proNameStr,
                                               testPointNameList);
                    event->setModal(true);
                    event->show();
                    qDebug()<<"(tcpclientthread.cpp)参数设置对话框"<<endl;

                }
                // 设备回复 "开始采集"
                else if(CommandData[2] == CMD_SEND_START){
                    if(CommandData.length() < 3)return;//length is not enough
                    pMainWindow->isStartCollect = true;
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '开始采集' 的回复: ================="<<endl<<endl;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经开始采集!\n"));
                }
                // 设备回复 "结束采集"
                else if(CommandData[2] == CMD_SEND_STOP){
                    if(CommandData.length() < 3)return;//length is not enough
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '结束采集' 的回复: ================="<<endl<<endl;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("已经结束采集!\n"));
                }
                // 设备回复 "恢复出厂设置"
                else if(CommandData[2] == CMD_SET_FACTORY){
                    if(CommandData.length() < 3)return;//length is not enough
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '恢复出厂设置' 的回复: ================="<<endl<<endl;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设备恢复出厂设置成功!\n"));
                }
                // 设备回复 "设置服务器"
                else if(CommandData[2] == CMD_SET_SERVER){
                    if(CommandData.length() < 3)return;//length is not enough
                    qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============= 设备对 '设置服务器' 的回复: ================="<<endl<<endl;
                    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("设置服务器成功!\n"));
                }
                if(CommandData[2] == 0x80){
                     if(CommandData.length() < 3)return;//length is not enough
                     qDebug()<<"(tcpclientthread.cpp)结束包:"<<CommandData<<endl;
                }else if(CommandData[2] == 0x81){
                    if(CommandData.length() < 3)return;//length is not enough
                    qDebug()<<"(tcpclientthread.cpp)开始包:"<<CommandData<<endl;
                }
                else qDebug()<<"(tcpclientthread.cpp)命令字长度: "<<CommandData.length()<<",回复内容:"<<CommandData.toHex();
                // 清空接收buffer
                CommandData.clear();
                break;
            }
            else
            {
                // 移除掉前面的错误字符,继续判断
                CommandData.remove(0,1);
            }
        }
    }
    // 设备 回复数据
    else{
        int i = 0;
        // 读取数据：每次读取4+16*3=52个字节
        ReadData.append(socket->readAll());
        qDebug()<<endl<<endl<<"(tcpclientthread.cpp)============== 设备 回复数据: ==========="<<endl<<endl;
        // 寻找数据开始点: 0xA5 0xA5
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
        // 移除掉前面的非相关数据
        if(i != 0){
            ReadData.remove(0,i);
        }
        qDebug()<<"(tcpclientthread.cpp)数据长度: "<<ReadData.length()<<endl;
        while(1){
            if(ReadData.length() < 54)break;
            if(ReadData[0] == 0XA5 && ReadData[1] == 0XA5){
                if(ReadData[52] == 0XA5 && ReadData[53] == 0XA5){
                    ADValue_proc(ReadData);
                    ReadData.remove(0,52);
                }else{
                    ReadData.remove(0,2);
                    break;
                }
            }else{
                break;
            }
        }
    }
}
// tcp连接超时    回掉函数:
void TcpClientThread::tcptimeout()
{
    QMessageBox::information(pMainWindow, tr("采集分析软件"), tr("                设备无响应\n\n请检查设备电源或者网络是否连接正常!\n"));
    CommandData.clear();
    timer->stop();
}

/***************** 功能函数 ********************************/
// 将数据填充到画图线程需要的数组中,并保存到文件中
void TcpClientThread::ADValue_proc(QByteArray &ReadBuf)
{
    double data[16] = {0};
    double f[16] = {0};          // 扰度值
    double V[16] = {0};          // 电压值
    int data1,data2,data3;

    pMainWindow->timeCount++;

    // 判断哪些通道被选中 (readBuf的第(0,1没用到)2,3个字节用于标识通道是否选择)
    for(int j = 0; j < 2;j++){
        for(int i = 0; i < 8; i++){
            if(ReadBuf[j + 2] & (0x01<<(7-i))){
                pMainWindow->isChannal[j * 8 + i] = 0;
            }else{
                pMainWindow->isChannal[j * 8 + i] = 1;
            }
        }
    }

    // 16帧数据,每帧代表每个通道的值
    int tmpData = 0;
    // 计算h值
    for(int i = 0;i < 16;i++){
        // 接下来的每3个字节组成一帧数据
        data1 = ReadBuf[i * 3 + 4 + 0];
        data1 = data1<<16;
        data2 = ReadBuf[i * 3 + 4 + 1];
        data2 = data2<<8;
        data3 = ReadBuf[i * 3 + 4 + 2];
        tmpData = (data1&0x00ff0000)|(data2&0x0000ff00)|(data3&0x000000ff);
        // 负数处理
        if(tmpData&0x00800000){
            tmpData = -(((~tmpData)&0x00ffffff) + 1);
        }

        // 计算H值
        double tmp = tmpData;
        tmp = (tmp*pMainWindow->e/393216.0 - 4)/16.0*(pMainWindow->PmaxList[i] - pMainWindow->PminList[i])
                  + pMainWindow->PminList[i];
        data[i] = tmp / (9.8 * pMainWindow->Density);
        // 保存初始H值
        if(pMainWindow->readInitialValue){
            if(pMainWindow->H[i] == 0) pMainWindow->H[i] = data[i];
            else  pMainWindow->H[i] = ( pMainWindow->H[i] + data[i] ) / 2.0;
        }
        // 计算电压值
        tmp = tmpData;
        V[i] = tmp * pMainWindow->e / 786432;
    }
    if(pMainWindow->readInitialValue == false){
            // 计算挠度值
            for(int i = 0;i<16;i++){
                f[i] = data[i] - pMainWindow->H[i] -
                      (data[pMainWindow->baseValue] - pMainWindow->H[pMainWindow->baseValue]);
            }
            // 将数据添加到画图线程中去，显示画图
            if(time[time.length()-1] < MAX_SHOW_TIME){
                time.append(pMainWindow->timeCount * 1000.0 / pMainWindow->samplerate);
                // 将每个通道的值添加到相应的代表通道的数组中
                for(int i = 0;i < 16;i++){
                     value[i].append(f[i]);
                }

            }else{
                //数据左移,以便能够显示新值
                time_MoveLeftInsert(pMainWindow->timeCount * 1000.0 / pMainWindow->samplerate);
                for(int i = 0;i < 16;i++){
                       data_MoveLeftInsert(i,f[i]);
                }
            }

            // 将数据写到文件中去
            if(!pMainWindow->file.isOpen())pMainWindow->file.open( QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text);
            QTextStream steam(&pMainWindow->file);

            // 数据文件保存1: 时分秒,毫秒
            steam<<QTime::currentTime().toString()<<":"<<QTime::currentTime().msec()<<",";
            if(last_second == QTime::currentTime().second()) id++;
            else {
                id=0;
                last_second = QTime::currentTime().second();
            }
            // 数据文件保存1: 递增id
            steam<<id<<",";
            // 数据文件保存1: 16个扰度值
            for(int i = 0; i < 16; i++){
                if(pMainWindow->isChannal[i])
                    steam<<f[i]<<",";
                else
                    steam<<"-,";
            }
            // 数据文件保存1: 16个平均值
            if(id == 0){
                for(int i = 0; i < 16; i++){
                    if(pMainWindow->isChannal[i]){
                        steam<<(f_avg[i]/200.0)<<",";
                        f_avg[i] = 0;
                    }
                    else steam<<"-,";
                }
            }else{
                for(int i = 0; i < 16; i++){
                    if(pMainWindow->isChannal[i]){
                        f_avg[i] = f_avg[i] + f[i];
                    }
                }
            }
            steam<<endl;

            if(!pMainWindow->vfile.isOpen())pMainWindow->vfile.open( QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text);
            QTextStream steam2(&pMainWindow->vfile);
            // 数据文件保存2: 时分秒,毫秒
            steam2<<QTime::currentTime().toString()<<":"<<QTime::currentTime().msec()<<",";
            // 数据文件保存: 保存16个电压值
            for(int i = 0; i < 16; i++){
                if(pMainWindow->isChannal[i])
                    steam2<<V[i]<<",";
                else
                    steam2<<"-,";
            }
            steam2<<endl;
     }
}
// 辅助函数 -- 时间值左移
void TcpClientThread::time_MoveLeftInsert(double data)
{
    for(int i = 0;i < time.length()-1;i++){
        time[i] = time[i+1];
    }
    time[time.length()-1] = data;
}
// 辅助函数 --  数据值左移
void TcpClientThread::data_MoveLeftInsert(int channal, double data)
{
    for(int i = 0;i < time.length()-1;i++){
        value[channal][i] = value[channal][i+1];
    }
    value[channal][time.length()-1] = data;
}

