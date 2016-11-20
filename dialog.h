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
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    MainWindow  *pMainWindow;
private:
    Ui::Dialog *ui;

public slots:
    virtual void accept();
    void changeShow(unsigned short ctrl);


signals:
    void SendCTRL(int ctrl);

};

#endif // DIALOG_H
