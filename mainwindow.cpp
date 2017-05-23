#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>
#include "qnamespace.h"

QByteArray ReadData;
QVector<double> time;
QVector<double> value[16];
QFile file("./default.csv");

bool isChannal[16] = {0};
int samplerate = 200;
bool box[16] = {false};

extern unsigned int timeCount;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("采集分析软件");

    initSeialPort();

    this->isStart = false;

    uart_thread = new UartThread("uartthread", this);
    uart_thread->start();
    text_thread = new TextTread("textthread", this);
    text_thread->start();

    uart_thread->my_serialport= new QSerialPort;
    connect(uart_thread->my_serialport,SIGNAL(readyRead()),uart_thread,SLOT(UART_RX_Handler()));

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
}

MainWindow::~MainWindow()
{
    uart_thread->quit();
    text_thread->quit();
    if(file.isOpen())file.close();
    delete ui;
}

void MainWindow::on_pushButton_OpenSerial_clicked()
{
    static int count = 0;

    if(ui->Port->currentText() == "NONE")
    {
        return;
    }

    if(++count%2 != 0)
    {
        ui->pushButton_OpenSerial->setText("关闭串口");
        uart_state = true;
        isWireless = false;

        uart_thread->my_serialport->setPortName(ui->Port->currentText());
        uart_thread->my_serialport->open(QIODevice::ReadWrite);
        uart_thread->my_serialport->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
        uart_thread->my_serialport->setDataBits(QSerialPort::Data8);
        uart_thread->my_serialport->setParity(QSerialPort::NoParity);
        uart_thread->my_serialport->setStopBits(QSerialPort::OneStop);
        uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);
        uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);

        ui->Port->setEditable(false);
        ui->pushButton_wireless->setEnabled(false);

        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_SetParam->setEnabled(true);

        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_SetServer->setEnabled(true);
    }
    else
    {
        ui->pushButton_OpenSerial->setText("有线串口");
        uart_state = false;
        uart_thread->my_serialport->close();
        ui->pushButton_wireless->setEnabled(true);


        ui->Port->setEditable(true);
        ui->pushButton_StartCollect->setEnabled(false);
        ui->pushButton_SetParam->setEnabled(false);
        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_SetServer->setEnabled(false);
    }
}

void MainWindow::on_pushButton_wireless_clicked()
{
     static int count = 0;

     if(ui->Port->currentText() == "NONE")
     {
         return;
     }

     if(++count%2 != 0)
     {
         ui->pushButton_wireless->setText("关闭串口");
         uart_state = true;
         isWireless = true;
         uart_thread->my_serialport->setPortName(ui->Port->currentText());
         uart_thread->my_serialport->open(QIODevice::ReadWrite);
         uart_thread->my_serialport->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
         uart_thread->my_serialport->setDataBits(QSerialPort::Data8);
         uart_thread->my_serialport->setParity(QSerialPort::NoParity);
         uart_thread->my_serialport->setStopBits(QSerialPort::OneStop);
         uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);
         uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);

         ui->Port->setEditable(false);
         ui->pushButton_OpenSerial->setEnabled(false);

         ui->pushButton_StartCollect->setEnabled(true);
         ui->pushButton_SetParam->setEnabled(true);
         ui->pushButton_Reset_2->setEnabled(true);
         ui->pushButton_SetServer->setEnabled(true);
     }
     else
     {
         ui->pushButton_wireless->setText("无线串口");
         uart_state = false;

         uart_thread->my_serialport->close();

         //ui->Port->pushButton_SetServer->setEditable(true);
         ui->pushButton_OpenSerial->setEnabled(true);

         ui->pushButton_StartCollect->setEnabled(false);
         ui->pushButton_SetParam->setEnabled(false);
         ui->pushButton_Reset_2->setEnabled(false);
         ui->pushButton_SetServer->setEnabled(false);
     }


}

void MainWindow::initSeialPort()
{
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    ui->Port->clear();
    if(infos.isEmpty())
    {
        ui->Port->addItem("NONE");
        return;
    }
    foreach (QSerialPortInfo info, infos)
    {
        ui->Port->addItem(info.portName());
    }
}

void MainWindow::on_pushButton_Send_clicked()
{
    if(ui->Input->text().isEmpty() || !uart_state)
        return;
    if(ui->check_newLine->isChecked())
        uart_thread->my_serialport->write(ui->Input->text().toLatin1() + "\r\n");
    else
        uart_thread->my_serialport->write(ui->Input->text().toLatin1());
}



void MainWindow::on_pushButton_GetCOM_clicked()
{
    initSeialPort();
}

