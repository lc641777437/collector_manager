#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QPalette>
#include "ui_dialog.h"

extern unsigned short ctrl;
#include <QDebug>

/*************** 初始化 ********************************/
/*
 * 入参:
 *   设备ID: devIDH,devIDL
 *   采样频率: fre
 *   服务器发送间隔: sendTimeServer
 *   触发态发送间隔: sendTimeDynamic
 *   采样类型: ctrL,ctrH
*/
Dialog::Dialog(QWidget *parent, unsigned char devIDH, unsigned char devIDL, unsigned char ctrlH, unsigned char ctrlL,\
               unsigned char fre, unsigned char sendTimeServer, unsigned char sendTimeDynamic,QString _proId,QString _proName,\
               QString _testPointName[16]) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    // 1,窗口设置
    this->orangeLine = 3000;
    this->redLine = 5000;
    ui->setupUi(this);
    this->setWindowTitle("参数设置");
    pMainWindow = static_cast<MainWindow *>(parent);
    pMainWindow->readInitialValue = true;
    for(int i = 0;i<20;i++) isSelected[i] = false;

    /******************** (1),设备上传的配置 **************/
    // 1,设备ID
    int devid = 0;
    devid = devIDH;
    devid <<= 8;
    devid += devIDL;
    QRegExp regExp("[0-9]{0,5}");
    ui->lineEdit_DevID->setValidator(new QRegExpValidator(regExp,this));
    this->ui->lineEdit_DevID->setText(QString::number(devid));
    pDevIDH = devIDH;
    pDevIDL = devIDL;
    // 2,设置采样频率
    ui->comboBox_SampleRte->setCurrentText(QString::number(fre));
    pFre = fre;
    // 3,设置服务器发送间隔
    ui->comboBox_SendTime2erver->setCurrentText(QString::number(sendTimeServer));
    pSendTimeServer = sendTimeServer;
    // 4,设置触发态发送间隔
    ui->comboBox_SendTimeDynamic->setCurrentText(QString::number(sendTimeDynamic));
    pSendTimeDynamic = sendTimeDynamic;
    // 5,设置采样类型
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
    pCtrlL = ctrlL;
    pCtrlH = ctrlH;
    // 6,设置工程流水号
    proId = _proId;
    ui->lineEdit_projectID->setText(proId);
    // 7,设置项目名称
    proName = _proName;
    ui->lineEdit_projectName->setText(proName);
    // 8,设置测试点的名称
    for(int i = 0;i<16;i++){
        testPointName[i] = _testPointName[i];
    }
    ui->lineEdit_test1->setText(testPointName[0]);
    ui->lineEdit_test2->setText(testPointName[1]);
    ui->lineEdit_test3->setText(testPointName[2]);
    ui->lineEdit_test4->setText(testPointName[3]);
    ui->lineEdit_test5->setText(testPointName[4]);
    ui->lineEdit_test6->setText(testPointName[5]);
    ui->lineEdit_test7->setText(testPointName[6]);
    ui->lineEdit_test8->setText(testPointName[7]);

    ui->lineEdit_test9->setText(testPointName[8]);
    ui->lineEdit_test10->setText(testPointName[9]);
    ui->lineEdit_test11->setText(testPointName[10]);
    ui->lineEdit_test12->setText(testPointName[11]);
    ui->lineEdit_test13->setText(testPointName[12]);
    ui->lineEdit_test14->setText(testPointName[13]);
    ui->lineEdit_test15->setText(testPointName[14]);
    ui->lineEdit_test16->setText(testPointName[15]);

     /******************** (2),setting.csv文件保存的配置 **************/
    QFile mfile("./Setting.csv");
    // 有配置文件,则读取配置以设置
    if(mfile.exists()){
        if(!mfile.isOpen()) mfile.open( QIODevice::ReadWrite  |QIODevice::Text);
        QTextStream steam(&mfile);
        // 1,设置服务器地址
        this->ui->lineEdit_serverAddr->setPlaceholderText(tr("域名或 IP 地址: 端口"));
        // 判断是否是同一台设备
        QString h = steam.readLine();
        qDebug()<<"(dialog.cpp)设备号:"<<h;
        int deviceId = h.toInt();
        // 如果是同一台设备,则读取文件配置以设置
        if(deviceId == devid ){
            qDebug()<<"(dialog.cpp)从 'setting.csv' 配置文件读取的设置是: "<<endl;
            // 2,设置自动自动保存间隔
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)自动保存间隔:"<<h;
            ui->comboBox_SaveDataDynamic->setCurrentText(h);
            on_comboBox_SaveDataDynamic_activated(h);     // 根据保存类型来判断是否允许选择自动保存路径

            // 3,设置自动保存路径
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)保存路径:"<<h;
            this->ui->lineEdit_file4save->setText(h);

            // 4,设置密度
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)密度:"<<h;
            this->ui->lineEdit_Density->setText(h);

            // 5,设置标定系数
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)标定系数:"<<h;
            this->ui->lineEdit_biaoding->setText(h);

            // 6,7,设置压强
            h = steam.readLine();
            qDebug()<<"(dialog.cpp) Pmax:"<<h;
//            QStringList pMaxList = h.split(",");
//            double myPmax[20];
//            for(int i = 0;i<16;i++){
//                myPmax[i] = pMaxList.at(i).toDouble();
//            }
            help_setP(h,true);

            h = steam.readLine();
            qDebug()<<"(dialog.cpp) Pmin:"<<h;
//            QStringList pMinList = h.split(",");
//            double myPmin[20];
//            for(int i = 0;i<16;i++){
//                myPmin[i] = pMinList.at(i).toDouble();
//            }
            help_setP(h,false);


            // 8,设置通道数
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)通道数:"<<h;
            QStringList list = h.split(",");
            bool tmp[16] = {false};
            for(int i = 0;i<16;i++){
                if(list.at(i).toInt() == 0){
                    tmp[i] = false;
                }
                else{
                    tmp[i] = true;
                }
            }
            help_setChannel(tmp);

            // 9,设置H初值
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)H初值:"<<h;
            help_setH(h);

            // 10,设置基准点
            h = steam.readLine();
            qDebug()<<"(dialog.cpp)基准点:"<<h;
            help_setBase(h);

        }
        // 如果不是同一台设备,则设置为默认设置
        else{
            // 2,设置自动自动保存间隔
            ui->comboBox_SaveDataDynamic->setCurrentText(tr("手动保存"));
            on_comboBox_SaveDataDynamic_activated(tr("手动保存"));     // 根据保存类型来判断是否允许选择自动保存路径
            // 3,设置自动保存路径
            this->ui->lineEdit_file4save->setText(tr("./"));
            // 4,设置密度
            this->ui->lineEdit_Density->setText(tr("1"));
            // 5,设置标定系数
            this->ui->lineEdit_biaoding->setText(tr("1"));
            // 6,7,设置压强
            //this->ui->lineEdit_Pmax->setText(tr("2000"));
            //this->ui->lineEdit_Pmin->setText(tr("-2000"));
            // 8,设置通道数
            bool tmp[16] = {false};
            for(int i = 0;i<16;i++){
                    tmp[i] = false;
            }
            help_setChannel(tmp);
            // 9, 设置H初值
            // 默认为空
            // 10, 设置基准点
            // 默认为空
            last_baseValue = -1;
        }
    }
    // 没有配置文件,则设置为默认设置
    else{
        // 1,设置服务器地址
        this->ui->lineEdit_serverAddr->setPlaceholderText(tr("域名或 IP 地址: 端口"));
        // 2,设置自动自动保存间隔
        ui->comboBox_SaveDataDynamic->setCurrentText(tr("手动保存"));
        on_comboBox_SaveDataDynamic_activated(tr("手动保存"));     // 根据保存类型来判断是否允许选择自动保存路径
        // 3,设置自动保存路径
        this->ui->lineEdit_file4save->setText(tr("./"));
        // 4,设置密度
        this->ui->lineEdit_Density->setText(tr("1"));
        // 5,设置标定系数
        this->ui->lineEdit_biaoding->setText(tr("1"));
        // 6,7, 设置压强
        //this->ui->lineEdit_Pmax->setText(tr("2000"));
        //this->ui->lineEdit_Pmin->setText(tr("-2000"));
        // 8,设置通道数
        bool tmp[16] = {false};
        for(int i = 0;i<16;i++){
            tmp[i] = false;
        }
        help_setChannel(tmp);
        // 9,设置H初值
        // 默认为空
        // 10,设置基准点
        // 默认为空
        last_baseValue = -1;
    }

    // 绑定基准点选择事件
    connect(ui->checkBox_BaseValue1, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue2, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue3, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue4, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue5, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue6, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue7, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue8, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue9, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue10, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue11, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue12, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue13, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue14, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue15, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));
    connect(ui->checkBox_BaseValue16, SIGNAL(clicked()), this, SLOT(on_checkBox_BaseValue_clicked()));

     // 绑定通道数选择事件
     connect(ui->checkBox_1,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_2,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_3,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_4,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_5,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_6,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_7,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_8,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_9,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_10,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_11,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_12,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_13,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_14,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_15,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));
     connect(ui->checkBox_16,SIGNAL(clicked()),this,SLOT(on_checkBox_ChannelSelected_clicked()));

     // 定时1分钟读取数据
     oneMinuteTimer = new QTimer(this);
     connect(oneMinuteTimer,SIGNAL(timeout()),this,SLOT(handlerTimerOut()));
     msgBox = new QMessageBox(QMessageBox::Information, tr("采集分析软件"),"");
     cnt = 20;      //  20s to read the initial H value;
}
Dialog::~Dialog()
{
    delete ui;
}

