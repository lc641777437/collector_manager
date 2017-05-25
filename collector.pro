#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T11:35:09
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += printsupport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = collector
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    uratthread.cpp \
    graphthread.cpp \
    dialog.cpp \
    tcpclientthread.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    uartthread.h \
    graphthread.h \
    dialog.h \
    tcpclientthread.h

FORMS    += mainwindow.ui \
    dialog.ui


