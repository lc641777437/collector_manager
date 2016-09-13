#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphthread.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>

extern QVector<double> time;
extern QVector<double> value[16];
extern bool isChannal[16];
extern QByteArray ReadData;
extern const char tag[2] = {0xA5,0xA5};
extern QFile file;
extern int timer_Count;

TextTread::TextTread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);
    graph_Initial();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowWave()), Qt::DirectConnection);
    timer->start(1000);

}

TextTread::~TextTread()
{
    this->wait();
    qDebug() << this<<"over";
}

void TextTread::setMessage(QString message)
{
    this->message = message;
}

QString TextTread::getMessage()
{
    return this->message;
}

void TextTread::run()
{
    exec();
}

void TextTread::ShowWave()
{
    static bool isAlarmed = false;

    int channal;
    timer_Count++;

    for(channal = 0;channal < 16;channal++)
    {
        pMainWindow->ui->widget->graph()->setVisible(false);
    }

    channal = pMainWindow->ui->comboBoxChannal->currentText().toInt()-1;
    if(isChannal[channal])
    {
        pMainWindow->ui->widget->graph(channal)->setData(time,value[channal]);
        pMainWindow->ui->widget->graph(channal)->setVisible(true);
        isAlarmed = false;
    }
    else if(!isAlarmed)
    {
        QMessageBox::warning(pMainWindow, tr("采集分析软件"), tr("该通道未插入设备:\n"));
        isAlarmed = true;
    }
    if(time[time.length()-1] > MAX_SHOW_TIME)
    {
        pMainWindow->ui->widget->xAxis->setRange(time[0],time[time.length() - 1]);
    }
    else
    {
        pMainWindow->ui->widget->xAxis->setRange(0,MAX_SHOW_TIME);
    }
    pMainWindow->ui->widget->replot();
}

void TextTread::graph_Initial()
{
    for(int channal = 0;channal < 16;channal++)
    {
        pMainWindow->ui->widget->addGraph();
        QPen pen;
        pen.setColor(QColor(0, 0, 255, 200));
        pMainWindow->ui->widget->graph()->setLineStyle(QCPGraph::lsLine);
        pMainWindow->ui->widget->graph()->setPen(pen);
        pMainWindow->ui->widget->graph()->setBrush(QBrush(QColor(255/16.0*channal,160,100,150)));
        pMainWindow->ui->widget->graph()->setVisible(false);
    }
    pMainWindow->ui->widget->setEnabled(true);
    pMainWindow->ui->widget->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    pMainWindow->ui->widget->xAxis->setTickLabelFont(QFont(QFont().family(), 8));    // set a more compact font size for bottom and left axis tick labels:
    pMainWindow->ui->widget->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    pMainWindow->ui->widget->xAxis->setAutoTickStep(true);    // set a fixed tick-step to one tick per month:
    pMainWindow->ui->widget->xAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget->yAxis->setAutoTicks(true);    // apply manual tick and tick label for left axis:
    pMainWindow->ui->widget->yAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget->xAxis->setLabel("Time");// set axis labels
    pMainWindow->ui->widget->yAxis->setLabel("Value");
    pMainWindow->ui->widget->xAxis2->setVisible(true);// make top and right axes visible but without ticks and labels:
    pMainWindow->ui->widget->yAxis2->setVisible(true);
    pMainWindow->ui->widget->xAxis2->setTicks(false);
    pMainWindow->ui->widget->yAxis2->setTicks(false);
    pMainWindow->ui->widget->xAxis2->setTickLabels(true);
    pMainWindow->ui->widget->yAxis2->setTickLabels(true);
    pMainWindow->ui->widget->xAxis->setRange(0,MAX_SHOW_TIME);
    pMainWindow->ui->widget->yAxis->setRange(0, 5);
    pMainWindow->ui->widget->legend->setVisible(false);// show legend:
}
