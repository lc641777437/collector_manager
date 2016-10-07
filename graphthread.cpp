#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphthread.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMessageBox>
#include <QTextStream>

extern QByteArray ReadData;
extern QVector<double> time;
extern QVector<double> value[16];
extern QFile file;

extern bool isChannal[16];
extern int timer_Count;
extern bool box[16];

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
    this->exit();
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
    int i = 0, count = 0;
    if(time[time.length()-1] > MAX_SHOW_TIME)
    {
        pMainWindow->ui->widget->xAxis->setRange(time[0],time[time.length() - 1]);
        pMainWindow->ui->widget_2->xAxis->setRange(time[0],time[time.length() - 1]);
        pMainWindow->ui->widget_3->xAxis->setRange(time[0],time[time.length() - 1]);
        pMainWindow->ui->widget_4->xAxis->setRange(time[0],time[time.length() - 1]);
    }
    else
    {
        pMainWindow->ui->widget->xAxis->setRange(0,MAX_SHOW_TIME);
        pMainWindow->ui->widget_2->xAxis->setRange(0,MAX_SHOW_TIME);
        pMainWindow->ui->widget_3->xAxis->setRange(0,MAX_SHOW_TIME);
        pMainWindow->ui->widget_4->xAxis->setRange(0,MAX_SHOW_TIME);
    }

    for(; i < 16;i++)
    {
        if(box[i])
        {
            switch(count++)
            {
            case 0:
                pMainWindow->ui->widget->graph()->setData(time,value[i]);
                pMainWindow->ui->widget->graph()->setVisible(true);
                break;
            case 1:
                pMainWindow->ui->widget_2->graph()->setData(time,value[i]);
                pMainWindow->ui->widget_2->graph()->setVisible(true);
                break;
            case 2:
                pMainWindow->ui->widget_3->graph()->setData(time,value[i]);
                pMainWindow->ui->widget_3->graph()->setVisible(true);
                break;
            case 3:
                pMainWindow->ui->widget_4->graph()->setData(time,value[i]);
                pMainWindow->ui->widget_4->graph()->setVisible(true);
                break;
            default:
                break;
            }
        }
    }
    count--;
    while(count++ < 4)
    {
        switch(count++)
        {
        case 0:
            pMainWindow->ui->widget->graph()->setVisible(false);
            break;
        case 1:
            pMainWindow->ui->widget_2->graph()->setVisible(false);
            break;
        case 2:
            pMainWindow->ui->widget_3->graph()->setVisible(false);
            break;
        case 3:
            pMainWindow->ui->widget_4->graph()->setVisible(false);
            break;
        default:
            break;
        }
    }

    pMainWindow->ui->widget->replot();
    pMainWindow->ui->widget_2->replot();
    pMainWindow->ui->widget_3->replot();
    pMainWindow->ui->widget_4->replot();
}

