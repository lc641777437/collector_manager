#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

extern unsigned short ctrl;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("采集类型设置");
    pMainWindow = static_cast<MainWindow *>(parent);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::accept()
{
    int ctrl = 0;
    if(ui->comboBox->currentText() == "电压")
    {
        ctrl |= 1<<0;
    }

    if(ui->comboBox_2->currentText() == "电压")
    {
        ctrl |= 1<<1;
    }

    if(ui->comboBox_3->currentText() == "电压")
    {
        ctrl |= 1<<2;
    }

    if(ui->comboBox_4->currentText() == "电压")
    {
        ctrl |= 1<<3;
    }

    if(ui->comboBox_5->currentText() == "电压")
    {
        ctrl |= 1<<4;
    }

    if(ui->comboBox_6->currentText() == "电压")
    {
        ctrl |= 1<<5;
    }

    if(ui->comboBox_7->currentText() == "电压")
    {
        ctrl |= 1<<6;
    }

    if(ui->comboBox_8->currentText() == "电压")
    {
        ctrl |= 1<<7;
    }

    if(ui->comboBox_9->currentText() == "电压")
    {
        ctrl |= 1<<8;
    }

    if(ui->comboBox_10->currentText() == "电压")
    {
        ctrl |= 1<<9;
    }

    if(ui->comboBox_11->currentText() == "电压")
    {
        ctrl |= 1<<10;
    }

    if(ui->comboBox_12->currentText() == "电压")
    {
        ctrl |= 1<<11;
    }

    if(ui->comboBox_13->currentText() == "电压")
    {
        ctrl |= 1<<12;
    }

    if(ui->comboBox_14->currentText() == "电压")
    {
        ctrl |= 1<<13;
    }

    if(ui->comboBox_15->currentText() == "电压")
    {
        ctrl |= 1<<14;
    }
    if(ui->comboBox_16->currentText() == "电压")
    {
        ctrl |= 1<<15;
    }
    emit SendCTRL(ctrl);
    this->close();
}

void Dialog::changeShow(unsigned short ctrl)
{
    qDebug()<<ctrl;
    if(ctrl&0x0001)
    {
        ui->comboBox->setCurrentText("电压");
    }
    else
    {
        ui->comboBox->setCurrentText("电流");
    }
    if(ctrl&0x0002)
    {
        ui->comboBox_2->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_2->setCurrentText("电流");
    }
    if(ctrl&0x0004)
    {
        ui->comboBox_3->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_3->setCurrentText("电流");
    }
    if(ctrl&0x0008)
    {
        ui->comboBox_4->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_4->setCurrentText("电流");
    }
    if(ctrl&0x0010)
    {
        ui->comboBox_5->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_5->setCurrentText("电流");
    }
    if(ctrl&0x0020)
    {
        ui->comboBox_6->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_6->setCurrentText("电流");
    }
    if(ctrl&0x0040)
    {
        ui->comboBox_7->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_7->setCurrentText("电流");
    }
    if(ctrl&0x0080)
    {
        ui->comboBox_8->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_8->setCurrentText("电流");
    }
    if(ctrl&0x0100)
    {
        ui->comboBox_9->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_9->setCurrentText("电流");
    }
    if(ctrl&0x0200)
    {
        ui->comboBox_10->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_10->setCurrentText("电流");
    }
    if(ctrl&0x0400)
    {
        ui->comboBox_11->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_11->setCurrentText("电流");
    }
    if(ctrl&0x0800)
    {
        ui->comboBox_12->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_12->setCurrentText("电流");
    }
    if(ctrl&0x1000)
    {
        ui->comboBox_13->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_13->setCurrentText("电流");
    }
    if(ctrl&0x2000)
    {
        ui->comboBox_14->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_14->setCurrentText("电流");
    }
    if(ctrl&0x4000)
    {
        ui->comboBox_15->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_15->setCurrentText("电流");
    }
    if(ctrl&0x8000)
    {
        ui->comboBox_16->setCurrentText("电压");
    }
    else
    {
        ui->comboBox_16->setCurrentText("电流");
    }
}

