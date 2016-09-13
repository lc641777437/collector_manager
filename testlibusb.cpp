#include "lusb0_usb.h"

#include <QDebug>
USB::USB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::USB)
{

    qDebug()<<"VID:";

    usb_set_debug(250);
    usb_init(); /* initialize the library */
    usb_find_busses(); /* find all busses */
    usb_find_devices(); /* find all connected devices */

    my_usb_get_device_list();

    //resize(320, 240);
}



