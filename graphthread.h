#ifndef GRAPHTHREAD_H
#define GRAPHTHREAD_H
#include <iostream>

#include <QThread>
#include <QDebug>
#include <QTimer>

using namespace std;

class MainWindow;

class GraphThread : public QThread
{
    Q_OBJECT
public:
    GraphThread(QString message = "", QObject *parent = NULL);
    ~GraphThread();
    MainWindow  *pMainWindow;
    void setMessage(QString);
    QString getMessage();

    void lhc_graph_Initial();  // 初始化画图
//    void graph_Initial();

private:
    QString message;
    QTimer *timer;

public slots:

    void lhc_ShowWave();     // 画图
//    void ShowWave();
};
#endif // GRAPHTHREAD_H

