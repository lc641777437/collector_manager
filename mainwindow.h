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
#include "dialog.h"
#define MAX_SHOW_TIME 120 * 1000 //ms
#define TIME_SLOT 1000  //ms
namespace Ui {
class MainWindow;
}

class UartThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    UartThread *uart_thread;
    Dialog *setCTRL;
    bool isStart;

    void initSeialPort();
    void show_wave();


private:
    bool isWireless = false;
    bool uart_state = false;

    QCustomPlot *customPlot;
    TextTread *text_thread;
    QTimer *timer;

private slots:
    void on_pushButton_Send_clicked();
    void on_pushButton_GetCOM_clicked();
    void on_pushButton_StartCollect_clicked();
    void on_pushButton_OpenSerial_clicked();
    void on_pushButton_Reset_clicked();
    void on_pushButton_Reset_2_clicked();
    void on_checkBox_clicked();
    void on_pushButton_wireless_clicked();

    void on_pushButton_SetParam_clicked();

    void on_pushButton_SetServer_clicked();

    void on_pushButton_clicked();

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