void TextTread::graph_Initial()
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 200));

    pMainWindow->ui->widget->addGraph();
    pMainWindow->ui->widget->graph()->setLineStyle(QCPGraph::lsLine);
    pMainWindow->ui->widget->graph()->setPen(pen);
    pMainWindow->ui->widget->graph()->setBrush(QBrush(QColor(255/16.0*3,160,100,150)));
    pMainWindow->ui->widget->graph()->setVisible(true);

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

    pMainWindow->ui->widget_2->addGraph();
    pMainWindow->ui->widget_2->graph()->setLineStyle(QCPGraph::lsLine);
    pMainWindow->ui->widget_2->graph()->setPen(pen);
    pMainWindow->ui->widget_2->graph()->setBrush(QBrush(QColor(255/16.0*3,160,100,150)));
    pMainWindow->ui->widget_2->graph()->setVisible(true);

    pMainWindow->ui->widget_2->setEnabled(true);
    pMainWindow->ui->widget_2->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    pMainWindow->ui->widget_2->xAxis->setTickLabelFont(QFont(QFont().family(), 8));    // set a more compact font size for bottom and left axis tick labels:
    pMainWindow->ui->widget_2->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    pMainWindow->ui->widget_2->xAxis->setAutoTickStep(true);    // set a fixed tick-step to one tick per month:
    pMainWindow->ui->widget_2->xAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_2->yAxis->setAutoTicks(true);    // apply manual tick and tick label for left axis:
    pMainWindow->ui->widget_2->yAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_2->xAxis->setLabel("Time");// set axis labels
    pMainWindow->ui->widget_2->yAxis->setLabel("Value");
    pMainWindow->ui->widget_2->xAxis2->setVisible(true);// make top and right axes visible but without ticks and labels:
    pMainWindow->ui->widget_2->yAxis2->setVisible(true);
    pMainWindow->ui->widget_2->xAxis2->setTicks(false);
    pMainWindow->ui->widget_2->yAxis2->setTicks(false);
    pMainWindow->ui->widget_2->xAxis2->setTickLabels(true);
    pMainWindow->ui->widget_2->yAxis2->setTickLabels(true);
    pMainWindow->ui->widget_2->xAxis->setRange(0,MAX_SHOW_TIME);
    pMainWindow->ui->widget_2->yAxis->setRange(0, 5);
    pMainWindow->ui->widget_2->legend->setVisible(false);// show legend:

    pMainWindow->ui->widget_3->addGraph();
    pMainWindow->ui->widget_3->graph()->setLineStyle(QCPGraph::lsLine);
    pMainWindow->ui->widget_3->graph()->setPen(pen);
    pMainWindow->ui->widget_3->graph()->setBrush(QBrush(QColor(255/16.0*3,160,100,150)));
    pMainWindow->ui->widget_3->graph()->setVisible(true);

    pMainWindow->ui->widget_3->setEnabled(true);
    pMainWindow->ui->widget_3->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    pMainWindow->ui->widget_3->xAxis->setTickLabelFont(QFont(QFont().family(), 8));    // set a more compact font size for bottom and left axis tick labels:
    pMainWindow->ui->widget_3->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    pMainWindow->ui->widget_3->xAxis->setAutoTickStep(true);    // set a fixed tick-step to one tick per month:
    pMainWindow->ui->widget_3->xAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_3->yAxis->setAutoTicks(true);    // apply manual tick and tick label for left axis:
    pMainWindow->ui->widget_3->yAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_3->xAxis->setLabel("Time");// set axis labels
    pMainWindow->ui->widget_3->yAxis->setLabel("Value");
    pMainWindow->ui->widget_3->xAxis2->setVisible(true);// make top and right axes visible but without ticks and labels:
    pMainWindow->ui->widget_3->yAxis2->setVisible(true);
    pMainWindow->ui->widget_3->xAxis2->setTicks(false);
    pMainWindow->ui->widget_3->yAxis2->setTicks(false);
    pMainWindow->ui->widget_3->xAxis2->setTickLabels(true);
    pMainWindow->ui->widget_3->yAxis2->setTickLabels(true);
    pMainWindow->ui->widget_3->xAxis->setRange(0,MAX_SHOW_TIME);
    pMainWindow->ui->widget_3->yAxis->setRange(0, 5);
    pMainWindow->ui->widget_3->legend->setVisible(false);// show legend:

    pMainWindow->ui->widget_4->addGraph();
    pMainWindow->ui->widget_4->graph()->setLineStyle(QCPGraph::lsLine);
    pMainWindow->ui->widget_4->graph()->setPen(pen);
    pMainWindow->ui->widget_4->graph()->setBrush(QBrush(QColor(255/16.0*3,160,100,150)));
    pMainWindow->ui->widget_4->graph()->setVisible(true);

    pMainWindow->ui->widget_4->setEnabled(true);
    pMainWindow->ui->widget_4->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    pMainWindow->ui->widget_4->xAxis->setTickLabelFont(QFont(QFont().family(), 8));    // set a more compact font size for bottom and left axis tick labels:
    pMainWindow->ui->widget_4->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    pMainWindow->ui->widget_4->xAxis->setAutoTickStep(true);    // set a fixed tick-step to one tick per month:
    pMainWindow->ui->widget_4->xAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_4->yAxis->setAutoTicks(true);    // apply manual tick and tick label for left axis:
    pMainWindow->ui->widget_4->yAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget_4->xAxis->setLabel("Time");// set axis labels
    pMainWindow->ui->widget_4->yAxis->setLabel("Value");
    pMainWindow->ui->widget_4->xAxis2->setVisible(true);// make top and right axes visible but without ticks and labels:
    pMainWindow->ui->widget_4->yAxis2->setVisible(true);
    pMainWindow->ui->widget_4->xAxis2->setTicks(false);
    pMainWindow->ui->widget_4->yAxis2->setTicks(false);
    pMainWindow->ui->widget_4->xAxis2->setTickLabels(true);
    pMainWindow->ui->widget_4->yAxis2->setTickLabels(true);
    pMainWindow->ui->widget_4->xAxis->setRange(0,MAX_SHOW_TIME);
    pMainWindow->ui->widget_4->yAxis->setRange(0, 5);
    pMainWindow->ui->widget_4->legend->setVisible(false);// show legend:


}
