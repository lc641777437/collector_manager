#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>
#include "qnamespace.h"



QVector<double> time;
QVector<double> value[16];
QFile file("./default.csv");

int samplerate = 200;

extern unsigned int timeCount;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("采集分析软件");
    file.setFileName("default.csv");

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

    tcpclient_thread = new TcpClientThread("tcpclientthread", this);
    tcpclient_thread->socket = new QTcpSocket;
    connect(tcpclient_thread->socket,SIGNAL(connected()),tcpclient_thread,SLOT(socketconnected()));
    connect(tcpclient_thread->socket, SIGNAL(readyRead()), tcpclient_thread, SLOT(socketreadyread()));
    tcpclient_thread->timer = new QTimer(this);
    connect(tcpclient_thread->timer, SIGNAL(timeout()), tcpclient_thread, SLOT(tcptimeout()));
    tcpclient_thread->start();

    uart_thread = new UartThread("uartthread", this);
    uart_thread->my_serialport= new QSerialPort;
    connect(uart_thread->my_serialport, SIGNAL(readyRead()), uart_thread, SLOT(UART_RX_Handler()));
    uart_thread->start();

    graph_thread = new GraphThread("graphthread", this);
    graph_thread->start();

    on_checkUartPort();
}

MainWindow::~MainWindow()
{
    uart_thread->quit();
    graph_thread->quit();
    tcpclient_thread->quit();
    if(file.isOpen())file.close();
    delete ui;
}

