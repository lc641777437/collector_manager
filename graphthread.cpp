#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphthread.h"

#include <Qfile>
#include <Qdebug>
#include <Qtime>
#include <QMenu>
#include <QTextStream>

extern QVector<double> time;
extern QVector<double> value[16];

GraphThread::GraphThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);
    graph_Initial();
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(ShowWave()));
    timer->start(1000);
    pMainWindow->ui->widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainWindow->ui->widget, SIGNAL(customContextMenuRequested(QPoint)), pMainWindow, SLOT(PresscontextMenuRequest_1(QPoint)));
    pMainWindow->ui->widget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainWindow->ui->widget_2, SIGNAL(customContextMenuRequested(QPoint)), pMainWindow, SLOT(PresscontextMenuRequest_2(QPoint)));
    pMainWindow->ui->widget_3->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainWindow->ui->widget_3, SIGNAL(customContextMenuRequested(QPoint)), pMainWindow, SLOT(PresscontextMenuRequest_3(QPoint)));
    pMainWindow->ui->widget_4->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainWindow->ui->widget_4, SIGNAL(customContextMenuRequested(QPoint)), pMainWindow, SLOT(PresscontextMenuRequest_4(QPoint)));

}

GraphThread::~GraphThread()
{
    this->wait();
    qDebug() << this<<"over";
    this->exit();
}

void GraphThread::setMessage(QString message)
{
    this->message = message;
}

QString GraphThread::getMessage()
{
    return this->message;
}

void GraphThread::ShowWave()
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

    for(; i < 16;i++){
        if(pMainWindow->box[i]){
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
    while(count++ < 4){
        switch(count++){
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

void GraphThread::graph_Initial()
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

    pMainWindow->ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    pMainWindow->ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    pMainWindow->ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    pMainWindow->ui->widget_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
