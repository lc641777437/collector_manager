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

/*************** 初始化 *************************************/
GraphThread::GraphThread(QString message, QObject *parent) :
    QThread(parent)
  , message(message)
{
    pMainWindow = static_cast<MainWindow *>(parent);
    // 1,初始化绘图环境
    lhc_graph_Initial();

    // 2,定时绘图
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(lhc_ShowWave()));
    timer->start(1000);

    // 3,图像保存
    pMainWindow->ui->widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainWindow->ui->widget, SIGNAL(customContextMenuRequested(QPoint)), pMainWindow, SLOT(PresscontextMenuRequest_1(QPoint)));
}
GraphThread::~GraphThread()
{
    this->wait();
    qDebug() << "(graphthread.cpp)"<<this<<"over";
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

/************** 功能函数 *****************************/
// 我的初始化绘图环境
void GraphThread::lhc_graph_Initial()
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 255));

    // 线一
    pMainWindow->ui->widget->addGraph();
    pMainWindow->ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    pMainWindow->ui->widget->graph(0)->setPen(pen);
    pMainWindow->ui->widget->graph(0)->setBrush(Qt::NoBrush); //QBrush(QColor(255/16.0*3,160,100,150))
    pMainWindow->ui->widget->graph(0)->setVisible(true);
    pMainWindow->ui->widget->graph(0)->setName("未使用");

    // 线二
    pMainWindow->ui->widget->addGraph();
    pMainWindow->ui->widget->graph(1)->setLineStyle(QCPGraph::lsLine);
    pen.setColor(QColor(255, 0, 0, 255));
    pMainWindow->ui->widget->graph(1)->setPen(pen);
    pMainWindow->ui->widget->graph(1)->setBrush(Qt::NoBrush); //QBrush(QColor(255/16.0*3,160,100,150))
    pMainWindow->ui->widget->graph(1)->setVisible(true);
    pMainWindow->ui->widget->graph(1)->setName("未使用");

    //线三
    pMainWindow->ui->widget->addGraph();
    pMainWindow->ui->widget->graph(2)->setLineStyle(QCPGraph::lsLine);
    pen.setColor(QColor(0, 255, 0, 255));
    pMainWindow->ui->widget->graph(2)->setPen(pen);
    pMainWindow->ui->widget->graph(2)->setBrush(Qt::NoBrush); //QBrush(QColor(255/16.0*3,160,100,150))
    pMainWindow->ui->widget->graph(2)->setVisible(true);
    pMainWindow->ui->widget->graph(2)->setName("未使用");

    // 线四
    pMainWindow->ui->widget->addGraph();
    pMainWindow->ui->widget->graph(3)->setLineStyle(QCPGraph::lsLine);
    pen.setColor(QColor(0, 0, 0, 255));
    pMainWindow->ui->widget->graph(3)->setPen(pen);
    pMainWindow->ui->widget->graph(3)->setBrush(Qt::NoBrush); //QBrush(QColor(255/16.0*3,160,100,150))
    pMainWindow->ui->widget->graph(3)->setVisible(true);
    pMainWindow->ui->widget->graph(3)->setName("未使用");

    // 设置坐标轴
    pMainWindow->ui->widget->setEnabled(true);
    pMainWindow->ui->widget->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    pMainWindow->ui->widget->xAxis->setTickLabelFont(QFont(QFont().family(), 8));    // set a more compact font size for bottom and left axis tick labels:
    pMainWindow->ui->widget->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    pMainWindow->ui->widget->xAxis->setAutoTickStep(true);    // set a fixed tick-step to one tick per month:
    pMainWindow->ui->widget->xAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget->yAxis->setAutoTicks(true);    // apply manual tick and tick label for left axis:
    pMainWindow->ui->widget->yAxis->setAutoTickLabels(true);
    pMainWindow->ui->widget->xAxis->setLabel("时间(ms)");// set axis labels
    pMainWindow->ui->widget->yAxis->setLabel("挠度值(mm)");
    pMainWindow->ui->widget->xAxis2->setVisible(true);// make top and right axes visible but without ticks and labels:
    pMainWindow->ui->widget->yAxis2->setVisible(true);
    pMainWindow->ui->widget->xAxis2->setTicks(false);
    pMainWindow->ui->widget->yAxis2->setTicks(false);
    pMainWindow->ui->widget->xAxis2->setTickLabels(true);
    pMainWindow->ui->widget->yAxis2->setTickLabels(true);
    pMainWindow->ui->widget->xAxis->setRange(0,MAX_SHOW_TIME);
    pMainWindow->ui->widget->yAxis->setRange(-100,20);

    pMainWindow->ui->widget->legend->setVisible(true);// show legend:

    pMainWindow->ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
// 我的绘图
void GraphThread::lhc_ShowWave()
{
    if(!pMainWindow->isStartCollect)return;
    int i = 0, count = 0;

    // 设置x轴
    if(time[time.length()-1] > MAX_SHOW_TIME)
    {
        pMainWindow->ui->widget->xAxis->setRange(time[0],time[time.length() - 1]);
    }
    else
    {
        pMainWindow->ui->widget->xAxis->setRange(0,MAX_SHOW_TIME);
    }

    // 根据选中了的通道绘图
    for(; i < 16;i++){
        if(pMainWindow->box[i]){
            switch(count++)
            {
            case 0:
                pMainWindow->ui->widget->graph(0)->setData(time,value[i]);
                pMainWindow->ui->widget->graph(0)->setVisible(true);
                break;
            case 1:
                pMainWindow->ui->widget->graph(1)->setData(time,value[i]);
                pMainWindow->ui->widget->graph(1)->setVisible(true);
                break;
            case 2:
                pMainWindow->ui->widget->graph(2)->setData(time,value[i]);
                pMainWindow->ui->widget->graph(2)->setVisible(true);
                break;
            case 3:
                pMainWindow->ui->widget->graph(3)->setData(time,value[i]);
                pMainWindow->ui->widget->graph(3)->setVisible(true);
                break;
            default:
                break;
            }
        }
    }
    // 抵消掉上面运算多带来的+1效果(count++语句)
    count--;
    while(count++ < 4){
        switch(count++){
        case 0:
            pMainWindow->ui->widget->graph(0)->setVisible(false);
            break;
        case 1:
            pMainWindow->ui->widget->graph(1)->setVisible(false);
            break;
        case 2:
            pMainWindow->ui->widget->graph(2)->setVisible(false);
            break;
        case 3:
            pMainWindow->ui->widget->graph(3)->setVisible(false);
            break;
        default:
            break;
        }
    }

    //设置完数据后,绘图
    pMainWindow->ui->widget->replot();
}

