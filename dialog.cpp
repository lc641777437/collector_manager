#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("采集类型设置");


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

