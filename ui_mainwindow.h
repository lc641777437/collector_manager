/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QCustomPlot *widget;
    QCustomPlot *widget_2;
    QCustomPlot *widget_3;
    QCustomPlot *widget_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_setSampleRate;
    QPushButton *pushButton_SetDeviceID;
    QPushButton *pushButton_setCTRL;
    QPushButton *pushButton_setServerIP;
    QPushButton *pushButton_Reset_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Send;
    QLineEdit *Input;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *Port;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_GetCOM;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_wireless;
    QPushButton *pushButton_OpenSerial;
    QCheckBox *check_newLine;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_Reset;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushButton_StartCollect;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(730, 478);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(widget, 0, 1, 1, 1);

        widget_2 = new QCustomPlot(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setEnabled(false);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(widget_2, 0, 2, 1, 1);

        widget_3 = new QCustomPlot(centralWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setEnabled(false);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(widget_3, 1, 1, 1, 1);

        widget_4 = new QCustomPlot(centralWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setEnabled(false);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(widget_4, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 9);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        pushButton_setSampleRate = new QPushButton(centralWidget);
        pushButton_setSampleRate->setObjectName(QStringLiteral("pushButton_setSampleRate"));
        pushButton_setSampleRate->setEnabled(false);
        pushButton_setSampleRate->setMaximumSize(QSize(75, 20));

        verticalLayout_5->addWidget(pushButton_setSampleRate);

        pushButton_SetDeviceID = new QPushButton(centralWidget);
        pushButton_SetDeviceID->setObjectName(QStringLiteral("pushButton_SetDeviceID"));
        pushButton_SetDeviceID->setEnabled(false);
        pushButton_SetDeviceID->setMaximumSize(QSize(75, 20));

        verticalLayout_5->addWidget(pushButton_SetDeviceID);

        pushButton_setCTRL = new QPushButton(centralWidget);
        pushButton_setCTRL->setObjectName(QStringLiteral("pushButton_setCTRL"));
        pushButton_setCTRL->setEnabled(false);
        pushButton_setCTRL->setMaximumSize(QSize(75, 20));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(8);
        pushButton_setCTRL->setFont(font);

        verticalLayout_5->addWidget(pushButton_setCTRL);

        pushButton_setServerIP = new QPushButton(centralWidget);
        pushButton_setServerIP->setObjectName(QStringLiteral("pushButton_setServerIP"));
        pushButton_setServerIP->setEnabled(false);
        pushButton_setServerIP->setMaximumSize(QSize(75, 20));

        verticalLayout_5->addWidget(pushButton_setServerIP);

        pushButton_Reset_2 = new QPushButton(centralWidget);
        pushButton_Reset_2->setObjectName(QStringLiteral("pushButton_Reset_2"));
        pushButton_Reset_2->setEnabled(false);
        pushButton_Reset_2->setMaximumSize(QSize(75, 20));
        pushButton_Reset_2->setFont(font);

        verticalLayout_5->addWidget(pushButton_Reset_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer);


        gridLayout_3->addLayout(verticalLayout_5, 1, 1, 1, 1);

        pushButton_Send = new QPushButton(centralWidget);
        pushButton_Send->setObjectName(QStringLiteral("pushButton_Send"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_Send->sizePolicy().hasHeightForWidth());
        pushButton_Send->setSizePolicy(sizePolicy1);
        pushButton_Send->setMaximumSize(QSize(80, 16777215));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(9);
        pushButton_Send->setFont(font1);

        gridLayout_3->addWidget(pushButton_Send, 2, 3, 1, 1);

        Input = new QLineEdit(centralWidget);
        Input->setObjectName(QStringLiteral("Input"));
        Input->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout_3->addWidget(Input, 2, 0, 1, 3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(20, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Agency FB"));
        font2.setPointSize(12);
        label->setFont(font2);

        horizontalLayout->addWidget(label);

        Port = new QComboBox(centralWidget);
        Port->setObjectName(QStringLiteral("Port"));
        Port->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(Port);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton_GetCOM = new QPushButton(centralWidget);
        pushButton_GetCOM->setObjectName(QStringLiteral("pushButton_GetCOM"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        pushButton_GetCOM->setFont(font3);

        horizontalLayout_10->addWidget(pushButton_GetCOM);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        pushButton_wireless = new QPushButton(centralWidget);
        pushButton_wireless->setObjectName(QStringLiteral("pushButton_wireless"));
        pushButton_wireless->setFont(font);

        horizontalLayout_11->addWidget(pushButton_wireless);

        pushButton_OpenSerial = new QPushButton(centralWidget);
        pushButton_OpenSerial->setObjectName(QStringLiteral("pushButton_OpenSerial"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font4.setPointSize(9);
        pushButton_OpenSerial->setFont(font4);

        horizontalLayout_11->addWidget(pushButton_OpenSerial);


        verticalLayout_2->addLayout(horizontalLayout_11);

        check_newLine = new QCheckBox(centralWidget);
        check_newLine->setObjectName(QStringLiteral("check_newLine"));
        check_newLine->setMaximumSize(QSize(130, 16777215));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font5.setPointSize(14);
        font5.setBold(true);
        font5.setWeight(75);
        check_newLine->setFont(font5);

        verticalLayout_2->addWidget(check_newLine);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout_6, 2, 4, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout_5, 2, 8, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_Reset = new QPushButton(centralWidget);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setEnabled(false);
        pushButton_Reset->setMinimumSize(QSize(100, 120));
        pushButton_Reset->setMaximumSize(QSize(100, 200));

        horizontalLayout_2->addWidget(pushButton_Reset);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 8, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 7, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        pushButton_StartCollect = new QPushButton(centralWidget);
        pushButton_StartCollect->setObjectName(QStringLiteral("pushButton_StartCollect"));
        pushButton_StartCollect->setEnabled(false);
        pushButton_StartCollect->setMinimumSize(QSize(100, 120));
        pushButton_StartCollect->setMaximumSize(QSize(100, 200));

        horizontalLayout_17->addWidget(pushButton_StartCollect);


        gridLayout_3->addLayout(horizontalLayout_17, 1, 7, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 4, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox_1 = new QCheckBox(centralWidget);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));

        gridLayout_2->addWidget(checkBox_1, 0, 0, 1, 1);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_2->addWidget(checkBox_3, 0, 2, 1, 1);

        checkBox_10 = new QCheckBox(centralWidget);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        gridLayout_2->addWidget(checkBox_10, 2, 1, 1, 1);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_2->addWidget(checkBox_4, 0, 3, 1, 1);

        checkBox_7 = new QCheckBox(centralWidget);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout_2->addWidget(checkBox_7, 1, 2, 1, 1);

        checkBox_8 = new QCheckBox(centralWidget);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout_2->addWidget(checkBox_8, 1, 3, 1, 1);

        checkBox_15 = new QCheckBox(centralWidget);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));

        gridLayout_2->addWidget(checkBox_15, 3, 2, 1, 1);

        checkBox_16 = new QCheckBox(centralWidget);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));

        gridLayout_2->addWidget(checkBox_16, 3, 3, 1, 1);

        checkBox_11 = new QCheckBox(centralWidget);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        gridLayout_2->addWidget(checkBox_11, 2, 2, 1, 1);

        checkBox_12 = new QCheckBox(centralWidget);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        gridLayout_2->addWidget(checkBox_12, 2, 3, 1, 1);

        checkBox_14 = new QCheckBox(centralWidget);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));

        gridLayout_2->addWidget(checkBox_14, 3, 1, 1, 1);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_2->addWidget(checkBox_5, 1, 0, 1, 1);

        checkBox_9 = new QCheckBox(centralWidget);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout_2->addWidget(checkBox_9, 2, 0, 1, 1);

        checkBox_13 = new QCheckBox(centralWidget);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));

        gridLayout_2->addWidget(checkBox_13, 3, 0, 1, 1);

        checkBox_6 = new QCheckBox(centralWidget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout_2->addWidget(checkBox_6, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 2, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        Input->raise();
        pushButton_Send->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_setSampleRate->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\207\207\346\240\267\347\216\207", 0));
        pushButton_SetDeviceID->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\256\276\345\244\207\345\217\267", 0));
        pushButton_setCTRL->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\207\207\346\240\267\347\261\273\345\236\213", 0));
        pushButton_setServerIP->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\234\215\345\212\241\345\231\250", 0));
        pushButton_Reset_2->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", 0));
        pushButton_Send->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0));
        label->setText(QApplication::translate("MainWindow", "COM", 0));
        pushButton_GetCOM->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\344\270\262\345\217\243", 0));
        pushButton_wireless->setText(QApplication::translate("MainWindow", "\346\227\240\347\272\277\344\270\262\345\217\243", 0));
        pushButton_OpenSerial->setText(QApplication::translate("MainWindow", "\346\234\211\347\272\277\344\270\262\345\217\243", 0));
        check_newLine->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\260\350\241\214", 0));
        pushButton_Reset->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\351\207\207\351\233\206", 0));
        pushButton_StartCollect->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", 0));
        checkBox_1->setText(QApplication::translate("MainWindow", "1", 0));
        checkBox_3->setText(QApplication::translate("MainWindow", "3", 0));
        checkBox_10->setText(QApplication::translate("MainWindow", "10", 0));
        checkBox_4->setText(QApplication::translate("MainWindow", "4", 0));
        checkBox_7->setText(QApplication::translate("MainWindow", "7", 0));
        checkBox_8->setText(QApplication::translate("MainWindow", "8", 0));
        checkBox_15->setText(QApplication::translate("MainWindow", "15", 0));
        checkBox_16->setText(QApplication::translate("MainWindow", "16", 0));
        checkBox_11->setText(QApplication::translate("MainWindow", "11", 0));
        checkBox_12->setText(QApplication::translate("MainWindow", "12", 0));
        checkBox_14->setText(QApplication::translate("MainWindow", "14", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "2", 0));
        checkBox_5->setText(QApplication::translate("MainWindow", "5", 0));
        checkBox_9->setText(QApplication::translate("MainWindow", "9", 0));
        checkBox_13->setText(QApplication::translate("MainWindow", "13", 0));
        checkBox_6->setText(QApplication::translate("MainWindow", "6", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
