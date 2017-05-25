#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QPoint>

#include "uartthread.h"
#include "graphthread.h"
#include "tcpclientthread.h"
#include "dialog.h"

#define MAX_SHOW_TIME 120 * 1000 //ms
#define TIMEOUTTIME (1000)


typedef enum{
    STATE_NULL,
    STATE_OPEN_SERIAL,
    STATE_START_COLLECT,
    STATE_STOP_COLLECT,
    STATE_CONNECT_SOCKET
} STATE_TYPE;

typedef enum{
    CONNECT_NULL,
    CONNECT_SERIAL,
    CONNECT_SOCKET,
} CONNECT_TYPE;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

    void show_wave();
    void changeState(STATE_TYPE type);

public:
    QFile file;
    bool box[16] = {false};
    unsigned int timeCount = 0;
    bool isStartCollect = false;
    bool isChannal[16] = {false};
    CONNECT_TYPE connectType = CONNECT_NULL;

private:
    QCustomPlot *customPlot;
    GraphThread *graph_thread;
    UartThread *uart_thread;
    TcpClientThread *tcpclient_thread;

    void on_checkUartPort();


private slots:
    void on_pushButton_GetCOM_clicked();
    void on_pushButton_wireless_clicked();

    void on_pushButton_SocketConnect_clicked();

    void on_pushButton_SetParam_clicked();
    void on_pushButton_SetServer_clicked();
    void on_pushButton_Reset_2_clicked();

    void on_pushButton_StartCollect_clicked();
    void on_pushButton_SaveData_clicked();

    void on_checkBox_clicked();

public slots:

    void PresscontextMenuRequest_1(QPoint pos);
    void PressSaveGraph_1();

    void PresscontextMenuRequest_2(QPoint pos);
    void PressSaveGraph_2();

    void PresscontextMenuRequest_3(QPoint pos);
    void PressSaveGraph_3();

    void PresscontextMenuRequest_4(QPoint pos);
    void PressSaveGraph_4();

};



#endif // MAINWINDOW_H
