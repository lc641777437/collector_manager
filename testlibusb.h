#ifndef TESTLIBUSB
#define TESTLIBUSB
#include <QMainWindow>

namespace Ui {
class USB;
}

class USB : public QMainWindow
{
    Q_OBJECT

public:
    explicit USB(QWidget *parent = 0);
    ~USB();

private:
    Ui::USB *ui;

    void my_usb_get_device_list(void);
};
#endif // TESTLIBUSB

