#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>
#include <QPointF>
#include "qnamespace.h"

QVector<double> time;
QVector<double> value[16];
QFile file("./default.csv");
QFile vfile("./v.csv");

extern unsigned int timeCount;

/*************** 初始化函数 ************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 1,窗口基本设置
    ui->setupUi(this);
    this->setWindowTitle("采集分析软件");
    file.setFileName("default.csv");
    vfile.setFileName("v.csv");

    // 2,画图时通道选择的复选框
    connect(ui->checkBox_1, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_2, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_3, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_4, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_5, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_6, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_7, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_8, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_9, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_10, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_11, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_12, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_13, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_14, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_15, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    connect(ui->checkBox_16, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));

    // 3,创建tcp线程,读数据
    tcpclient_thread = new TcpClientThread("tcpclientthread", this);
    tcpclient_thread->socket = new QTcpSocket;
    connect(tcpclient_thread->socket,SIGNAL(connected()),tcpclient_thread,SLOT(socketconnected()));
    connect(tcpclient_thread->socket, SIGNAL(readyRead()), tcpclient_thread, SLOT(socketreadyread()));
    tcpclient_thread->timer = new QTimer(this);
    connect(tcpclient_thread->timer, SIGNAL(timeout()), tcpclient_thread, SLOT(tcptimeout()));
    tcpclient_thread->start();

    // 4,创建串口线程,读数据
    uart_thread = new UartThread("uartthread", this);
    uart_thread->my_serialport= new QSerialPort;
    connect(uart_thread->my_serialport, SIGNAL(readyRead()), uart_thread, SLOT(UART_RX_Handler()));
    uart_thread->start();

    // 5,创建画图线程,读数据画图
    graph_thread = new GraphThread("graphthread", this);
    graph_thread->start();

    // 6,定时刷新可用通道
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(flush_checkBox()));
    timer->start(500);

    // 刷新可用通道
    flush_checkBox();
    // 刷新可用串口
    on_checkUartPort();

    // 7,自动保存读取数据相关设置
    AutoSavePeriod = 0;           // 自动保存周期
    AutoSaveFile = "./";          // 自动保存路径
    //定时保存文件
    AutoSaveFileId = 0;
    timerCount = 0;
    timer4AutoSaveFile = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_auto_save_file()));

    // 8,基准点
    baseValue = 0;
    readInitialValue = true; //读取初值
    for(int i = 0;i<20;i++) {
        H[i] = 100;
        PmaxList[i] = 0;
        PminList[i] = 0;
    }

}

// 关线程,关文件
MainWindow::~MainWindow()
{
    // 关线程,关文件
    uart_thread->quit();
    graph_thread->quit();
    tcpclient_thread->quit();
    if(file.isOpen())file.close();
    delete ui;
}

/***************** 按钮响应函数 **********************************/
// 1,"获取串口"按钮响应函数
void MainWindow::on_checkUartPort()   // 读取可用串口,加入到可用串口列表中 -- (help函数)
{
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    ui->Port->clear();
    if(infos.isEmpty()){
        ui->Port->addItem("NONE");
        return;
    }
    foreach (QSerialPortInfo info, infos){
        ui->Port->addItem(info.portName());
    }
}
void MainWindow::on_pushButton_GetCOM_clicked()
{
    on_checkUartPort();
}

// 2,"无线串口"按钮响应函数 -- 我(lhc)没用到
void MainWindow::on_pushButton_wireless_clicked()
{
     qDebug()<<"(mainwindow.cpp)这是无线串口响应函数";
     if(ui->Port->currentText() == "NONE")return;

     if(ui->pushButton_wireless->text() == "无线串口"){
         bool isOK = true;
         uart_thread->my_serialport->setPortName(ui->Port->currentText());
         isOK = isOK && uart_thread->my_serialport->open(QIODevice::ReadWrite);
         isOK = isOK && uart_thread->my_serialport->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
         isOK = isOK && uart_thread->my_serialport->setDataBits(QSerialPort::Data8);
         isOK = isOK && uart_thread->my_serialport->setParity(QSerialPort::NoParity);
         isOK = isOK && uart_thread->my_serialport->setStopBits(QSerialPort::OneStop);
         isOK = isOK && uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);
         if(!isOK){
             QMessageBox::information(this, tr("采集分析软件"), tr("串口可能被占用！\n"));
             return;
         }

         changeState(STATE_OPEN_SERIAL);
         ui->pushButton_wireless->setText("关闭串口");
     }else{
         uart_thread->my_serialport->close();
         changeState(STATE_NULL);
         ui->pushButton_wireless->setText("无线串口");
     }
}