void MainWindow::on_pushButton_StartCollect_clicked()
{
    if(!uart_state)return;
    if(ui->pushButton_StartCollect->text() == "开始采集")
    {
        ui->pushButton_OpenSerial->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(false);
        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_SetServer->setEnabled(false);

        file.open( QIODevice::ReadWrite | QIODevice::Text);
        uart_thread->my_serialport->write("StartToSend\r\n");
        ui->pushButton_StartCollect->setText("结束采集");
    }
    else if(ui->pushButton_StartCollect->text() == "结束采集")
    {

        ui->pushButton_Reset->setEnabled(true);
        if(isWireless)
        {
            ui->pushButton_wireless->setEnabled(true);
        }
        else
        {
            ui->pushButton_OpenSerial->setEnabled(true);
        }


        ui->pushButton_SetParam->setEnabled(true);
        ui->pushButton_Reset_2->setEnabled(true);
        ui->pushButton_SetServer->setEnabled(true);


        file.close();
        uart_thread->my_serialport->write("StopToSend\r\n");
        uart_thread->timer->start(2000);
        qDebug()<<"uart send:"<<"StopToSend\r\n";
        this->isStart = false;
        ui->pushButton_StartCollect->setText("继续采集");
    }
    else if(ui->pushButton_StartCollect->text() == "继续采集")
    {
        if(!uart_state)return;

        ui->pushButton_Reset->setEnabled(false);
        ui->pushButton_OpenSerial->setEnabled(false);
        ui->pushButton_wireless->setEnabled(false);

        ui->pushButton_SetParam->setEnabled(false);
        ui->pushButton_Reset_2->setEnabled(false);
        ui->pushButton_SetServer->setEnabled(false);


        file.open( QIODevice::Append | QIODevice::Text);
        uart_thread->my_serialport->write("StartToSend\r\n");
        qDebug()<<"uart send:"<<"StartToSend\r\n";
        ui->pushButton_StartCollect->setText("结束采集");
    }
}


void MainWindow::on_pushButton_Reset_clicked()
{
    if(!uart_state)return;

    QString fileName = QFileDialog::getSaveFileName (this, tr("保存数据"),"",tr("日志文件 (*.csv)"));
    if(!fileName.isEmpty ())
    {
          file.copy("./default.csv",fileName);
          QFile::remove("./default.csv");
    }

    ui->pushButton_OpenSerial->setEnabled(true);
    ui->pushButton_Reset->setEnabled(false);
    isStart = false;
    time.clear();
    for(int i = 0;i<16;i++)
    {
        value[i].clear();
    }
    timeCount = 0;
    ui->pushButton_StartCollect->setText("开始采集");
}

void MainWindow::on_pushButton_SetParam_clicked()
{
    if(!uart_state)return;
    uart_thread->my_serialport->write("GetParam\r\n");
    uart_thread->timer->start(2000);
}

void MainWindow::on_pushButton_Reset_2_clicked()
{
    if(!uart_state)return;
    QStringList list;
    bool isOK;
    list<<tr("恢复出厂设置")<<tr("点错了");
    QString select=QInputDialog::getItem(this,tr("采集分析软件"),tr("点击确定"),list,0,false,&isOK);
    if(select == "恢复出厂设置" && isOK)
    {
        uart_thread->my_serialport->write("ResetOption\r\n");
        uart_thread->timer->start(2000);
    }
}

void MainWindow::on_pushButton_SetServer_clicked()
{
    if(!uart_state)return;

    QString server = QInputDialog::getText(this,tr("采集分析软件"),tr("域名或IP地址:端口"));
    if(server.length() != 0)
    {
        qDebug()<<QString("SetServer" + server + "\r\n");
        QByteArray message;
        message.append(QString("SetServer" + server + "\r\n"));
        uart_thread->my_serialport->write(message);
        uart_thread->timer->start(2000);
    }
}

void MainWindow::on_checkBox_clicked()
{
    int count = 0,i;
    bool tmp_box[16] = {false};

    if(ui->checkBox_1->isChecked())
    {
        tmp_box[0] = true;
    }
    if(ui->checkBox_2->isChecked())
    {
        tmp_box[1] = true;
    }
    if(ui->checkBox_3->isChecked())
    {
        tmp_box[2] = true;
    }

    if(ui->checkBox_4->isChecked())
    {
        tmp_box[3] = true;
    }
    if(ui->checkBox_5->isChecked())
    {
        tmp_box[4] = true;
    }

    if(ui->checkBox_6->isChecked())
    {
        tmp_box[5] = true;
    }

    if(ui->checkBox_7->isChecked())
    {
        tmp_box[6] = true;
    }

    if(ui->checkBox_8->isChecked())
    {
        tmp_box[7] = true;
    }
    if(ui->checkBox_9->isChecked())
    {
        tmp_box[8] = true;
    }

    if(ui->checkBox_10->isChecked())
    {
        tmp_box[9] = true;
    }

    if(ui->checkBox_11->isChecked())
    {
        tmp_box[10] = true;
    }

    if(ui->checkBox_12->isChecked())
    {
        tmp_box[11] = true;
    }

    if(ui->checkBox_13->isChecked())
    {
        tmp_box[12] = true;
    }

    if(ui->checkBox_14->isChecked())
    {
        tmp_box[13] = true;
    }

    if(ui->checkBox_15->isChecked())
    {
        tmp_box[14] = true;
    }

    if(ui->checkBox_16->isChecked())
    {
        tmp_box[15] = true;
    }

    for(i = 0,count = 0; i < 16; i++)
    {
        if(box[i])count++;
    }

    for(i = 0; i < 16; i++)
    {
        if(box[i] != tmp_box[i])break;
    }
    if(count <= 3)box[i] = tmp_box[i];

    if(count >= 4)
    {
        if(tmp_box[i] == true)
        {
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

        }
        else
        {
            box[i] = false;
        }
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
