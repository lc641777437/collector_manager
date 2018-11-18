#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QPoint>
#include <QPointF>

#include "uartthread.h"
#include "graphthread.h"
#include "tcpclientthread.h"
#include "dialog.h"

#define MAX_SHOW_TIME (120 * 1000) //ms
#define TIMEOUTTIME (1000 * 2)


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

#define STYLE_RED "color:red"
#define STYLE_GREEN "color:green"
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
    QFile vfile;
    bool box[16] = {false};                   // 已选通道box
    unsigned int samplerate = 0;              // 采样率
    unsigned int samplerateTmp = 0;
    unsigned int timeCount = 0;
    bool isStartCollect = false;
    bool isChannal[16] = {false};              // 可用通道box
    CONNECT_TYPE connectType = CONNECT_NULL;


public:
    QTimer *timer;
    QCustomPlot *customPlot;
    GraphThread *graph_thread;
    UartThread *uart_thread;
    TcpClientThread *tcpclient_thread;

    // 新添加变量
    double Density;
    double e;
    double coefficient1;
    double coefficient2;
    double coefficient3;
    double coefficient4;
    double coefficient5;
    double coefficient6;
    double coefficient7;
    double coefficient8;
    double coefficient9;
    double coefficient10;

    double AutoSavePeriod;
    QString AutoSaveFile;
    double H[20];
    double PmaxList[20];         // 最大压强
    double PminList[20];         // 最小压强
    unsigned char baseValue;
    QTimer *timer4AutoSaveFile;
    int timerCount;
    int AutoSaveFileId;
    bool readInitialValue;

    void on_checkUartPort();


private slots:
    void on_pushButton_GetCOM_clicked();
    void on_pushButton_wireless_clicked();

    void on_pushButton_SocketConnect_clicked();

    void on_pushButton_SetParam_clicked();

    void on_pushButton_StartCollect_clicked();
    void on_pushButton_SaveData_clicked();

    void on_checkBox_clicked();
    void on_auto_save_file();

public slots:

    void PresscontextMenuRequest_1(QPoint pos);
    void PressSaveGraph_1();

    void flush_checkBox(void);

};



#endif // MAINWINDOW_H