// 3,"参数设置"按钮响应函数
void MainWindow::on_pushButton_SetParam_clicked()
{
    if(connectType == CONNECT_SERIAL){
        qDebug()<<"(mainwindow.cpp)串口连接..向下位机发送获取参数命令..."<<endl;
        uart_thread->my_serialport->write("GetParam\r\n");
        uart_thread->timer->start(TIMEOUTTIME);
    }else if(connectType == CONNECT_SOCKET){
        qDebug()<<"(mainwindow.cpp)无线网络连接..向下位机发送获取参数命令..."<<endl;
        tcpclient_thread->socket->write("GetParam\r\n");
        tcpclient_thread->timer->start(TIMEOUTTIME);
    }
}

// 4,"局域网络连接"按钮响应函数
void MainWindow::on_pushButton_SocketConnect_clicked()
{
    // 建立连接
    if(ui->pushButton_SocketConnect->text() != "断开连接"){
        tcpclient_thread->socket->connectToHost("192.168.0.7", 23, QTcpSocket::ReadWrite);
        tcpclient_thread->timer->start(TIMEOUTTIME);
    }
    //断开连接
    else{
        tcpclient_thread->socket->close();
        changeState(STATE_NULL);
        ui->pushButton_SocketConnect->setText("局域\n网络连接");
    }
}

