#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H
#include <iostream>

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>

class MainWindow;

class TcpClientThread : public QThread
{
    Q_OBJECT
public:
    TcpClientThread(QString message = "", QObject *parent = NULL);
    ~TcpClientThread();
    MainWindow  *pMainWindow;
    QTcpSocket *socket;
    QTimer *timer;

private:
    QString message;
    QByteArray ReadData;
    QByteArray CommandData;

    // 新增变量
    int id;
    int last_second;
    double f_avg[16];           // 扰度均值

    void ADValue_proc(QByteArray &ReadBuf);
    void time_MoveLeftInsert(double data);
    void data_MoveLeftInsert(int channal, double data);

public slots:
    void tcptimeout();
    void socketconnected();
    void socketreadyread();
};

#endif // TCPCLIENTTHREAD_H
