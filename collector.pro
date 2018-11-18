#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T12:15:29
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
    graphthread.cpp \
    tcpclientthread.cpp \
    dialog.cpp \
    uratthread.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    graphthread.h \
    dialog.h \
    uartthread.h \
    tcpclientthread.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dialog.ui

RC_FILE += myico.rc
