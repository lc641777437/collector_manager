/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 26), // "on_pushButton_Send_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 28), // "on_pushButton_GetCOM_clicked"
QT_MOC_LITERAL(4, 68, 35), // "on_pushButton_setSampleRate_c..."
QT_MOC_LITERAL(5, 104, 33), // "on_pushButton_SetDeviceID_cli..."
QT_MOC_LITERAL(6, 138, 34), // "on_pushButton_StartCollect_cl..."
QT_MOC_LITERAL(7, 173, 32), // "on_pushButton_OpenSerial_clicked"
QT_MOC_LITERAL(8, 206, 27), // "on_pushButton_Reset_clicked"
QT_MOC_LITERAL(9, 234, 29), // "on_pushButton_setCTRL_clicked"
QT_MOC_LITERAL(10, 264, 33), // "on_pushButton_setServerIP_cli..."
QT_MOC_LITERAL(11, 298, 29), // "on_pushButton_Reset_2_clicked"
QT_MOC_LITERAL(12, 328, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(13, 348, 30), // "on_pushButton_wireless_clicked"
QT_MOC_LITERAL(14, 379, 7), // "GetCTRL"
QT_MOC_LITERAL(15, 387, 4) // "ctrl"

    },
    "MainWindow\0on_pushButton_Send_clicked\0"
    "\0on_pushButton_GetCOM_clicked\0"
    "on_pushButton_setSampleRate_clicked\0"
    "on_pushButton_SetDeviceID_clicked\0"
    "on_pushButton_StartCollect_clicked\0"
    "on_pushButton_OpenSerial_clicked\0"
    "on_pushButton_Reset_clicked\0"
    "on_pushButton_setCTRL_clicked\0"
    "on_pushButton_setServerIP_clicked\0"
    "on_pushButton_Reset_2_clicked\0"
    "on_checkBox_clicked\0on_pushButton_wireless_clicked\0"
    "GetCTRL\0ctrl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    1,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Send_clicked(); break;
        case 1: _t->on_pushButton_GetCOM_clicked(); break;
        case 2: _t->on_pushButton_setSampleRate_clicked(); break;
        case 3: _t->on_pushButton_SetDeviceID_clicked(); break;
        case 4: _t->on_pushButton_StartCollect_clicked(); break;
        case 5: _t->on_pushButton_OpenSerial_clicked(); break;
        case 6: _t->on_pushButton_Reset_clicked(); break;
        case 7: _t->on_pushButton_setCTRL_clicked(); break;
        case 8: _t->on_pushButton_setServerIP_clicked(); break;
        case 9: _t->on_pushButton_Reset_2_clicked(); break;
        case 10: _t->on_checkBox_clicked(); break;
        case 11: _t->on_pushButton_wireless_clicked(); break;
        case 12: _t->GetCTRL((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
