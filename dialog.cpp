#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

extern unsigned short ctrl;
#include <QDebug>
Dialog::Dialog(QWidget *parent, unsigned char devIDH, unsigned char devIDL, unsigned char ctrlH, unsigned char ctrlL,\
               unsigned char fre, unsigned char sendTimeServer, unsigned char sendTimeDynamic) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("参数设置");
    pMainWindow = static_cast<MainWindow *>(parent);
    QRegExp regExp("[0-9]{0,5}");
    ui->lineEdit_DevID->setValidator(new QRegExpValidator(regExp,this));


    int devid = 0;
    devid = devIDH;
    devid <<= 8;
    devid += devIDL;
    this->ui->lineEdit_DevID->setText(QString::number(devid));

    if(ctrlL&0x01){
        ui->comboBox->setCurrentText("电压");
    }else{
        ui->comboBox->setCurrentText("电流");
    }
    if(ctrlL&0x02){
        ui->comboBox_2->setCurrentText("电压");
    }else{
        ui->comboBox_2->setCurrentText("电流");
    }
    if(ctrlL&0x04){
        ui->comboBox_3->setCurrentText("电压");
    }else{
        ui->comboBox_3->setCurrentText("电流");
    }
    if(ctrlL&0x08){
        ui->comboBox_4->setCurrentText("电压");
    }else{
        ui->comboBox_4->setCurrentText("电流");
    }
    if(ctrlL&0x10)
    {
        ui->comboBox_5->setCurrentText("电压");
    }else{
        ui->comboBox_5->setCurrentText("电流");
    }
    if(ctrlL&0x20){
        ui->comboBox_6->setCurrentText("电压");
    }else{
        ui->comboBox_6->setCurrentText("电流");
    }
    if(ctrlL&0x40){
        ui->comboBox_7->setCurrentText("电压");
    }else{
        ui->comboBox_7->setCurrentText("电流");
    }
    if(ctrlL&0x80){
        ui->comboBox_8->setCurrentText("电压");
    }else{
        ui->comboBox_8->setCurrentText("电流");
    }
    if(ctrlH&0x01){
        ui->comboBox_9->setCurrentText("电压");
    }else{
        ui->comboBox_9->setCurrentText("电流");
    }
    if(ctrlH&0x02){
        ui->comboBox_10->setCurrentText("电压");
    }else{
        ui->comboBox_10->setCurrentText("电流");
    }
    if(ctrlH&0x04){
        ui->comboBox_11->setCurrentText("电压");
    }else{
        ui->comboBox_11->setCurrentText("电流");
    }
    if(ctrlH&0x08){
        ui->comboBox_12->setCurrentText("电压");
    }else{
        ui->comboBox_12->setCurrentText("电流");
    }
    if(ctrlH&0x10){
        ui->comboBox_13->setCurrentText("电压");
    }else{
        ui->comboBox_13->setCurrentText("电流");
    }
    if(ctrlH&0x20){
        ui->comboBox_14->setCurrentText("电压");
    }else{
        ui->comboBox_14->setCurrentText("电流");
    }
    if(ctrlH&0x40){
        ui->comboBox_15->setCurrentText("电压");
    } else{
        ui->comboBox_15->setCurrentText("电流");
    }
    if(ctrlH&0x80){
        ui->comboBox_16->setCurrentText("电压");
    }
    else{
        ui->comboBox_16->setCurrentText("电流");
    }

    ui->comboBox_SampleRte->setCurrentText(QString::number(fre));
    ui->comboBox_SendTime2erver->setCurrentText(QString::number(sendTimeServer));
    ui->comboBox_SendTimeDynamic->setCurrentText(QString::number(sendTimeDynamic));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::accept()
{
    unsigned int tmp = 0;
    tmp = ui->lineEdit_DevID->text().toInt();
    if(tmp > 65536)
    {
        ui->label__Message->setText("设备ID必须在0 - 65536之间");
        ui->label__Message->setStyleSheet("color:red;");
        return;
    }
    this->pDevIDH = (tmp>>8) & 0XFF;
    this->pDevIDL = tmp & 0XFF;
    qDebug()<<this->pDevIDH<<this->pDevIDL;
    tmp = 0;
    if(ui->comboBox->currentText() == "电压"){
        tmp |= 1<<0;
    }
    if(ui->comboBox_2->currentText() == "电压"){
        tmp |= 1<<1;
    }
    if(ui->comboBox_3->currentText() == "电压"){
        tmp |= 1<<2;
    }
    if(ui->comboBox_4->currentText() == "电压"){
        tmp |= 1<<3;
    }
    if(ui->comboBox_5->currentText() == "电压"){
        tmp |= 1<<4;
    }
    if(ui->comboBox_6->currentText() == "电压"){
        tmp |= 1<<5;
    }
    if(ui->comboBox_7->currentText() == "电压"){
        tmp |= 1<<6;
    }
    if(ui->comboBox_8->currentText() == "电压"){
        tmp |= 1<<7;
    }
    if(ui->comboBox_9->currentText() == "电压"){
        tmp |= 1<<8;
    }
    if(ui->comboBox_10->currentText() == "电压"){
        tmp |= 1<<9;
    }
    if(ui->comboBox_11->currentText() == "电压"){
        tmp |= 1<<10;
    }
    if(ui->comboBox_12->currentText() == "电压"){
        tmp |= 1<<11;
    }
    if(ui->comboBox_13->currentText() == "电压"){
        tmp |= 1<<12;
    }
    if(ui->comboBox_14->currentText() == "电压"){
        tmp |= 1<<13;
    }
    if(ui->comboBox_15->currentText() == "电压"){
        tmp |= 1<<14;
    }
    if(ui->comboBox_16->currentText() == "电压"){
        tmp |= 1<<15;
    }
    this->pCtrlH = (tmp>>8) && 0XFF;
    this->pCtrlL = tmp && 0XFF;
    if(ui->comboBox_SampleRte->currentText().toInt() > 20 &&
            pMainWindow->uart_thread->my_serialport->baudRate() == QSerialPort::Baud38400)
    {
        QMessageBox::information(pMainWindow, tr("采集分析软件"),
                tr("采样频率20以上,本地无线采集将失效!\n要支持更高的频率，请用有线串口进行采集！"));
    }
    this->pFre = ui->comboBox_SampleRte->currentText().toInt();
    this->pSendTimeServer = ui->comboBox_SendTime2erver->currentText().toInt();
    this->pSendTimeDynamic = ui->comboBox_SendTimeDynamic->currentText().toInt();

    Dialog::done(0);
}

void Dialog::reject()
{
    Dialog::done(-1);
}