void MainWindow::on_pushButton_wireless_clicked()
{
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
         if(!isOK)
         {
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

void MainWindow::on_pushButton_SocketConnect_clicked()
{
    static int count = 0;
    if(ui->pushButton_SocketConnect->text() != "断开连接"){
        tcpclient_thread->socket->connectToHost("192.168.0.7",23,QTcpSocket::ReadWrite);
        tcpclient_thread->timer->start(TIMEOUTTIME);
    }else{
        tcpclient_thread->socket->close();
        changeState(STATE_NULL);
        ui->pushButton_SocketConnect->setText("局域\n网络连接");
    }
}

void MainWindow::on_checkUartPort()
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

void MainWindow::on_pushButton_StartCollect_clicked()
{
    if(connectType != CONNECT_SOCKET)return;
    if(ui->pushButton_StartCollect->text() == "开始采集"){
        tcpclient_thread->socket->write("StartToSend\r\n");
        tcpclient_thread->timer->start(TIMEOUTTIME);
        qDebug()<<"socket send:"<<"StartToSend\r\n";

        changeState(STATE_START_COLLECT);
        ui->pushButton_StartCollect->setText("结束采集");
    }else if(ui->pushButton_StartCollect->text() == "结束采集"){
        tcpclient_thread->socket->write("StopToSend\r\n");
        tcpclient_thread->timer->start(TIMEOUTTIME);
        qDebug()<<"uart send:"<<"StopToSend\r\n";

        changeState(STATE_STOP_COLLECT);
        ui->pushButton_StartCollect->setText("继续采集");
    }else if(ui->pushButton_StartCollect->text() == "继续采集"){
        tcpclient_thread->socket->write("StartToSend\r\n");
        tcpclient_thread->timer->start(TIMEOUTTIME);
        qDebug()<<"uart send:"<<"StartToSend\r\n";

        changeState(STATE_START_COLLECT);
        ui->pushButton_StartCollect->setText("结束采集");
    }
}

void MainWindow::on_pushButton_SaveData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName (this, tr("保存数据"),"",tr("日志文件 (*.csv)"));
    if(!fileName.isEmpty()){
        if(file.isOpen())file.close();
        file.copy("./default.csv",fileName);
        QFile::remove("./default.csv");
    }

    time.clear();
    for(int i = 0; i < 16; i++){
        value[i].clear();
    }
    timeCount = 0;

    if(connectType == CONNECT_SERIAL)changeState(STATE_OPEN_SERIAL);
    if(connectType == CONNECT_SOCKET)changeState(STATE_CONNECT_SOCKET);

    ui->pushButton_StartCollect->setText("开始采集");
}


void MainWindow::on_pushButton_SetParam_clicked()
{
    if(connectType == CONNECT_SERIAL){
        uart_thread->my_serialport->write("GetParam\r\n");
        uart_thread->timer->start(TIMEOUTTIME);
    }else if(connectType == CONNECT_SOCKET){
        tcpclient_thread->socket->write("GetParam\r\n");
        tcpclient_thread->timer->start(TIMEOUTTIME);
    }
}

void MainWindow::on_pushButton_Reset_2_clicked()
{
    if(connectType == CONNECT_SERIAL || connectType == CONNECT_SOCKET){
        bool isOK;
        QStringList list;
        list<<tr("恢复出厂设置")<<tr("点错了");
        QString select=QInputDialog::getItem(this,tr("采集分析软件"),tr("点击确定"),list,0,false,&isOK);
        if(select == "恢复出厂设置" && isOK){
            if(connectType == CONNECT_SERIAL){
                uart_thread->my_serialport->write("ResetOption\r\n");
                uart_thread->timer->start(TIMEOUTTIME);
            }else if(connectType == CONNECT_SOCKET){
                tcpclient_thread->socket->write("ResetOption\r\n");
                tcpclient_thread->timer->start(TIMEOUTTIME);
            }
        }
    }
}

void MainWindow::on_pushButton_SetServer_clicked()
{
    if(connectType == CONNECT_SERIAL || connectType == CONNECT_SOCKET){
        QString server = QInputDialog::getText(this,tr("采集分析软件"),tr("域名或IP地址:端口"));
        if(server.length() == 0)return;
        qDebug()<<QString("SetServer" + server + "\r\n");
        QByteArray message;
        message.append(QString("SetServer" + server + "\r\n"));
        if(connectType == CONNECT_SERIAL){
            uart_thread->my_serialport->write(message);
            uart_thread->timer->start(TIMEOUTTIME);
        }else if(connectType == CONNECT_SOCKET){
            tcpclient_thread->socket->write(message);
            tcpclient_thread->timer->start(TIMEOUTTIME);
        }
    }
}

void MainWindow::on_checkBox_clicked()
{
    int count = 0,i;
    bool tmp_box[16] = {false};

    if(ui->checkBox_1->isChecked())tmp_box[0] = true;
    if(ui->checkBox_2->isChecked())tmp_box[1] = true;
    if(ui->checkBox_3->isChecked())tmp_box[2] = true;
    if(ui->checkBox_4->isChecked())tmp_box[3] = true;
    if(ui->checkBox_5->isChecked())tmp_box[4] = true;
    if(ui->checkBox_6->isChecked())tmp_box[5] = true;
    if(ui->checkBox_7->isChecked())tmp_box[6] = true;
    if(ui->checkBox_8->isChecked())tmp_box[7] = true;
    if(ui->checkBox_9->isChecked())tmp_box[8] = true;
    if(ui->checkBox_10->isChecked())tmp_box[9] = true;
    if(ui->checkBox_11->isChecked())tmp_box[10] = true;
    if(ui->checkBox_12->isChecked())tmp_box[11] = true;
    if(ui->checkBox_13->isChecked())tmp_box[12] = true;
    if(ui->checkBox_14->isChecked())tmp_box[13] = true;
    if(ui->checkBox_15->isChecked())tmp_box[14] = true;
    if(ui->checkBox_16->isChecked())tmp_box[15] = true;

    for(i = 0,count = 0; i < 16; i++){
        if(box[i])count++;
    }

    for(i = 0; i < 16; i++){
        if(box[i] != tmp_box[i])break;
    }

    if(count <= 3)box[i] = tmp_box[i];

    if(count >= 4){
        if(tmp_box[i] == true){
            qDebug()<<"channal"<<i+1<<"clicked";
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
}

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
        ui->pushButton_SetServer->setEnabled(false);
        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_StartCollect->setEnabled(false);
        ui->pushButton_SaveData->setEnabled(false);

        connectType = CONNECT_NULL;
        if(file.isOpen())file.close();
        break;

    case STATE_OPEN_SERIAL:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        ui->pushButton_wireless->setEnabled(true);
        ui->pushButton_SocketConnect->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(true);
        ui->pushButton_SetServer->setEnabled(true);
        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(false);
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
        ui->pushButton_SetServer->setEnabled(false);
        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(false);

        isStartCollect = true;
        if(!file.isOpen())file.open( QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text);
        break;

    case STATE_STOP_COLLECT:
        ui->Port->setEditable(false);
        ui->pushButton_GetCOM->setEnabled(false);
        ui->pushButton_wireless->setEnabled(false);
        ui->pushButton_SocketConnect->setEnabled(true);

        ui->pushButton_SetParam->setEnabled(true);
        ui->pushButton_SetServer->setEnabled(true);
        ui->pushButton_Reset_2->setEnabled(true);
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
        ui->pushButton_SetServer->setEnabled(true);
        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SaveData->setEnabled(false);

        connectType = CONNECT_SOCKET;
        isStartCollect = false;
        if(file.isOpen())file.close();
        break;
    }
}

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
void MainWindow::PresscontextMenuRequest_2(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (ui->widget_2->legend->selectTest(pos, false) < 0){
        menu->addAction("保存图像", this, SLOT(PressSaveGraph_2()));
    }
    menu->popup(ui->widget_2->mapToGlobal(pos));
}
void MainWindow::PressSaveGraph_2()
{
    QString fileName = QFileDialog::getSaveFileName (this,tr("保存图像"),"",tr("图像 (*.png)"));
    ui->widget_2->savePng(fileName,ui->widget_2->width(),ui->widget_2->height());
}
void MainWindow::PresscontextMenuRequest_3(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (ui->widget_3->legend->selectTest(pos, false) < 0){
        menu->addAction("保存图像", this, SLOT(PressSaveGraph_3()));
    }
    menu->popup(ui->widget_3->mapToGlobal(pos));
}
void MainWindow::PressSaveGraph_3()
{
    QString fileName = QFileDialog::getSaveFileName (this,tr("保存图像"),"",tr("图像 (*.png)"));
    ui->widget_3->savePng(fileName,ui->widget_3->width(),ui->widget_3->height());
}
void MainWindow::PresscontextMenuRequest_4(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (ui->widget_4->legend->selectTest(pos, false) < 0){
        menu->addAction("保存图像", this, SLOT(PressSaveGraph_4()));
    }
    menu->popup(ui->widget_4->mapToGlobal(pos));
}
void MainWindow::PressSaveGraph_4()
{
    QString fileName = QFileDialog::getSaveFileName (this,tr("保存图像"),"",tr("图像 (*.png)"));
    ui->widget_4->savePng(fileName,ui->widget_4->width(),ui->widget_4->height());
}