/*************** 辅助函数 *********************************/
// 辅助函数 -- 设置通道数
void Dialog::help_setChannel(bool a[])
{
    for(int i = 0;i<16;i++){
        isSelected[i] = a[i];
    }
   if(a[0]) ui->checkBox_1->setChecked(true);
   else  ui->checkBox_1->setChecked(false);
   if(a[1]) ui->checkBox_2->setChecked(true);
   else  ui->checkBox_2->setChecked(false);
   if(a[2]) ui->checkBox_3->setChecked(true);
   else  ui->checkBox_3->setChecked(false);
   if(a[3]) ui->checkBox_4->setChecked(true);
   else  ui->checkBox_4->setChecked(false);

   if(a[4]) ui->checkBox_5->setChecked(true);
   else  ui->checkBox_5->setChecked(false);
   if(a[5]) ui->checkBox_6->setChecked(true);
   else  ui->checkBox_6->setChecked(false);
   if(a[6]) ui->checkBox_7->setChecked(true);
   else  ui->checkBox_7->setChecked(false);
   if(a[7]) ui->checkBox_8->setChecked(true);
   else  ui->checkBox_8->setChecked(false);

   if(a[8]) ui->checkBox_9->setChecked(true);
   else  ui->checkBox_9->setChecked(false);
   if(a[9]) ui->checkBox_10->setChecked(true);
   else  ui->checkBox_10->setChecked(false);
   if(a[10]) ui->checkBox_11->setChecked(true);
   else  ui->checkBox_11->setChecked(false);
   if(a[11]) ui->checkBox_12->setChecked(true);
   else  ui->checkBox_12->setChecked(false);

   if(a[12]) ui->checkBox_13->setChecked(true);
   else  ui->checkBox_13->setChecked(false);
   if(a[13]) ui->checkBox_14->setChecked(true);
   else  ui->checkBox_14->setChecked(false);
   if(a[14]) ui->checkBox_15->setChecked(true);
   else  ui->checkBox_15->setChecked(false);
   if(a[15]) ui->checkBox_16->setChecked(true);
   else  ui->checkBox_16->setChecked(false);
}
// 辅助函数 -- 设置测试点名称
void Dialog::help_setTestName(QString s)
{
    QStringList list = s.split(",");

    if(list.at(0) != "-") ui->lineEdit_test1->setText(list.at(0));
    else ui->lineEdit_test1->setText(tr(""));
    if(list.at(1) != "-") ui->lineEdit_test2->setText(list.at(1));
    else ui->lineEdit_test2->setText(tr(""));
    if(list.at(2) != "-") ui->lineEdit_test3->setText(list.at(2));
    else ui->lineEdit_test3->setText(tr(""));
    if(list.at(3) != "-") ui->lineEdit_test4->setText(list.at(3));
    else ui->lineEdit_test4->setText(tr(""));

    if(list.at(4) != "-") ui->lineEdit_test5->setText(list.at(4));
    else ui->lineEdit_test5->setText(tr(""));
    if(list.at(5) != "-") ui->lineEdit_test6->setText(list.at(5));
    else ui->lineEdit_test6->setText(tr(""));
    if(list.at(6) != "-") ui->lineEdit_test7->setText(list.at(6));
    else ui->lineEdit_test7->setText(tr(""));
    if(list.at(7) != "-") ui->lineEdit_test8->setText(list.at(7));
    else ui->lineEdit_test8->setText(tr(""));

    if(list.at(8) != "-") ui->lineEdit_test9->setText(list.at(8));
    else ui->lineEdit_test9->setText(tr(""));
    if(list.at(9) != "-") ui->lineEdit_test10->setText(list.at(9));
    else ui->lineEdit_test10->setText(tr(""));
    if(list.at(10) != "-") ui->lineEdit_test11->setText(list.at(10));
    else ui->lineEdit_test11->setText(tr(""));
    if(list.at(11) != "-") ui->lineEdit_test12->setText(list.at(11));
    else ui->lineEdit_test12->setText(tr(""));

    if(list.at(12) != "-") ui->lineEdit_test13->setText(list.at(12));
    else ui->lineEdit_test13->setText(tr(""));
    if(list.at(13) != "-") ui->lineEdit_test14->setText(list.at(13));
    else ui->lineEdit_test14->setText(tr(""));
    if(list.at(14) != "-") ui->lineEdit_test15->setText(list.at(14));
    else ui->lineEdit_test15->setText(tr(""));
    if(list.at(15) != "-") ui->lineEdit_test16->setText(list.at(15));
    else ui->lineEdit_test16->setText(tr(""));
}
// 辅助函数 -- 设置H初值
void Dialog::help_setH(QString s){
    QStringList list = s.split(",");

    if(list.at(0) != "-") ui->lineEdit_H1->setText(list.at(0));
    else ui->lineEdit_H1->setText(tr(""));
    if(list.at(1) != "-") ui->lineEdit_H2->setText(list.at(1));
    else ui->lineEdit_H2->setText(tr(""));
    if(list.at(2) != "-") ui->lineEdit_H3->setText(list.at(2));
    else ui->lineEdit_H3->setText(tr(""));
    if(list.at(3) != "-") ui->lineEdit_H4->setText(list.at(3));
    else ui->lineEdit_H4->setText(tr(""));

    if(list.at(4) != "-") ui->lineEdit_H5->setText(list.at(4));
    else ui->lineEdit_H5->setText(tr(""));
    if(list.at(5) != "-") ui->lineEdit_H6->setText(list.at(5));
    else ui->lineEdit_H6->setText(tr(""));
    if(list.at(6) != "-") ui->lineEdit_H7->setText(list.at(6));
    else ui->lineEdit_H7->setText(tr(""));
    if(list.at(7) != "-") ui->lineEdit_H8->setText(list.at(7));
    else ui->lineEdit_H8->setText(tr(""));

    if(list.at(8) != "-") ui->lineEdit_H9->setText(list.at(8));
    else ui->lineEdit_H9->setText(tr(""));
    if(list.at(9) != "-") ui->lineEdit_H10->setText(list.at(9));
    else ui->lineEdit_H10->setText(tr(""));
    if(list.at(10) != "-") ui->lineEdit_H11->setText(list.at(10));
    else ui->lineEdit_H11->setText(tr(""));
    if(list.at(11) != "-") ui->lineEdit_H12->setText(list.at(11));
    else ui->lineEdit_H12->setText(tr(""));

    if(list.at(12) != "-") ui->lineEdit_H13->setText(list.at(12));
    else ui->lineEdit_H13->setText(tr(""));
    if(list.at(13) != "-") ui->lineEdit_H14->setText(list.at(13));
    else ui->lineEdit_H14->setText(tr(""));
    if(list.at(14) != "-") ui->lineEdit_H15->setText(list.at(14));
    else ui->lineEdit_H15->setText(tr(""));
    if(list.at(15) != "-") ui->lineEdit_H16->setText(list.at(15));
    else ui->lineEdit_H16->setText(tr(""));
}
// 辅助函数 -- 设置选中的基准点
void Dialog::help_setBase(QString s){
    int index = s.toInt();   // index: 1-16
    last_baseValue = index - 1;

    if(index == 1) ui->checkBox_BaseValue1->setChecked(true);
    else if(index == 2) ui->checkBox_BaseValue2->setChecked(true);
    else if(index == 3) ui->checkBox_BaseValue3->setChecked(true);
    else if(index == 4) ui->checkBox_BaseValue4->setChecked(true);

    else if(index == 5) ui->checkBox_BaseValue5->setChecked(true);
    else if(index == 6) ui->checkBox_BaseValue6->setChecked(true);
    else if(index == 7) ui->checkBox_BaseValue7->setChecked(true);
    else if(index == 8) ui->checkBox_BaseValue8->setChecked(true);

    else if(index == 9) ui->checkBox_BaseValue9->setChecked(true);
    else if(index == 10) ui->checkBox_BaseValue10->setChecked(true);
    else if(index == 11) ui->checkBox_BaseValue11->setChecked(true);
    else if(index == 12) ui->checkBox_BaseValue12->setChecked(true);

    else if(index == 13) ui->checkBox_BaseValue13->setChecked(true);
    else if(index == 14) ui->checkBox_BaseValue14->setChecked(true);
    else if(index == 15) ui->checkBox_BaseValue15->setChecked(true);
    else if(index == 16) ui->checkBox_BaseValue16->setChecked(true);

}
// 辅助函数 -- 保存参数
bool Dialog::help_saveParam(){
    unsigned int tmp = 0;
    QByteArray message;       // 保存待会要下传的数据
    /*************** (1) 读取输入值 **********************************/
    // 1,选中基准点
    if(last_baseValue == -1) {
        QMessageBox::information(this, tr("采集分析软件"), tr("没有选择基准点!\n"));
        return false;
    }
    pMainWindow->baseValue = last_baseValue;

    // 2,读取设置的设备ID
    tmp = ui->lineEdit_DevID->text().toInt();
    if(tmp > 65536)
    {
        ui->label__Message->setText("设备ID必须在0 - 65536之间");
        ui->label__Message->setStyleSheet("color:red;");
        return false;
    }
    this->pDevIDH = (tmp>>8) & 0XFF;
    this->pDevIDL = tmp & 0XFF;
    qDebug()<<"(dialog.cpp)设备ID: "<<tmp<<endl;
    tmp = 0;

    // 3,读取项目名称
    if(this->ui->lineEdit_projectName->text() == ""){
         QMessageBox::information(this, tr("采集分析软件"), tr("项目名称不能为空!\n"));
         return false;
    }
    this->proName = this->ui->lineEdit_projectName->text();

    // 4,读取工程流水号
    if(this->ui->lineEdit_projectID->text() == ""){
         QMessageBox::information(this, tr("采集分析软件"), tr("工程流水号不能为空!\n"));
         return false;
    }
   // this->ProjectID = this->ui->lineEdit_projectID->text();
    this->proId = this->ui->lineEdit_projectID->text();

    // 5,读取服务器地址, 为空默认不设置
    if(this->ui->lineEdit_serverAddr->text() != ""){
        if(pMainWindow->connectType == CONNECT_SERIAL || pMainWindow->connectType == CONNECT_SOCKET){
            QString server = this->ui->lineEdit_serverAddr->text();
            qDebug()<<"(dialog.cpp)"<<QString("SetServer: " + server + "\r\n");
            // QByteArray message;
            message.append(QString("SetServer" + server + "\r\n"));
            // 下发命令SetServer: 设置服务器.
            if(pMainWindow->connectType == CONNECT_SERIAL){
                pMainWindow->uart_thread->my_serialport->write(message);
                pMainWindow->uart_thread->timer->start(TIMEOUTTIME);
            }else if(pMainWindow->connectType == CONNECT_SOCKET){
                pMainWindow->tcpclient_thread->socket->write(message);
                pMainWindow->tcpclient_thread->timer->start(TIMEOUTTIME);
            }
        }
    }

    // 6,读取设置的 采样频率
    this->pFre = ui->comboBox_SampleRte->currentText().toInt();

    // 7,读取设置的 服务器发送间隔
    this->pSendTimeServer = ui->comboBox_SendTime2erver->currentText().toInt();

    // 8,读取设置的 触发态发送间隔
    this->pSendTimeDynamic = ui->comboBox_SendTimeDynamic->currentText().toInt();

    // 9,读取设置的 数据自动保存间隔
    QString tmpPeriod = ui->comboBox_SaveDataDynamic->currentText();
    if(tmpPeriod == "手动保存"){
        pMainWindow->AutoSavePeriod = 0;
        pMainWindow->timer4AutoSaveFile->stop();
    }
    else{
        pMainWindow->AutoSavePeriod = ui->comboBox_SaveDataDynamic->currentText().toInt();
        pMainWindow->timer4AutoSaveFile->start(pMainWindow->AutoSavePeriod*1000);
    }

    // 10,读取设置的 数据保存路径
    if(ui->lineEdit_file4save->text() == ""){
        QMessageBox::information(this, tr("采集分析软件"), tr("数据保存路径不能为空!\n"));
        return false;
    }
    pMainWindow->AutoSaveFile = ui->lineEdit_file4save->text();

    // 11,读取设置的密度
    if(ui->lineEdit_Density->text() == ""){
        QMessageBox::information(this, tr("采集分析软件"), tr("密度设置不能为空!\n"));
        return false;
    }
    pMainWindow->Density = ui->lineEdit_Density->text().toDouble();

    // 12,读取设置的标定系数
    if(ui->lineEdit_biaoding->text() == ""){
        QMessageBox::information(this, tr("采集分析软件"), tr("标定系数设置不能为空!\n"));
        return false;
    }
    pMainWindow->e = ui->lineEdit_biaoding->text().toDouble();

    // 13,读取设置的Pmax,Pmin
    if(isSelected[0]){
        if(this->ui->Pmax_1->text() == "" || this->ui->Pmin_1->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第一个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[0] = ui->Pmax_1->text().toDouble();
        pMainWindow->PminList[0] = ui->Pmin_1->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[0] = 0;
        pMainWindow->PminList[0] = 0;
    }
    if(isSelected[1]){
        if(this->ui->Pmax_2->text() == "" || this->ui->Pmin_2->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第2个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[1] = ui->Pmax_2->text().toDouble();
        pMainWindow->PminList[1] = ui->Pmin_2->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[1] = 0;
        pMainWindow->PminList[1] = 0;
    }
    if(isSelected[2]){
        if(this->ui->Pmax_3->text() == "" || this->ui->Pmin_3->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第3个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[2] = ui->Pmax_3->text().toDouble();
        pMainWindow->PminList[2] = ui->Pmin_3->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[2] = 0;
        pMainWindow->PminList[2] = 0;
    }
    if(isSelected[3]){
        if(this->ui->Pmax_4->text() == "" || this->ui->Pmin_4->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第4个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[3] = ui->Pmax_4->text().toDouble();
        pMainWindow->PminList[3] = ui->Pmin_4->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[3] = 0;
        pMainWindow->PminList[3] = 0;
    }

    if(isSelected[4]){
        if(this->ui->Pmax_5->text() == "" || this->ui->Pmin_5->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第5个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[4] = ui->Pmax_5->text().toDouble();
        pMainWindow->PminList[4] = ui->Pmin_5->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[4] = 0;
        pMainWindow->PminList[4] = 0;
    }
    if(isSelected[5]){
        if(this->ui->Pmax_6->text() == "" || this->ui->Pmin_6->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第6个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[5] = ui->Pmax_6->text().toDouble();
        pMainWindow->PminList[5] = ui->Pmin_6->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[5] = 0;
        pMainWindow->PminList[5] = 0;
    }
    if(isSelected[6]){
        if(this->ui->Pmax_7->text() == "" || this->ui->Pmin_7->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第7个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[6] = ui->Pmax_7->text().toDouble();
        pMainWindow->PminList[6] = ui->Pmin_7->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[6] = 0;
        pMainWindow->PminList[6] = 0;
    }
    if(isSelected[7]){
        if(this->ui->Pmax_8->text() == "" || this->ui->Pmin_8->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第8个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[7] = ui->Pmax_8->text().toDouble();
        pMainWindow->PminList[7] = ui->Pmin_8->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[7] = 0;
        pMainWindow->PminList[7] = 0;
    }

    if(isSelected[8]){
        if(this->ui->Pmax_9->text() == "" || this->ui->Pmin_9->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第9个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[8] = ui->Pmax_9->text().toDouble();
        pMainWindow->PminList[8] = ui->Pmin_9->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[8] = 0;
        pMainWindow->PminList[8] = 0;
    }
    if(isSelected[9]){
        if(this->ui->Pmax_10->text() == "" || this->ui->Pmin_10->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第10个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[9] = ui->Pmax_10->text().toDouble();
        pMainWindow->PminList[9] = ui->Pmin_10->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[9] = 0;
        pMainWindow->PminList[9] = 0;
    }
    if(isSelected[10]){
        if(this->ui->Pmax_11->text() == "" || this->ui->Pmin_11->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第11个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[10] = ui->Pmax_11->text().toDouble();
        pMainWindow->PminList[10] = ui->Pmin_11->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[10] = 0;
        pMainWindow->PminList[10] = 0;
    }
    if(isSelected[11]){
        if(this->ui->Pmax_12->text() == "" || this->ui->Pmin_12->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第12个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[11] = ui->Pmax_12->text().toDouble();
        pMainWindow->PminList[11] = ui->Pmin_12->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[11] = 0;
        pMainWindow->PminList[11] = 0;
    }

    if(isSelected[12]){
        if(this->ui->Pmax_13->text() == "" || this->ui->Pmin_13->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第13个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[12] = ui->Pmax_13->text().toDouble();
        pMainWindow->PminList[12] = ui->Pmin_13->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[12] = 0;
        pMainWindow->PminList[12] = 0;
    }
    if(isSelected[13]){
        if(this->ui->Pmax_14->text() == "" || this->ui->Pmin_14->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第14个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[13] = ui->Pmax_14->text().toDouble();
        pMainWindow->PminList[13] = ui->Pmin_14->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[13] = 0;
        pMainWindow->PminList[13] = 0;
    }
    if(isSelected[14]){
        if(this->ui->Pmax_15->text() == "" || this->ui->Pmin_15->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第15个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[14] = ui->Pmax_15->text().toDouble();
        pMainWindow->PminList[14] = ui->Pmin_15->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[14] = 0;
        pMainWindow->PminList[14] = 0;
    }
    if(isSelected[15]){
        if(this->ui->Pmax_16->text() == "" || this->ui->Pmin_16->text() == ""){
            QMessageBox::information(this, tr("采集分析软件"), tr("请输入第16个通道的压强!\n"));
            return false;
        }
        pMainWindow->PmaxList[15] = ui->Pmax_16->text().toDouble();
        pMainWindow->PminList[15] = ui->Pmin_16->text().toDouble();
    }
    else{
        pMainWindow->PmaxList[15] = 0;
        pMainWindow->PminList[15] = 0;
    }

    // 14,保存设置的通道数,H初值
    if(!isSelected[0] && !isSelected[1] && !isSelected[2] && !isSelected[3]
       && !isSelected[4] && !isSelected[5] && !isSelected[6] && !isSelected[7]
       && !isSelected[8] && !isSelected[9] && !isSelected[10] && !isSelected[11]
       && !isSelected[12] && !isSelected[13] && !isSelected[14] && !isSelected[15])
    {
        QMessageBox::information(this,tr("采集仪分析软件"),tr("请勾选要保存的通道"));
        return false;
    }

    if(isSelected[0]) pMainWindow->H[0] = (ui->lineEdit_H1->text().toDouble());
    else pMainWindow->H[0] = 0;
    if(isSelected[1]) pMainWindow->H[1] = ( ui->lineEdit_H2->text().toDouble());
    else pMainWindow->H[1] = 0;
    if(isSelected[2]) pMainWindow->H[2] = (ui->lineEdit_H3->text().toDouble());
    else pMainWindow->H[2] = 0;
    if(isSelected[3]) pMainWindow->H[3] = ( ui->lineEdit_H4->text().toDouble());
    else pMainWindow->H[3] = 0;
    if(isSelected[4]) pMainWindow->H[4] = ( ui->lineEdit_H5->text().toDouble());
    else pMainWindow->H[4] = 0;
    if(isSelected[5]) pMainWindow->H[5] = ( ui->lineEdit_H6->text().toDouble());
    else pMainWindow->H[5] = 0;
    if(isSelected[6]) pMainWindow->H[6] = ( ui->lineEdit_H7->text().toDouble());
    else pMainWindow->H[6] = 0;
    if(isSelected[7]) pMainWindow->H[7] = ( ui->lineEdit_H8->text().toDouble());
    else pMainWindow->H[7] = 0;
    if(isSelected[8]) pMainWindow->H[8] = ( ui->lineEdit_H9->text().toDouble());
    else pMainWindow->H[8] = 0;
    if(isSelected[9]) pMainWindow->H[9] = ( ui->lineEdit_H10->text().toDouble());
    else pMainWindow->H[9] = 0;
    if(isSelected[10]) pMainWindow->H[10] = ( ui->lineEdit_H11->text().toDouble());
    else pMainWindow->H[10] = 0;
    if(isSelected[11]) pMainWindow->H[11] = ( ui->lineEdit_H12->text().toDouble());
    else pMainWindow->H[11] = 0;
    if(isSelected[12]) pMainWindow->H[12] = ( ui->lineEdit_H13->text().toDouble());
    else pMainWindow->H[12] = 0;
    if(isSelected[13]) pMainWindow->H[13] = ( ui->lineEdit_H14->text().toDouble());
    else pMainWindow->H[13] = 0;
    if(isSelected[14]) pMainWindow->H[14] = ( ui->lineEdit_H15->text().toDouble());
    else pMainWindow->H[14] = 0;
    if(isSelected[15]) pMainWindow->H[15] = ( ui->lineEdit_H16->text().toDouble());
    else pMainWindow->H[15] = 0;

    // 15,读取设置的测试点名称  --> (未勾选的不保存)
    QString slist[16] ;
    if(isSelected[0]) slist[0] = ui->lineEdit_test1->text();
    else slist[0] = "";
    if(isSelected[1]) slist[1] = ui->lineEdit_test2->text();
    else slist[1] = "";
    if(isSelected[2]) slist[2] = ui->lineEdit_test3->text();
    else slist[2] = "";
    if(isSelected[3]) slist[3] = ui->lineEdit_test4->text();
    else slist[3] = "";
    if(isSelected[4]) slist[4] = ui->lineEdit_test5->text();
    else slist[4] = "";
    if(isSelected[5]) slist[5] = ui->lineEdit_test6->text();
    else slist[5] = "";
    if(isSelected[6]) slist[6] = ui->lineEdit_test7->text();
    else slist[6] = "";
    if(isSelected[7]) slist[7] = ui->lineEdit_test8->text();
    else slist[7] = "";
    if(isSelected[8]) slist[8] = ui->lineEdit_test9->text();
    else slist[8] = "";
    if(isSelected[9]) slist[9] = ui->lineEdit_test10->text();
    else slist[9] = "";
    if(isSelected[10]) slist[10] = ui->lineEdit_test11->text();
    else slist[10] = "";
    if(isSelected[11]) slist[11] = ui->lineEdit_test12->text();
    else slist[11] = "";
    if(isSelected[12]) slist[12] = ui->lineEdit_test13->text();
    else slist[12] = "";
    if(isSelected[13]) slist[13] = ui->lineEdit_test14->text();
    else slist[13] = "";
    if(isSelected[14]) slist[14] = ui->lineEdit_test15->text();
    else slist[14] = "";
    if(isSelected[15]) slist[15] = ui->lineEdit_test16->text();
    else slist[15] = "";

    // 16,读取设置的采样类型
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
    this->pCtrlH = (tmp>>8) & 0XFF;
    this->pCtrlL = tmp & 0XFF;

    /************* (2) 下传设置的命令字 ****************************/

    message.append(QString("SetParam"));
    message.append(pDevIDH);
    message.append(pDevIDL);                 // 1,设备号
    message.append(pCtrlH);
    message.append(pCtrlL);                  // 2,采样类型
    message.append(pFre);                    // 3,采样频率
    message.append(pSendTimeServer);         // 4,服务器发送间隔
    message.append(pSendTimeDynamic);        // 5,触发态保存间隔

    int len = proId.toUtf8().length();
    unsigned char fillCode = 0x00;   // 填充码
    message.append(proId);                   // 6,工程流水号
    for(int i = len;i<48;i++){
        message.append(fillCode);
    }

    len = proName.toUtf8().length();
    message.append(proName);                 // 7,项目名称
    for(int i = len;i<48;i++){
        message.append(fillCode);
    }

    for(int j = 0;j<16;j++){                 // 8,测试点的名称
        len = slist[j].toUtf8().length();
        message.append(slist[j]);
        for(int i = len;i<24;i++){
            message.append(fillCode);
        }
    }

    message.append(QString("\r\n"));
    qDebug()<<"(dialog.cpp 759) 保存设置参数"<<endl;
    pMainWindow->tcpclient_thread->socket->write(message);
    pMainWindow->samplerateTmp = pFre;
    pMainWindow->tcpclient_thread->timer->start(TIMEOUTTIME);

    /************* (3) 保存用户设置于setting.csv文件中 ***********************/
    QFile mfile("./Setting.csv");
    if(!mfile.isOpen()) mfile.open( QIODevice::ReadWrite | QIODevice::Truncate |QIODevice::Text);
    QTextStream steam(&mfile);
    int devid = 0;
    devid = pDevIDH;
    devid <<= 8;
    devid += pDevIDL;
    steam<<devid<<endl;                      // 1,写入设备ID   (用于区分不同设备)
    steam<<tmpPeriod<<endl;                  // 2,写入自动保存间隔 或 手动保存
    steam<<pMainWindow->AutoSaveFile<<endl;  // 3,写入自动保存路径
    steam<<pMainWindow->Density<<endl;       // 4,写入密度
    steam<<pMainWindow->e<<endl;             // 5,写入标定系数e
    for(int i = 0;i < 16; i++){              // 6,写入Pmax
        if(isSelected[i])
            steam<<pMainWindow->PmaxList[i]<<",";
        else
            steam<<"-,";
    }
    steam<<endl;
    for(int i = 0;i < 16; i++){              // 7,写入Pmin
        if(isSelected[i])
            steam<<pMainWindow->PminList[i]<<",";
        else
            steam<<"-,";
    }
    steam<<endl;
    for(int i = 0; i < 16; i++){             // 8,写入选中的通道数
        if(isSelected[i])
            steam<<"1,";
        else
            steam<<"0,";
    }
    steam<<endl;
    for(int i = 0; i < 16; i++){             // 9,写入H初值
        if(isSelected[i])
            steam<<pMainWindow->H[i]<<",";
        else
            steam<<"-,";
    }
    steam<<endl;
    steam<<last_baseValue+1<<endl;            // 10,写入基准点选择
    pMainWindow->readInitialValue = true;
    cnt = 20;
    return true;
}
// 辅助函数 -- 设置压强
void Dialog::help_setP(QString s, bool isMax){
}/*{
    QStringList list = s.split(",");
    if(!isMax){
        if(list.at(0) != "-" ){
            if(list.at(0).toDouble() == -1000) ui->Pbtn_11->setChecked(true);
            else if(list.at(0).toDouble() == -5000) ui->Pbtn_12->setChecked(true);
            else if(list.at(0).toDouble() == -10000) ui->Pbtn_13->setChecked(true);
            pMainWindow->PminList[0] = list.at(0).toDouble();
            pMainWindow->PmaxList[0] = - pMainWindow->PminList[0] ;

            ui->Pmin_1->setText(list.at(0));
        }
        else ui->Pmin_1->setText(tr(""));
        if(list.at(1) != "-" ){
            if(list.at(1).toDouble() == -1000) ui->Pbtn_21->setChecked(true);
            else if(list.at(1).toDouble() == -5000) ui->Pbtn_22->setChecked(true);
            else if(list.at(1).toDouble() == -10000) ui->Pbtn_23->setChecked(true);
            pMainWindow->PminList[1] = list.at(1).toDouble();
            pMainWindow->PmaxList[1] = - pMainWindow->PminList[1] ;

            ui->Pmin_2->setText(list.at(1));
        }
        else ui->Pmin_2->setText(tr(""));
        if(list.at(2) != "-" ){
            if(list.at(2).toDouble() == -1000) ui->Pbtn_31->setChecked(true);
            else if(list.at(2).toDouble() == -5000) ui->Pbtn_32->setChecked(true);
            else if(list.at(2).toDouble() == -10000) ui->Pbtn_33->setChecked(true);
            pMainWindow->PminList[2] = list.at(2).toDouble();
            pMainWindow->PmaxList[2] = - pMainWindow->PminList[2] ;

            ui->Pmin_3->setText(list.at(2));
        }
        else ui->Pmin_3->setText(tr(""));
        if(list.at(3) != "-" ){
            if(list.at(3).toDouble() == -1000) ui->Pbtn_41->setChecked(true);
            else if(list.at(3).toDouble() == -5000) ui->Pbtn_42->setChecked(true);
            else if(list.at(3).toDouble() == -10000) ui->Pbtn_43->setChecked(true);
            pMainWindow->PminList[3] = list.at(3).toDouble();
            pMainWindow->PmaxList[3] = - pMainWindow->PminList[3] ;

            ui->Pmin_4->setText(list.at(3));
        }
        else ui->Pmin_4->setText(tr(""));

        if(list.at(4) != "-" ) {
            if(list.at(4).toDouble() == -1000) ui->Pbtn_51->setChecked(true);
            else if(list.at(4).toDouble() == -5000) ui->Pbtn_52->setChecked(true);
            else if(list.at(4).toDouble() == -10000) ui->Pbtn_53->setChecked(true);
            pMainWindow->PminList[4] = list.at(4).toDouble();
            pMainWindow->PmaxList[4] = - pMainWindow->PminList[4] ;

            ui->Pmin_5->setText(list.at(4));
        }
        else ui->Pmin_5->setText(tr(""));
        if(list.at(5) != "-" ){
            if(list.at(5).toDouble() == -1000) ui->Pbtn_61->setChecked(true);
            else if(list.at(5).toDouble() == -5000) ui->Pbtn_62->setChecked(true);
            else if(list.at(5).toDouble() == -10000) ui->Pbtn_63->setChecked(true);
            pMainWindow->PminList[5] = list.at(5).toDouble();
            pMainWindow->PmaxList[5] = - pMainWindow->PminList[5] ;

            ui->Pmin_6->setText(list.at(5));
        }
        else ui->Pmin_6->setText(tr(""));
        if(list.at(6) != "-" ) {
            if(list.at(6).toDouble() == -1000) ui->Pbtn_71->setChecked(true);
            else if(list.at(6).toDouble() == -5000) ui->Pbtn_72->setChecked(true);
            else if(list.at(6).toDouble() == -10000) ui->Pbtn_73->setChecked(true);
            pMainWindow->PminList[6] = list.at(6).toDouble();
            pMainWindow->PmaxList[6] = - pMainWindow->PminList[6] ;

            ui->Pmin_7->setText(list.at(6));
        }
        else ui->Pmin_7->setText(tr(""));
        if(list.at(7) != "-" ) {
            if(list.at(7).toDouble() == -1000) ui->Pbtn_81->setChecked(true);
            else if(list.at(7).toDouble() == -5000) ui->Pbtn_82->setChecked(true);
            else if(list.at(7).toDouble() == -10000) ui->Pbtn_83->setChecked(true);
            pMainWindow->PminList[7] = list.at(7).toDouble();
            pMainWindow->PmaxList[7] = - pMainWindow->PminList[7] ;

            ui->Pmin_8->setText(list.at(7));
        }
        else ui->Pmin_8->setText(tr(""));

        if(list.at(8) != "-" ){
            if(list.at(8).toDouble() == -1000) ui->Pbtn_91->setChecked(true);
            else if(list.at(8).toDouble() == -5000) ui->Pbtn_92->setChecked(true);
            else if(list.at(8).toDouble() == -10000) ui->Pbtn_93->setChecked(true);
            pMainWindow->PminList[8] = list.at(8).toDouble();
            pMainWindow->PmaxList[8] = - pMainWindow->PminList[8] ;

            ui->Pmin_9->setText(list.at(8));
        }
        else ui->Pmin_9->setText(tr(""));
        if(list.at(9) != "-" ) {
            if(list.at(9).toDouble() == -1000) ui->Pbtn_a1->setChecked(true);
            else if(list.at(9).toDouble() == -5000) ui->Pbtn_a2->setChecked(true);
            else if(list.at(9).toDouble() == -10000) ui->Pbtn_a3->setChecked(true);
            pMainWindow->PminList[9] = list.at(9).toDouble();
            pMainWindow->PmaxList[9] = - pMainWindow->PminList[9] ;

            ui->Pmin_10->setText(list.at(9));
        }
        else ui->Pmin_10->setText(tr(""));
        if(list.at(10) != "-" ) {
            if(list.at(10).toDouble() == -1000) ui->Pbtn_b1->setChecked(true);
            else if(list.at(10).toDouble() == -5000) ui->Pbtn_b2->setChecked(true);
            else if(list.at(10).toDouble() == -10000) ui->Pbtn_b3->setChecked(true);
            pMainWindow->PminList[10] = list.at(10).toDouble();
            pMainWindow->PmaxList[10] = - pMainWindow->PminList[10] ;

            ui->Pmin_11->setText(list.at(10));
        }
        else ui->Pmin_11->setText(tr(""));
        if(list.at(11) != "-" ) {
            if(list.at(11).toDouble() == -1000) ui->Pbtn_c1->setChecked(true);
            else if(list.at(11).toDouble() == -5000) ui->Pbtn_c2->setChecked(true);
            else if(list.at(11).toDouble() == -10000) ui->Pbtn_c3->setChecked(true);
            pMainWindow->PminList[11] = list.at(11).toDouble();
            pMainWindow->PmaxList[11] = - pMainWindow->PminList[11] ;

            ui->Pmin_12->setText(list.at(11));
        }
        else ui->Pmin_12->setText(tr(""));

        if(list.at(12) != "-" ) {
            if(list.at(12).toDouble() == -1000) ui->Pbtn_d1->setChecked(true);
            else if(list.at(12).toDouble() == -5000) ui->Pbtn_d2->setChecked(true);
            else if(list.at(12).toDouble() == -10000) ui->Pbtn_d3->setChecked(true);
            pMainWindow->PminList[12] = list.at(12).toDouble();
            pMainWindow->PmaxList[12] = - pMainWindow->PminList[12] ;

            ui->Pmin_13->setText(list.at(12));
        }
        else ui->Pmin_13->setText(tr(""));
        if(list.at(13) != "-" ){
            if(list.at(13).toDouble() == -1000) ui->Pbtn_e1->setChecked(true);
            else if(list.at(13).toDouble() == -5000) ui->Pbtn_e2->setChecked(true);
            else if(list.at(13).toDouble() == -10000) ui->Pbtn_e3->setChecked(true);
            pMainWindow->PminList[13] = list.at(13).toDouble();
            pMainWindow->PmaxList[13] = - pMainWindow->PminList[13] ;

            ui->Pmin_14->setText(list.at(13));
        }
        else ui->Pmin_14->setText(tr(""));
        if(list.at(14) != "-" ) {
            if(list.at(14).toDouble() == -1000) ui->Pbtn_f1->setChecked(true);
            else if(list.at(14).toDouble() == -5000) ui->Pbtn_f2->setChecked(true);
            else if(list.at(14).toDouble() == -10000) ui->Pbtn_f3->setChecked(true);
            pMainWindow->PminList[14] = list.at(14).toDouble();
            pMainWindow->PmaxList[14] = - pMainWindow->PminList[14] ;

            ui->Pmin_15->setText(list.at(14));
        }
        else ui->Pmin_15->setText(tr(""));
        if(list.at(15) != "-" ) {
            if(list.at(15).toDouble() == -1000) ui->Pbtn_g1->setChecked(true);
            else if(list.at(15).toDouble() == -5000) ui->Pbtn_g2->setChecked(true);
            else if(list.at(15).toDouble() == -10000) ui->Pbtn_g3->setChecked(true);
            pMainWindow->PminList[15] = list.at(15).toDouble();
            pMainWindow->PmaxList[15] = - pMainWindow->PminList[15] ;

            ui->Pmin_16->setText(list.at(15));
        }
        else ui->Pmin_16->setText(tr(""));

    }else{
        if(list.at(0) != "-" ) ui->Pmax_1->setText(list.at(0));
        else ui->Pmax_1->setText(tr(""));
        if(list.at(1) != "-" ) ui->Pmax_2->setText(list.at(1));
        else ui->Pmax_2->setText(tr(""));
        if(list.at(2) != "-" ) ui->Pmax_3->setText(list.at(2));
        else ui->Pmax_3->setText(tr(""));
        if(list.at(3) != "-" ) ui->Pmax_4->setText(list.at(3));
        else ui->Pmax_4->setText(tr(""));

        if(list.at(4) != "-" ) ui->Pmax_5->setText(list.at(4));
        else ui->Pmax_5->setText(tr(""));
        if(list.at(5) != "-" ) ui->Pmax_6->setText(list.at(5));
        else ui->Pmax_6->setText(tr(""));
        if(list.at(6) != "-" ) ui->Pmax_7->setText(list.at(6));
        else ui->Pmax_7->setText(tr(""));
        if(list.at(7) != "-" ) ui->Pmax_8->setText(list.at(7));
        else ui->Pmax_8->setText(tr(""));

        if(list.at(8) != "-" ) ui->Pmax_9->setText(list.at(8));
        else ui->Pmax_9->setText(tr(""));
        if(list.at(9) != "-" ) ui->Pmax_10->setText(list.at(9));
        else ui->Pmax_10->setText(tr(""));
        if(list.at(10) != "-" ) ui->Pmax_11->setText(list.at(10));
        else ui->Pmax_11->setText(tr(""));
        if(list.at(11) != "-") ui->Pmax_12->setText(list.at(11));
        else ui->Pmax_12->setText(tr(""));

        if(list.at(12) != "-" ) ui->Pmax_13->setText(list.at(12));
        else ui->Pmax_13->setText(tr(""));
        if(list.at(13) != "-" ) ui->Pmax_14->setText(list.at(13));
        else ui->Pmax_14->setText(tr(""));
        if(list.at(14) != "-" ) ui->Pmax_15->setText(list.at(14));
        else ui->Pmax_15->setText(tr(""));
        if(list.at(15) != "-") ui->Pmax_16->setText(list.at(15));
        else ui->Pmax_16->setText(tr(""));
    }
}*/
// 辅助函数 -- 读取压强
void Dialog::help_readP(){
    // 读取压强
    if(isSelected[0]){
        pMainWindow->PmaxList[0] = ui->Pmax_1->text().toDouble();
        pMainWindow->PminList[0] = ui->Pmin_1->text().toDouble();
    }
    if(isSelected[1]){
        pMainWindow->PmaxList[1] = ui->Pmax_2->text().toDouble();
        pMainWindow->PminList[1] = ui->Pmin_2->text().toDouble();
    }
    if(isSelected[2]){
        pMainWindow->PmaxList[2] = ui->Pmax_3->text().toDouble();
        pMainWindow->PminList[2] = ui->Pmin_3->text().toDouble();
    }
    if(isSelected[3]){
        pMainWindow->PmaxList[3] = ui->Pmax_4->text().toDouble();
        pMainWindow->PminList[3] = ui->Pmin_4->text().toDouble();
    }

    if(isSelected[4]){
        pMainWindow->PmaxList[4] = ui->Pmax_5->text().toDouble();
        pMainWindow->PminList[4] = ui->Pmin_5->text().toDouble();
    }
    if(isSelected[5]){
        pMainWindow->PmaxList[5] = ui->Pmax_6->text().toDouble();
        pMainWindow->PminList[5] = ui->Pmin_6->text().toDouble();
    }
    if(isSelected[6]){
        pMainWindow->PmaxList[6] = ui->Pmax_7->text().toDouble();
        pMainWindow->PminList[6] = ui->Pmin_7->text().toDouble();
    }
    if(isSelected[7]){
        pMainWindow->PmaxList[7] = ui->Pmax_8->text().toDouble();
        pMainWindow->PminList[7] = ui->Pmin_8->text().toDouble();
    }

    if(isSelected[8]){
        pMainWindow->PmaxList[8] = ui->Pmax_9->text().toDouble();
        pMainWindow->PminList[8] = ui->Pmin_9->text().toDouble();
    }
    if(isSelected[9]){
        pMainWindow->PmaxList[9] = ui->Pmax_10->text().toDouble();
        pMainWindow->PminList[9] = ui->Pmin_10->text().toDouble();
    }
    if(isSelected[10]){
        pMainWindow->PmaxList[10] = ui->Pmax_11->text().toDouble();
        pMainWindow->PminList[10] = ui->Pmin_11->text().toDouble();
    }
    if(isSelected[11]){
        pMainWindow->PmaxList[11] = ui->Pmax_12->text().toDouble();
        pMainWindow->PminList[11] = ui->Pmin_12->text().toDouble();
    }

    if(isSelected[12]){
        pMainWindow->PmaxList[12] = ui->Pmax_13->text().toDouble();
        pMainWindow->PminList[12] = ui->Pmin_13->text().toDouble();
    }
    if(isSelected[13]){
        pMainWindow->PmaxList[13] = ui->Pmax_14->text().toDouble();
        pMainWindow->PminList[13] = ui->Pmin_14->text().toDouble();
    }
    if(isSelected[14]){
        pMainWindow->PmaxList[14] = ui->Pmax_15->text().toDouble();
        pMainWindow->PminList[14] = ui->Pmin_15->text().toDouble();
    }
    if(isSelected[15]){
        pMainWindow->PmaxList[15] = ui->Pmax_16->text().toDouble();
        pMainWindow->PminList[15] = ui->Pmin_16->text().toDouble();
    }

}

/************** 按钮响应函数 ********************************/
// "ok"         按钮: 保存参数到setting.csv, 下发设置到设备, 退出
void Dialog::accept()
{
    if(help_saveParam()) {
        pMainWindow->readInitialValue = false;
        Dialog::done(0);
    }
    else return;
}
// "cancel"     按钮:
void Dialog::reject()
{
    Dialog::done(-1);
}
// "浏览"        按钮: 选择文件自动保存路径
void Dialog::on_pushButton_selectFile_clicked()
{
   QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
   QString fileName =  QFileDialog::getExistingDirectory(this,tr("保存目录"),
                                           this->ui->lineEdit_file4save->text(),
                                           options);
   if(!fileName.isEmpty()){
       this->ui->lineEdit_file4save->setText(fileName);
   }
}
// "恢复出厂设置" 按钮: 下发“恢复出厂设置”命令字
void Dialog::on_pushButton_Reset_2_clicked()
{
    if(pMainWindow->connectType == CONNECT_SERIAL || pMainWindow->connectType == CONNECT_SOCKET){
        bool isOK;
        QStringList list;
        list<<tr("恢复出厂设置")<<tr("点错了");
        QString select=QInputDialog::getItem(this,tr("采集分析软件"),tr("点击确定"),list,0,false,&isOK);
        if(select == "恢复出厂设置" && isOK){
            if(pMainWindow->connectType == CONNECT_SERIAL){
                // 下发命名字ResetOption:恢复出厂设置
                pMainWindow->uart_thread->my_serialport->write("ResetOption\r\n");
                pMainWindow->uart_thread->timer->start(TIMEOUTTIME);
            }else if(pMainWindow->connectType == CONNECT_SOCKET){
                pMainWindow->tcpclient_thread->socket->write("ResetOption\r\n");
                pMainWindow->tcpclient_thread->timer->start(TIMEOUTTIME);
            }
        }
    }
}
// "读取初值"    按钮: 打开计时器,下发“发送数据”命令字
void Dialog::on_pushButton_readH0_clicked()
{
   if(!isSelected[0] && !isSelected[1] && !isSelected[2] && !isSelected[3]
      && !isSelected[4] && !isSelected[5] && !isSelected[6] && !isSelected[7]
      && !isSelected[8] && !isSelected[9] && !isSelected[10] && !isSelected[11]
      && !isSelected[12] && !isSelected[13] && !isSelected[14] && !isSelected[15])
   {
       QMessageBox::information(this,tr("采集仪分析软件"),tr("请选择通道数"));
       return;
   }
   if(cnt>0){

      // 读取最新设置的参数值:密度,Pmax,Pmin,标记系数
      pMainWindow->e = ui->lineEdit_biaoding->text().toDouble();
      pMainWindow->Density = ui->lineEdit_Density->text().toDouble();
      // 读取压强
      help_readP();
      // 读取h初值
      pMainWindow->readInitialValue = true;


      QString str = "请等待" + QString::number(cnt) + "秒采集数据";
      msgBox->setInformativeText(str);
      if(!oneMinuteTimer->isActive()) oneMinuteTimer->start(1000);
      msgBox->setModal(true);
      msgBox->exec();
   }
}
void Dialog::handlerTimerOut(){         // 定时器处理函数
     if(cnt > 0){
          // (1)发送命令字
          if(cnt == 20 && pMainWindow->connectType == CONNECT_SOCKET) {
               // 读取密度
               pMainWindow->Density = ui->lineEdit_Density->text().toDouble();
               // 读取标定系数
               pMainWindow->e = ui->lineEdit_biaoding->text().toDouble();
               // 读取压强
               help_readP();

               pMainWindow->tcpclient_thread->socket->write("StartToSend\r\n");
               qDebug()<<"(dialog.cpp)send to device: StartToSend\r\n"<<endl;
               pMainWindow->isStartCollect = true;
          }
          // (2) 等待
          cnt--;
          QString str = "请等待" + QString::number(cnt) + "秒采集数据";
          qDebug()<<"(dialog.cpp)"<<str<<endl;
          msgBox->setInformativeText(str);
     }
     else{
         msgBox->close();
         oneMinuteTimer->stop();
         pMainWindow->tcpclient_thread->socket->write("StopToSend\r\n");
         qDebug()<<"(dialog.cpp)send to device: StopToSend\r\n"<<endl;
         pMainWindow->isStartCollect = false;
         pMainWindow->readInitialValue = false;
         pMainWindow->timeCount = 0;

         // 显示读取到的H初始值;
         cnt = 20;
         if(pMainWindow->isChannal[0]) {
             this->ui->lineEdit_H1->setText(QString::number(pMainWindow->H[0]));
             int tmp = pMainWindow->H[0];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H1->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H1->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H1->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H1->setText(tr(""));
         if(pMainWindow->isChannal[1]) {
             this->ui->lineEdit_H2->setText(QString::number(pMainWindow->H[1]));
             int tmp = pMainWindow->H[1];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H2->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H2->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H2->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H2->setText(tr(""));
         if(pMainWindow->isChannal[2]) {
             this->ui->lineEdit_H3->setText(QString::number(pMainWindow->H[2]));
             int tmp = pMainWindow->H[2];
             if(tmp < 0) tmp = -tmp;

             if(tmp > this->redLine) this->ui->lineEdit_H3->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H3->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H3->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H3->setText(tr(""));
         if(pMainWindow->isChannal[3]) {
             this->ui->lineEdit_H4->setText(QString::number(pMainWindow->H[3]));
             int tmp = pMainWindow->H[3];
             if(tmp < 0) tmp = -tmp;

             if(tmp > this->redLine) this->ui->lineEdit_H4->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H4->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H4->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H4->setText(tr(""));
         if(pMainWindow->isChannal[4]) {
             this->ui->lineEdit_H5->setText(QString::number(pMainWindow->H[4]));
             int tmp = pMainWindow->H[4];
             if(tmp < 0) tmp = -tmp;

             if(tmp > this->redLine) this->ui->lineEdit_H5->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H5->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H5->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H5->setText(tr(""));
         if(pMainWindow->isChannal[5]){
             this->ui->lineEdit_H6->setText(QString::number(pMainWindow->H[5]));
             int tmp = pMainWindow->H[5];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H6->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H6->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H6->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H6->setText(tr(""));
         if(pMainWindow->isChannal[6]){
             this->ui->lineEdit_H7->setText(QString::number(pMainWindow->H[6]));
             int tmp = pMainWindow->H[6];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H7->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H7->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H7->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H7->setText(tr(""));
         if(pMainWindow->isChannal[7]){
             this->ui->lineEdit_H8->setText(QString::number(pMainWindow->H[7]));
             int tmp = pMainWindow->H[7];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H8->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H8->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H8->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H8->setText(tr(""));

         if(pMainWindow->isChannal[8]) {
             this->ui->lineEdit_H9->setText(QString::number(pMainWindow->H[8]));
             int tmp = pMainWindow->H[8];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H9->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H9->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H9->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H9->setText(tr(""));
         if(pMainWindow->isChannal[9]){
             this->ui->lineEdit_H10->setText(QString::number(pMainWindow->H[9]));
             int tmp = pMainWindow->H[9];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H10->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H10->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H10->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H10->setText(tr(""));
         if(pMainWindow->isChannal[10]){
             this->ui->lineEdit_H11->setText(QString::number(pMainWindow->H[10]));
             int tmp = pMainWindow->H[10];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H11->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H11->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H11->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H11->setText(tr(""));
         if(pMainWindow->isChannal[11]) {
             this->ui->lineEdit_H12->setText(QString::number(pMainWindow->H[11]));
             int tmp = pMainWindow->H[11];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H12->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H12->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H12->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H12->setText(tr(""));
         if(pMainWindow->isChannal[12]) {
             this->ui->lineEdit_H13->setText(QString::number(pMainWindow->H[12]));
             int tmp = pMainWindow->H[12];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H13->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H13->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H13->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H13->setText(tr(""));
         if(pMainWindow->isChannal[13]) {
             this->ui->lineEdit_H14->setText(QString::number(pMainWindow->H[13]));
             int tmp = pMainWindow->H[13];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H14->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H14->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H14->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H14->setText(tr(""));
         if(pMainWindow->isChannal[14]) {
             this->ui->lineEdit_H15->setText(QString::number(pMainWindow->H[14]));
             int tmp = pMainWindow->H[14];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H15->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H15->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H15->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H15->setText(tr(""));
         if(pMainWindow->isChannal[15]) {
             this->ui->lineEdit_H16->setText(QString::number(pMainWindow->H[15]));
             int tmp = pMainWindow->H[15];
             if(tmp < 0) tmp = -tmp;
             if(tmp > this->redLine) this->ui->lineEdit_H16->setStyleSheet("color:red;");
             else if(tmp > this->orangeLine) this->ui->lineEdit_H16->setStyleSheet("color:orange;");
             else this->ui->lineEdit_H16->setStyleSheet("color:black;");
         }
         else  this->ui->lineEdit_H16->setText(tr(""));
     }
}
// "保存参数"    按钮: 保存参数,下发设置到设备
void Dialog::on_pushButton_saveParam_clicked()
{
   help_saveParam();
}

/*************** 复选框响应函数 *******************************/
// 选择基准点
void Dialog::on_checkBox_BaseValue_clicked()
{
   //(1) 清除上次的标记
   if(last_baseValue != -1){
       switch(last_baseValue){
           case 0: ui->checkBox_BaseValue1->setChecked(false); break;
           case 1: ui->checkBox_BaseValue2->setChecked(false); break;
           case 2: ui->checkBox_BaseValue3->setChecked(false); break;
           case 3: ui->checkBox_BaseValue4->setChecked(false); break;
           case 4: ui->checkBox_BaseValue5->setChecked(false); break;
           case 5: ui->checkBox_BaseValue6->setChecked(false); break;
           case 6: ui->checkBox_BaseValue7->setChecked(false); break;
           case 7: ui->checkBox_BaseValue8->setChecked(false); break;

           case 8: ui->checkBox_BaseValue9->setChecked(false); break;
           case 9: ui->checkBox_BaseValue10->setChecked(false); break;
           case 10: ui->checkBox_BaseValue11->setChecked(false); break;
           case 11: ui->checkBox_BaseValue12->setChecked(false); break;
           case 12: ui->checkBox_BaseValue13->setChecked(false); break;
           case 13: ui->checkBox_BaseValue14->setChecked(false); break;
           case 14: ui->checkBox_BaseValue15->setChecked(false); break;
           case 15: ui->checkBox_BaseValue16->setChecked(false); break;

       }
   }
   //(2) 设置新的基准点
   if(ui->checkBox_BaseValue1->isChecked()) last_baseValue = 0;
   else if(ui->checkBox_BaseValue2->isChecked()) last_baseValue = 1;
   else if(ui->checkBox_BaseValue3->isChecked()) last_baseValue = 2;
   else if(ui->checkBox_BaseValue4->isChecked()) last_baseValue = 3;
   else if(ui->checkBox_BaseValue5->isChecked()) last_baseValue = 4;
   else if(ui->checkBox_BaseValue6->isChecked()) last_baseValue = 5;
   else if(ui->checkBox_BaseValue7->isChecked()) last_baseValue = 6;
   else if(ui->checkBox_BaseValue8->isChecked()) last_baseValue = 7;
   else if(ui->checkBox_BaseValue9->isChecked()) last_baseValue = 8;
   else if(ui->checkBox_BaseValue10->isChecked()) last_baseValue = 9;
   else if(ui->checkBox_BaseValue11->isChecked()) last_baseValue = 10;
   else if(ui->checkBox_BaseValue12->isChecked()) last_baseValue = 11;
   else if(ui->checkBox_BaseValue13->isChecked()) last_baseValue = 12;
   else if(ui->checkBox_BaseValue14->isChecked()) last_baseValue = 13;
   else if(ui->checkBox_BaseValue15->isChecked()) last_baseValue = 14;
   else if(ui->checkBox_BaseValue16->isChecked()) last_baseValue = 15;
   else last_baseValue = -1;

   qDebug()<<"(dialog.cpp)新选中的基准点是: "<<QString::number(last_baseValue)<<endl;
}
// 选择手动保存还是自动保存
void Dialog::on_comboBox_SaveDataDynamic_activated(const QString &str)
{
    // 如果是手动保存,则禁止选择自动保存路径,禁止点击“浏览按钮”
    if(str == "手动保存"){
        ui->pushButton_selectFile->setEnabled(false);
        ui->lineEdit_file4save->setEnabled(false);
    }else{
        ui->pushButton_selectFile->setEnabled(true);
        ui->lineEdit_file4save->setEnabled(true);
    }
}
// 选择通道
void Dialog::on_checkBox_ChannelSelected_clicked(){
    if(ui->checkBox_1->isChecked()) isSelected[0] = true;
    else isSelected[0] = false;
    if(ui->checkBox_2->isChecked()) isSelected[1] = true;
    else isSelected[1] = false;
    if(ui->checkBox_3->isChecked()) isSelected[2] = true;
    else isSelected[2] = false;
    if(ui->checkBox_4->isChecked()) isSelected[3] = true;
    else isSelected[3] = false;
    if(ui->checkBox_5->isChecked()) isSelected[4] = true;
    else isSelected[4] = false;
    if(ui->checkBox_6->isChecked()) isSelected[5] = true;
    else isSelected[5] = false;
    if(ui->checkBox_7->isChecked()) isSelected[6] = true;
    else isSelected[6] = false;
    if(ui->checkBox_8->isChecked()) isSelected[7] = true;
    else isSelected[7] = false;

    if(ui->checkBox_9->isChecked()) isSelected[8] = true;
    else isSelected[8] = false;
    if(ui->checkBox_10->isChecked()) isSelected[9] = true;
    else isSelected[9] = false;
    if(ui->checkBox_11->isChecked()) isSelected[10] = true;
    else isSelected[10] = false;
    if(ui->checkBox_12->isChecked()) isSelected[11] = true;
    else isSelected[11] = false;
    if(ui->checkBox_13->isChecked()) isSelected[12] = true;
    else isSelected[12] = false;
    if(ui->checkBox_14->isChecked()) isSelected[13] = true;
    else isSelected[13] = false;
    if(ui->checkBox_15->isChecked()) isSelected[14] = true;
    else isSelected[14] = false;
    if(ui->checkBox_16->isChecked()) isSelected[15] = true;
    else isSelected[15] = false;

}


/************** 单选按钮选择 ******************/
// 第一组
void Dialog::on_Pbtn_11_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_1->setText(QString::number(1000));
    this->ui->Pmin_1->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_12_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_1->setText(QString::number(5000));
    this->ui->Pmin_1->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_13_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_1->setText(QString::number(10000));
    this->ui->Pmin_1->setText(QString::number(-10000));
}

// 第二组
void Dialog::on_Pbtn_21_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_2->setText(QString::number(1000));
    this->ui->Pmin_2->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_22_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_2->setText(QString::number(5000));
    this->ui->Pmin_2->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_23_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_2->setText(QString::number(10000));
    this->ui->Pmin_2->setText(QString::number(-10000));
}

// 第三组
void Dialog::on_Pbtn_31_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_3->setText(QString::number(1000));
    this->ui->Pmin_3->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_32_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_3->setText(QString::number(5000));
    this->ui->Pmin_3->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_33_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_3->setText(QString::number(10000));
    this->ui->Pmin_3->setText(QString::number(-10000));
}

// 第4组
void Dialog::on_Pbtn_41_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_4->setText(QString::number(1000));
    this->ui->Pmin_4->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_42_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_4->setText(QString::number(5000));
    this->ui->Pmin_4->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_43_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_4->setText(QString::number(10000));
    this->ui->Pmin_4->setText(QString::number(-10000));
}

// 第5组
void Dialog::on_Pbtn_51_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_5->setText(QString::number(1000));
    this->ui->Pmin_5->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_52_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_5->setText(QString::number(5000));
    this->ui->Pmin_5->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_53_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_5->setText(QString::number(10000));
    this->ui->Pmin_5->setText(QString::number(-10000));
}

// 第6组
void Dialog::on_Pbtn_61_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_6->setText(QString::number(1000));
    this->ui->Pmin_6->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_62_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_6->setText(QString::number(5000));
    this->ui->Pmin_6->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_63_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_6->setText(QString::number(10000));
    this->ui->Pmin_6->setText(QString::number(-10000));
}

// 第7组
void Dialog::on_Pbtn_71_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_7->setText(QString::number(1000));
    this->ui->Pmin_7->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_72_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_7->setText(QString::number(5000));
    this->ui->Pmin_7->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_73_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_7->setText(QString::number(10000));
    this->ui->Pmin_7->setText(QString::number(-10000));
}

// 第8组
void Dialog::on_Pbtn_81_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_8->setText(QString::number(1000));
    this->ui->Pmin_8->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_82_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_8->setText(QString::number(5000));
    this->ui->Pmin_8->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_83_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_8->setText(QString::number(10000));
    this->ui->Pmin_8->setText(QString::number(-10000));
}

// 第9组
void Dialog::on_Pbtn_91_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_9->setText(QString::number(1000));
    this->ui->Pmin_9->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_92_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_9->setText(QString::number(5000));
    this->ui->Pmin_9->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_93_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_9->setText(QString::number(10000));
    this->ui->Pmin_9->setText(QString::number(-10000));
}

// 第10组
void Dialog::on_Pbtn_a1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_10->setText(QString::number(1000));
    this->ui->Pmin_10->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_a2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_10->setText(QString::number(5000));
    this->ui->Pmin_10->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_a3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_10->setText(QString::number(10000));
    this->ui->Pmin_10->setText(QString::number(-10000));
}

// 第11组
void Dialog::on_Pbtn_b1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_11->setText(QString::number(1000));
    this->ui->Pmin_11->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_b2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_11->setText(QString::number(5000));
    this->ui->Pmin_11->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_b3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_11->setText(QString::number(10000));
    this->ui->Pmin_11->setText(QString::number(-10000));
}

// 第12组
void Dialog::on_Pbtn_c1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_12->setText(QString::number(1000));
    this->ui->Pmin_12->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_c2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_12->setText(QString::number(5000));
    this->ui->Pmin_12->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_c3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_12->setText(QString::number(10000));
    this->ui->Pmin_12->setText(QString::number(-10000));
}

// 第13组
void Dialog::on_Pbtn_d1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_13->setText(QString::number(1000));
    this->ui->Pmin_13->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_d2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_13->setText(QString::number(5000));
    this->ui->Pmin_13->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_d3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_13->setText(QString::number(10000));
    this->ui->Pmin_13->setText(QString::number(-10000));
}

// 第14组
void Dialog::on_Pbtn_e1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_14->setText(QString::number(1000));
    this->ui->Pmin_14->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_e2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_14->setText(QString::number(5000));
    this->ui->Pmin_14->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_e3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_14->setText(QString::number(10000));
    this->ui->Pmin_14->setText(QString::number(-10000));
}

// 第15组
void Dialog::on_Pbtn_f1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_15->setText(QString::number(1000));
    this->ui->Pmin_15->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_f2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_15->setText(QString::number(5000));
    this->ui->Pmin_15->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_f3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_15->setText(QString::number(10000));
    this->ui->Pmin_15->setText(QString::number(-10000));
}

// 第16组
void Dialog::on_Pbtn_g1_clicked()
{
    qDebug()<<"1k的被选中..."<<endl;
    this->ui->Pmax_16->setText(QString::number(1000));
    this->ui->Pmin_16->setText(QString::number(-1000));
}
void Dialog::on_Pbtn_g2_clicked()
{
    qDebug()<<"5k的被选中..."<<endl;
    this->ui->Pmax_16->setText(QString::number(5000));
    this->ui->Pmin_16->setText(QString::number(-5000));
}
void Dialog::on_Pbtn_g3_clicked()
{
    qDebug()<<"10k的被选中..."<<endl;
    this->ui->Pmax_16->setText(QString::number(10000));
    this->ui->Pmin_16->setText(QString::number(-10000));
}


void Dialog::on_comboBox_range1_currentIndexChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_1->setText(QString(""));
        this->ui->Pmin_1->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_1->setText(QString::number(1000));
        this->ui->Pmin_1->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_1->setText(QString::number(2000));
        this->ui->Pmin_1->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_1->setText(QString::number(5000));
        this->ui->Pmin_1->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_1->setText(QString::number(10000));
        this->ui->Pmin_1->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range2_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_2->setText(QString(""));
        this->ui->Pmin_2->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_2->setText(QString::number(1000));
        this->ui->Pmin_2->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_2->setText(QString::number(2000));
        this->ui->Pmin_2->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_2->setText(QString::number(5000));
        this->ui->Pmin_2->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_2->setText(QString::number(10000));
        this->ui->Pmin_2->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range3_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_3->setText(QString(""));
        this->ui->Pmin_3->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_3->setText(QString::number(1000));
        this->ui->Pmin_3->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_3->setText(QString::number(2000));
        this->ui->Pmin_3->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_3->setText(QString::number(5000));
        this->ui->Pmin_3->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_3->setText(QString::number(10000));
        this->ui->Pmin_3->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range4_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_4->setText(QString(""));
        this->ui->Pmin_4->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_4->setText(QString::number(1000));
        this->ui->Pmin_4->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_4->setText(QString::number(2000));
        this->ui->Pmin_4->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_4->setText(QString::number(5000));
        this->ui->Pmin_4->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_4->setText(QString::number(10000));
        this->ui->Pmin_4->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range5_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_5->setText(QString(""));
        this->ui->Pmin_5->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_5->setText(QString::number(1000));
        this->ui->Pmin_5->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_5->setText(QString::number(2000));
        this->ui->Pmin_5->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_5->setText(QString::number(5000));
        this->ui->Pmin_5->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_5->setText(QString::number(10000));
        this->ui->Pmin_5->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range6_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_6->setText(QString(""));
        this->ui->Pmin_6->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_6->setText(QString::number(1000));
        this->ui->Pmin_6->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_6->setText(QString::number(2000));
        this->ui->Pmin_6->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_6->setText(QString::number(5000));
        this->ui->Pmin_6->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_6->setText(QString::number(10000));
        this->ui->Pmin_6->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range7_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_7->setText(QString(""));
        this->ui->Pmin_7->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_7->setText(QString::number(1000));
        this->ui->Pmin_7->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_7->setText(QString::number(2000));
        this->ui->Pmin_7->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_7->setText(QString::number(5000));
        this->ui->Pmin_7->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_7->setText(QString::number(10000));
        this->ui->Pmin_7->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range8_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_8->setText(QString(""));
        this->ui->Pmin_8->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_8->setText(QString::number(1000));
        this->ui->Pmin_8->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_8->setText(QString::number(2000));
        this->ui->Pmin_8->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_8->setText(QString::number(5000));
        this->ui->Pmin_8->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_8->setText(QString::number(10000));
        this->ui->Pmin_8->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range9_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_9->setText(QString(""));
        this->ui->Pmin_9->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_9->setText(QString::number(1000));
        this->ui->Pmin_9->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_9->setText(QString::number(2000));
        this->ui->Pmin_9->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_9->setText(QString::number(5000));
        this->ui->Pmin_9->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_9->setText(QString::number(10000));
        this->ui->Pmin_9->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range10_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_10->setText(QString(""));
        this->ui->Pmin_10->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_10->setText(QString::number(1000));
        this->ui->Pmin_10->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_10->setText(QString::number(2000));
        this->ui->Pmin_10->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_10->setText(QString::number(5000));
        this->ui->Pmin_10->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_10->setText(QString::number(10000));
        this->ui->Pmin_10->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range11_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_11->setText(QString(""));
        this->ui->Pmin_11->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_11->setText(QString::number(1000));
        this->ui->Pmin_11->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_11->setText(QString::number(2000));
        this->ui->Pmin_11->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_11->setText(QString::number(5000));
        this->ui->Pmin_11->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_11->setText(QString::number(10000));
        this->ui->Pmin_11->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range12_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_12->setText(QString(""));
        this->ui->Pmin_12->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_12->setText(QString::number(1000));
        this->ui->Pmin_12->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_12->setText(QString::number(2000));
        this->ui->Pmin_12->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_12->setText(QString::number(5000));
        this->ui->Pmin_12->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_12->setText(QString::number(10000));
        this->ui->Pmin_12->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range13_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_13->setText(QString(""));
        this->ui->Pmin_13->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_13->setText(QString::number(1000));
        this->ui->Pmin_13->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_13->setText(QString::number(2000));
        this->ui->Pmin_13->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_13->setText(QString::number(5000));
        this->ui->Pmin_13->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_13->setText(QString::number(10000));
        this->ui->Pmin_13->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range14_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_14->setText(QString(""));
        this->ui->Pmin_14->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_14->setText(QString::number(1000));
        this->ui->Pmin_14->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_14->setText(QString::number(2000));
        this->ui->Pmin_14->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_14->setText(QString::number(5000));
        this->ui->Pmin_14->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_14->setText(QString::number(10000));
        this->ui->Pmin_14->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range15_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_15->setText(QString(""));
        this->ui->Pmin_15->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_15->setText(QString::number(1000));
        this->ui->Pmin_15->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_15->setText(QString::number(2000));
        this->ui->Pmin_15->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_15->setText(QString::number(5000));
        this->ui->Pmin_15->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_15->setText(QString::number(10000));
        this->ui->Pmin_15->setText(QString::number(-10000));
    }
}

void Dialog::on_comboBox_range16_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
        this->ui->Pmax_16->setText(QString(""));
        this->ui->Pmin_16->setText(QString(""));
    } else if(arg1 == "1K"){
        this->ui->Pmax_16->setText(QString::number(1000));
        this->ui->Pmin_16->setText(QString::number(-1000));
    } else if(arg1 == "2K"){
        this->ui->Pmax_16->setText(QString::number(2000));
        this->ui->Pmin_16->setText(QString::number(-2000));
    } else if(arg1 == "5K"){
        this->ui->Pmax_16->setText(QString::number(5000));
        this->ui->Pmin_16->setText(QString::number(-5000));
    } else if(arg1 == "10K"){
        this->ui->Pmax_16->setText(QString::number(10000));
        this->ui->Pmin_16->setText(QString::number(-10000));
    }
}
