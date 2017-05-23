#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class MainWindow;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, unsigned char devIDH, unsigned char devIDL, unsigned char ctrlH, unsigned char ctrlL,\
                    unsigned char fre, unsigned char sendTimeServer, unsigned char sendTimeDynamic);
    ~Dialog();
    MainWindow  *pMainWindow;
    bool isReject;
    unsigned char pDevIDH;
    unsigned char pDevIDL;
    unsigned char pCtrlH;
    unsigned char pCtrlL;
    unsigned char pFre;
    unsigned char pSendTimeServer;
    unsigned char pSendTimeDynamic;

private:
    Ui::Dialog *ui;

public slots:
    virtual void accept();
    virtual void reject();

signals:
    void SendCTRL(int ctrl);

};

#endif // DIALOG_H
