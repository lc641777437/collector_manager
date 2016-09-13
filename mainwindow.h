#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>


#include "uartthread.h"
#include "graphthread.h"
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

    void initSeialPort();
    void show_wave();


private:

    QCustomPlot *customPlot;
    UartThread *uart_thread;
    TextTread *text_thread;
    QTimer *timer;

private slots:
    void on_pushButton_Send_clicked();
    void on_pushButton_ClearText_clicked();
    void on_pushButton_GetCOM_clicked();
    void on_pushButton_setSampleRate_clicked();
    void on_pushButton_SetDeviceID_clicked();
    void on_pushButton_StartCollect_clicked();
    void on_pushButton_OpenSerial_clicked();
    void on_pushButton_Reset_clicked();

};



#endif // MAINWINDOW_H
