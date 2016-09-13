#ifndef TEXTTHREAD
#define TEXTTHREAD

#include <QThread>
#include <iostream>
#include <QDebug>
#include <QTimer>

using namespace std;

class MainWindow;

class TextTread : public QThread
{
    Q_OBJECT
public:
    TextTread(QString message = "", QObject *parent = NULL);
    ~TextTread();
    MainWindow  *pMainWindow;
    void setMessage(QString);
    QString getMessage();
    void run();
    void graph_Initial();

private:
    QString message;
    QTimer *timer;

public slots:
    void ShowWave();
};
#endif // TEXTTHREAD

