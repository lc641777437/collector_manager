#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>


QByteArray ReadData;
QVector<double> time;
QVector<double> value[16];
bool isChannal[16] = {0};
const char tag[2] = {0xA5,0xA5};

QFile file("./default.csv");

int timer_Count;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("采集分析软件");

    initSeialPort();

    uart_thread = new UartThread("uartthread", this);
    uart_thread->start();
    text_thread = new TextTread("textthread", this);
    text_thread->start();

    uart_thread->my_serialport= new QSerialPort;
    connect(uart_thread->my_serialport,SIGNAL(readyRead()),uart_thread,SLOT(UART_RX_Handler()));

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

        uart_thread->my_serialport->setPortName(ui->Port->currentText());
        uart_thread->my_serialport->open(QIODevice::ReadWrite);
        uart_thread->my_serialport->setBaudRate(ui->Bound->currentText().toInt(),QSerialPort::AllDirections);
        uart_thread->my_serialport->setDataBits(QSerialPort::Data8);
        uart_thread->my_serialport->setParity(QSerialPort::NoParity);
        uart_thread->my_serialport->setStopBits(QSerialPort::OneStop);
        uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);
        uart_thread->my_serialport->setFlowControl(QSerialPort::NoFlowControl);

        ui->Port->setEditable(false);
        ui->Bound->setEditable(false);
        ui->Check->setEditable(false);
        ui->Stop->setEditable(false);
        ui->Data->setEnabled(false);
        ui->pushButton_StartCollect->setEnabled(true);
        ui->pushButton_setSampleRate->setEnabled(true);
        ui->pushButton_SetDeviceID->setEnabled(true);
    }
    else
    {
        ui->pushButton_OpenSerial->setText("打开串口");
        uart_thread->my_serialport->close();
        ui->Port->setEditable(true);
        ui->Bound->setEditable(true);
        ui->Check->setEditable(true);
        ui->Stop->setEditable(true);
        ui->Data->setEnabled(true);
        ui->pushButton_StartCollect->setEnabled(false);
        ui->pushButton_setSampleRate->setEnabled(false);
        ui->pushButton_SetDeviceID->setEnabled(false);
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
void MainWindow::on_pushButton_SetDeviceID_clicked()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL,"Set Device ID","Pleace Enter one ID", QLineEdit::Normal,NULL,&isOK);
    if(text.isEmpty() || ui->pushButton_OpenSerial->text() == "打开串口")return;
    uart_thread->my_serialport->write("SetDeviceID:" + text.toLatin1() + "\r\n");
}

void MainWindow::on_pushButton_Send_clicked()
{
    if(ui->Input->text().isEmpty() || ui->pushButton_OpenSerial->text() == "打开串口")
        return;
    if(ui->check_newLine->isChecked())
        uart_thread->my_serialport->write(ui->Input->text().toLatin1() + "\r\n");
    else
        uart_thread->my_serialport->write(ui->Input->text().toLatin1());
}

void MainWindow::on_pushButton_ClearText_clicked()
{
    ui->TextPlain->clear();
}

void MainWindow::on_pushButton_GetCOM_clicked()
{
    initSeialPort();
}

void MainWindow::on_pushButton_setSampleRate_clicked()
{
    if(ui->pushButton_OpenSerial->text() == "打开串口")
        return;
    uart_thread->my_serialport->write("SampleRate:"+ui->comboBox_SampleRate->currentText().toLatin1() + "\r\n");
}

void MainWindow::on_pushButton_StartCollect_clicked()
{
    if(ui->pushButton_StartCollect->text() == "开始采集")
    {
        if(ui->pushButton_OpenSerial->text() == "打开串口")return;
        ui->pushButton_StartCollect->setText("结束采集");

        ui->pushButton_OpenSerial->setEnabled(false);
        file.open( QIODevice::Append | QIODevice::Text);

    }
    else if(ui->pushButton_StartCollect->text() == "结束采集")
    {
        ui->pushButton_StartCollect->setText("继续采集");

        ui->pushButton_Reset->setEnabled(true);
        ui->pushButton_OpenSerial->setEnabled(true);

        file.close();

    }
    else if(ui->pushButton_StartCollect->text() == "继续采集")
    {
        if(ui->pushButton_OpenSerial->text() == "打开串口")return;
        ui->pushButton_StartCollect->setText("结束采集");

        ui->pushButton_Reset->setEnabled(false);
        ui->pushButton_OpenSerial->setEnabled(false);

        file.open( QIODevice::Append | QIODevice::Text);
    }
}


void MainWindow::on_pushButton_Reset_clicked()
{
    if(ui->pushButton_OpenSerial->text() == "打开串口")return;
    ui->pushButton_OpenSerial->setEnabled(true);
    ui->pushButton_Reset->setEnabled(false);
    ui->pushButton_StartCollect->setText("开始采集");
}