// 5,点击选择通道之后,扫描记录下已选项,超过4个时不选中,并给予提示
void MainWindow::on_checkBox_clicked()
{
    int count = 0,i;
    bool tmp_box[16] = {false};   // 记录选中的通道的个数

    if(ui->checkBox_1->isChecked()){
        if(isChannal[0] == false){
            ui->checkBox_1->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[0] = true;
    }
    if(ui->checkBox_2->isChecked()){
        if(isChannal[1] == false){
            ui->checkBox_2->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[1] = true;
    }
    if(ui->checkBox_3->isChecked()){
        if(isChannal[2] == false){
            ui->checkBox_3->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[2] = true;
    }
    if(ui->checkBox_4->isChecked()){
        if(isChannal[3] == false){
            ui->checkBox_4->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[3] = true;
    }
    if(ui->checkBox_5->isChecked()){
        if(isChannal[4] == false){
            ui->checkBox_5->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[4] = true;
    }
    if(ui->checkBox_6->isChecked()){
        if(isChannal[5] == false){
            ui->checkBox_6->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[5] = true;
    }
    if(ui->checkBox_7->isChecked()){
        if(isChannal[6] == false){
            ui->checkBox_7->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[6] = true;
    }
    if(ui->checkBox_8->isChecked()){
        if(isChannal[7] == false){
            ui->checkBox_8->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[7] = true;
    }
    if(ui->checkBox_9->isChecked()){
        if(isChannal[8] == false){
            ui->checkBox_9->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[8] = true;
    }
    if(ui->checkBox_10->isChecked()){
        if(isChannal[9] == false){
            ui->checkBox_10->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[9] = true;
    }
    if(ui->checkBox_11->isChecked()){
        if(isChannal[10] == false){
            ui->checkBox_11->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[10] = true;
    }
    if(ui->checkBox_12->isChecked()){
        if(isChannal[11] == false){
            ui->checkBox_12->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[11] = true;
    }
    if(ui->checkBox_13->isChecked()){
        if(isChannal[12] == false){
            ui->checkBox_13->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[12] = true;
    }
    if(ui->checkBox_14->isChecked()){
        if(isChannal[13] == false){
            ui->checkBox_14->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[13] = true;
    }
    if(ui->checkBox_15->isChecked()){
        if(isChannal[14] == false){
            ui->checkBox_15->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[14] = true;
    }
    if(ui->checkBox_16->isChecked()){
        if(isChannal[15] == false){
            ui->checkBox_16->setChecked(false);
            QMessageBox::information(this, tr("采集分析软件"), tr("该通道没有连接传感器!\n"));
            return;
        }
        tmp_box[15] = true;
    }

    ui->widget->graph(0)->setName("未使用");
    ui->widget->graph(1)->setName("未使用");
    ui->widget->graph(2)->setName("未使用");
    ui->widget->graph(3)->setName("未使用");

    // (1) 统计上一次已经选中了多少个通道
    for(i = 0,count = 0; i < 16; i++){
        if(box[i]) count++;
    }
    // (2) 通过对比这一次和上一次选中的通道的不同,以找出这次新选中的一个通道(一般就是这唯一的一个不同,因为每选中一个通道就会调用该函数)
    for(i = 0; i < 16; i++){
        if(box[i] != tmp_box[i])break;
    }
    // (3) 如果上次选中的通道个数少于4个,则记录下这次选中的通道
    if(count <= 3){
        box[i] = tmp_box[i];
    }
    // (4) 如果上次选中的通道个数已经是4个了,则提示不能新增通道了.并将用户的勾选取消掉.
    if(count >= 4){
        if(tmp_box[i] == true){
            qDebug()<<"(mainwindow.cpp)channal"<<i+1<<"clicked";
            QMessageBox::information(this, tr("采集分析软件"), tr("最多选择四个通道！\n"));
            switch(i)
            {
                case 0:
                ui->checkBox_1->setCheckState(Qt::Unchecked);
                    break;
                case 1:
                ui->checkBox_2->setCheckState(Qt::Unchecked);
                    break;
                case 2:
                ui->checkBox_3->setCheckState(Qt::Unchecked);
                    break;
                case 3:
                ui->checkBox_4->setCheckState(Qt::Unchecked);
                    break;
                case 4:
                ui->checkBox_5->setCheckState(Qt::Unchecked);
                    break;
                case 5:
                ui->checkBox_6->setCheckState(Qt::Unchecked);
                    break;
                case 6:
                ui->checkBox_7->setCheckState(Qt::Unchecked);
                    break;
                case 7:
                ui->checkBox_8->setCheckState(Qt::Unchecked);
                    break;
                case 8:
                ui->checkBox_9->setCheckState(Qt::Unchecked);
                    break;
                case 9:
                ui->checkBox_10->setCheckState(Qt::Unchecked);
                    break;
                case 10:
                ui->checkBox_11->setCheckState(Qt::Unchecked);
                    break;
                case 11:
                ui->checkBox_12->setCheckState(Qt::Unchecked);
                    break;
                case 12:
                ui->checkBox_13->setCheckState(Qt::Unchecked);
                    break;
                case 13:
                ui->checkBox_14->setCheckState(Qt::Unchecked);
                    break;
                case 14:
                ui->checkBox_15->setCheckState(Qt::Unchecked);
                    break;
                case 15:
                ui->checkBox_16->setCheckState(Qt::Unchecked);
                    break;
            }

        }else{
            box[i] = false;
        }
    }
    // (5) 画图显示已选中通道数据
    for(int j = 0,index = 0; j < 16; j++){
        if(box[j]) {
            ui->widget->graph(index)->setName("通道"+QString::number(j+1));
            index++;
        }
    }
}

// 6,"开始采集"按钮响应函数
void MainWindow::on_pushButton_StartCollect_clicked()
{
    // 数据连接方式: 串口连接
    if(connectType == CONNECT_SERIAL){
        if(this->samplerate == 0 || this->samplerate != 1){
            QMessageBox::information(this, tr("采集分析软件"), tr("无线本地采集，请先设置采样频率为1!\n"));
            return;
        }

        if(ui->pushButton_StartCollect->text() == "开始采集"){
            uart_thread->my_serialport->write("StartToSend\r\n");
            qDebug()<<"(mainwindow.cpp)socket send:"<<"StartToSend\r\n";

            changeState(STATE_START_COLLECT);
            ui->pushButton_StartCollect->setText("结束采集");
        }else if(ui->pushButton_StartCollect->text() == "结束采集"){
            uart_thread->my_serialport->write("StopToSend\r\n");
            uart_thread->timer->start(TIMEOUTTIME);
            qDebug()<<"(mainwindow.cpp)uart send:"<<"StopToSend\r\n";

            changeState(STATE_STOP_COLLECT);
            ui->pushButton_StartCollect->setText("继续采集");
        }else if(ui->pushButton_StartCollect->text() == "继续采集"){
            uart_thread->my_serialport->write("StartToSend\r\n");
            //uart_thread->timer->start(TIMEOUTTIME);
            qDebug()<<"(mainwindow.cpp)uart send:"<<"StartToSend\r\n";

            changeState(STATE_START_COLLECT);
            ui->pushButton_StartCollect->setText("结束采集");
        }
    }
    // 数据连接方式: 网络连接
    else if(connectType == CONNECT_SOCKET){
        if(this->samplerate == 0){
            QMessageBox::information(this, tr("采集分析软件"), tr("有线本地采集，请先设置采样参数!\n"));
            return;
        }

        if(ui->pushButton_StartCollect->text() == "开始采集"){
            tcpclient_thread->socket->write("StartToSend\r\n");
            qDebug()<<"(mainwindow.cpp)socket send:"<<"StartToSend\r\n";

            changeState(STATE_START_COLLECT);
            ui->pushButton_StartCollect->setText("结束采集");
        }else if(ui->pushButton_StartCollect->text() == "结束采集"){
            tcpclient_thread->socket->write("StopToSend\r\n");
            tcpclient_thread->timer->start(TIMEOUTTIME);
            qDebug()<<"(mainwindow.cpp)uart send:"<<"StopToSend\r\n";

            changeState(STATE_STOP_COLLECT);
            ui->pushButton_StartCollect->setText("继续采集");
        }else if(ui->pushButton_StartCollect->text() == "继续采集"){
            tcpclient_thread->socket->write("StartToSend\r\n");
            qDebug()<<"(mainwindow.cpp)uart send:"<<"StartToSend\r\n";

            changeState(STATE_START_COLLECT);
            ui->pushButton_StartCollect->setText("结束采集");
        }
    }else{
        return;
    }
}

// 7,保存数据: 将文件名default.csv换成用户命名.csv
void MainWindow::on_pushButton_SaveData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName (this, tr("保存数据"),"",tr("日志文件 (*.csv)"));
    if(!fileName.isEmpty()){
        if(file.isOpen())file.close();
        file.copy("./default.csv",fileName);
        QFile::remove("./default.csv");
    }

    time.clear();
    for(int i = 0; i < 16; i++){value[i].clear();}
    timeCount = 0;

    if(connectType == CONNECT_SERIAL)changeState(STATE_OPEN_SERIAL);
    if(connectType == CONNECT_SOCKET)changeState(STATE_CONNECT_SOCKET);

    ui->pushButton_StartCollect->setText("开始采集");
}

// 8,保存大坐标轴的图像
void MainWindow::PresscontextMenuRequest_1(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (ui->widget->legend->selectTest(pos, false) < 0){
        menu->addAction("保存图像", this, SLOT(PressSaveGraph_1()));
    }
    menu->popup(ui->widget->mapToGlobal(pos));
}
void MainWindow::PressSaveGraph_1()
{
    QString fileName = QFileDialog::getSaveFileName (this,tr("保存图像"),"",tr("图像 (*.png)"));
    ui->widget->savePng(fileName,ui->widget->width(),ui->widget->height());
}

/**************** 辅助函数 *******************************/
// 定时自动保存文件
void MainWindow::on_auto_save_file()
{
    if(AutoSavePeriod != 0){
        if(timerCount == 120){
             timerCount = 0;
             QString autosavefilename = AutoSaveFile + "扰度值" + QString::number(AutoSaveFileId) + ".csv";
             if(file.isOpen())file.close();
             file.copy("./default.csv",autosavefilename);
             QFile::remove("./default.csv");
             file.open(QIODevice::ReadWrite);
             AutoSaveFileId++;
             if(AutoSaveFileId >= 65530) AutoSaveFileId = 0;
        }
        else{
            timerCount++;
        }
    }
}
// 根据不同的状态设置软件的不同按钮状态
void MainWindow::changeState(STATE_TYPE type)
{
    switch(type)
    {
    case STATE_NULL:
        ui->Port->setEditable(true);
        ui->pushButton_GetCOM->setEnabled(true);
        ui->pushButton_wireless->setEnabled(true);
        ui->pushButton_SocketConnect->setEnabled(true);

        ui->pushButton_SetParam->setEnabled(false);
//        ui->pushButton_SetServer->setEnabled(false);
//        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_StartCollect->setEnabled(false);
        ui->pushButton_SaveData->setEnabled(false);

        connectType = CONNECT_NULL;
        isStartCollect = false;
        if(ui->pushButton_StartCollect->text() == "继续采集")ui->pushButton_StartCollect->setText("开始采集");
        time.remove(0, time.length());
        for(int i = 0; i < 16; i++){value[i].remove(0, value[i].length());}
        if(file.isOpen())file.close();
        break;

    case STATE_OPEN_SERIAL:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        ui->pushButton_wireless->setEnabled(true);
        ui->pushButton_SocketConnect->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(true);
//        ui->pushButton_SetServer->setEnabled(true);
//        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(false);

        connectType = CONNECT_SERIAL;
        isStartCollect = false;
        if(file.isOpen())file.close();
        break;

    case STATE_START_COLLECT:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        ui->pushButton_wireless->setEnabled(false);
        ui->pushButton_SocketConnect->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(false);
//        ui->pushButton_SetServer->setEnabled(false);
//        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(false);

        isStartCollect = true;
        if(!file.isOpen())file.open( QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text);
        break;

    case STATE_STOP_COLLECT:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        if(connectType == CONNECT_SOCKET)ui->pushButton_SocketConnect->setEnabled(true);
        if(connectType == CONNECT_SERIAL)ui->pushButton_wireless->setEnabled(true);

        ui->pushButton_SetParam->setEnabled(true);
//        ui->pushButton_SetServer->setEnabled(true);
//        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(true);

        isStartCollect = false;
        if(file.isOpen())file.close();
        break;

    case STATE_CONNECT_SOCKET:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        ui->pushButton_wireless->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(true);
//        ui->pushButton_SetServer->setEnabled(true);
//        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(false);

        connectType = CONNECT_SOCKET;
        isStartCollect = false;
        if(file.isOpen())file.close();
        break;
    }
}
// 判断可用通道,显示可用通道
void MainWindow::flush_checkBox(void)
{
    if(isChannal[0]){
        ui->checkBox_1->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_1->setStyleSheet(STYLE_RED);
    }
    if(isChannal[1]){
        ui->checkBox_2->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_2->setStyleSheet(STYLE_RED);
    }
    if(isChannal[2]){
        ui->checkBox_3->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_3->setStyleSheet(STYLE_RED);
    }
    if(isChannal[3]){
        ui->checkBox_4->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_4->setStyleSheet(STYLE_RED);
    }
    if(isChannal[4]){
        ui->checkBox_5->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_5->setStyleSheet(STYLE_RED);
    }
    if(isChannal[5]){
        ui->checkBox_6->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_6->setStyleSheet(STYLE_RED);
    }
    if(isChannal[6]){
        ui->checkBox_7->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_7->setStyleSheet(STYLE_RED);
    }
    if(isChannal[7]){
        ui->checkBox_8->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_8->setStyleSheet(STYLE_RED);
    }
    if(isChannal[8]){
        ui->checkBox_9->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_9->setStyleSheet(STYLE_RED);
    }
    if(isChannal[9]){
        ui->checkBox_10->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_10->setStyleSheet(STYLE_RED);
    }
    if(isChannal[10]){
        ui->checkBox_11->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_11->setStyleSheet(STYLE_RED);
    }
    if(isChannal[11]){
        ui->checkBox_12->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_12->setStyleSheet(STYLE_RED);
    }
    if(isChannal[12]){
        ui->checkBox_13->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_13->setStyleSheet(STYLE_RED);
    }
    if(isChannal[13]){
        ui->checkBox_14->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_14->setStyleSheet(STYLE_RED);
    }
    if(isChannal[14]){
        ui->checkBox_15->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_15->setStyleSheet(STYLE_RED);
    }
    if(isChannal[15]){
        ui->checkBox_16->setStyleSheet(STYLE_GREEN);
    }else{
        ui->checkBox_16->setStyleSheet(STYLE_RED);
    }
}
