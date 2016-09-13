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
#include <QtWidgets/QPlainTextEdit>
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
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_20;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_Send;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_21;
    QSpacerItem *horizontalSpacer_3;
    QCustomPlot *widget;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *pushButton_Reset;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *Port;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *Bound;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *Check;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *Data;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *Stop;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_GetCOM;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_OpenSerial;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *check_newLine;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButton_ClearText;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QComboBox *comboBox_SampleRate;
    QLabel *label_6;
    QPushButton *pushButton_setSampleRate;
    QPushButton *pushButton_SetDeviceID;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushButton_StartCollect;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QComboBox *comboBoxChannal;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *Input;
    QPlainTextEdit *TextPlain;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(732, 478);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_20, 2, 5, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButton_Send = new QPushButton(centralWidget);
        pushButton_Send->setObjectName(QStringLiteral("pushButton_Send"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_Send->sizePolicy().hasHeightForWidth());
        pushButton_Send->setSizePolicy(sizePolicy);
        pushButton_Send->setMaximumSize(QSize(80, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(9);
        pushButton_Send->setFont(font);

        horizontalLayout_8->addWidget(pushButton_Send);


        gridLayout->addLayout(horizontalLayout_8, 2, 2, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_15, 2, 3, 1, 1);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_21, 2, 4, 1, 1);

        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(widget, 0, 1, 1, 5);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        pushButton_Reset = new QPushButton(centralWidget);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setEnabled(false);
        pushButton_Reset->setMinimumSize(QSize(100, 120));
        pushButton_Reset->setMaximumSize(QSize(100, 200));

        horizontalLayout_16->addWidget(pushButton_Reset);


        gridLayout->addLayout(horizontalLayout_16, 1, 5, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(12);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        Port = new QComboBox(centralWidget);
        Port->setObjectName(QStringLiteral("Port"));
        Port->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(Port);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(50, 20));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        Bound = new QComboBox(centralWidget);
        Bound->setObjectName(QStringLiteral("Bound"));
        Bound->setMaximumSize(QSize(60, 20));
        Bound->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_2->addWidget(Bound);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(50, 20));
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        Check = new QComboBox(centralWidget);
        Check->setObjectName(QStringLiteral("Check"));
        Check->setMaximumSize(QSize(60, 20));

        horizontalLayout_3->addWidget(Check);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(50, 20));
        label_4->setFont(font1);

        horizontalLayout_4->addWidget(label_4);

        Data = new QComboBox(centralWidget);
        Data->setObjectName(QStringLiteral("Data"));
        Data->setMaximumSize(QSize(60, 20));

        horizontalLayout_4->addWidget(Data);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(50, 20));
        label_5->setFont(font1);

        horizontalLayout_5->addWidget(label_5);

        Stop = new QComboBox(centralWidget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setMaximumSize(QSize(60, 20));

        horizontalLayout_5->addWidget(Stop);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton_GetCOM = new QPushButton(centralWidget);
        pushButton_GetCOM->setObjectName(QStringLiteral("pushButton_GetCOM"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        pushButton_GetCOM->setFont(font2);

        horizontalLayout_10->addWidget(pushButton_GetCOM);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        pushButton_OpenSerial = new QPushButton(centralWidget);
        pushButton_OpenSerial->setObjectName(QStringLiteral("pushButton_OpenSerial"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font3.setPointSize(9);
        pushButton_OpenSerial->setFont(font3);

        horizontalLayout_11->addWidget(pushButton_OpenSerial);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_11);

        check_newLine = new QCheckBox(centralWidget);
        check_newLine->setObjectName(QStringLiteral("check_newLine"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        check_newLine->setFont(font4);

        verticalLayout_2->addWidget(check_newLine);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        pushButton_ClearText = new QPushButton(centralWidget);
        pushButton_ClearText->setObjectName(QStringLiteral("pushButton_ClearText"));
        sizePolicy.setHeightForWidth(pushButton_ClearText->sizePolicy().hasHeightForWidth());
        pushButton_ClearText->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font5.setPointSize(10);
        pushButton_ClearText->setFont(font5);

        horizontalLayout_12->addWidget(pushButton_ClearText);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_12);


        horizontalLayout_6->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_19, 1, 3, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setSizeConstraint(QLayout::SetDefaultConstraint);
        comboBox_SampleRate = new QComboBox(centralWidget);
        comboBox_SampleRate->setObjectName(QStringLiteral("comboBox_SampleRate"));
        comboBox_SampleRate->setMaximumSize(QSize(50, 20));

        horizontalLayout_18->addWidget(comboBox_SampleRate);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(20, 20));

        horizontalLayout_18->addWidget(label_6);


        verticalLayout_5->addLayout(horizontalLayout_18);

        pushButton_setSampleRate = new QPushButton(centralWidget);
        pushButton_setSampleRate->setObjectName(QStringLiteral("pushButton_setSampleRate"));
        pushButton_setSampleRate->setEnabled(false);
        pushButton_setSampleRate->setMaximumSize(QSize(70, 20));

        verticalLayout_5->addWidget(pushButton_setSampleRate);

        pushButton_SetDeviceID = new QPushButton(centralWidget);
        pushButton_SetDeviceID->setObjectName(QStringLiteral("pushButton_SetDeviceID"));
        pushButton_SetDeviceID->setEnabled(false);
        pushButton_SetDeviceID->setMaximumSize(QSize(70, 20));

        verticalLayout_5->addWidget(pushButton_SetDeviceID);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout_13->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout_13, 1, 1, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        pushButton_StartCollect = new QPushButton(centralWidget);
        pushButton_StartCollect->setObjectName(QStringLiteral("pushButton_StartCollect"));
        pushButton_StartCollect->setEnabled(false);
        pushButton_StartCollect->setMinimumSize(QSize(100, 120));
        pushButton_StartCollect->setMaximumSize(QSize(100, 200));

        horizontalLayout_17->addWidget(pushButton_StartCollect);


        gridLayout->addLayout(horizontalLayout_17, 1, 4, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(70, 20));
        label_7->setTextFormat(Qt::AutoText);

        verticalLayout_3->addWidget(label_7);

        comboBoxChannal = new QComboBox(centralWidget);
        comboBoxChannal->setObjectName(QStringLiteral("comboBoxChannal"));
        comboBoxChannal->setMaximumSize(QSize(70, 20));

        verticalLayout_3->addWidget(comboBoxChannal);

        verticalSpacer_2 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_7->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_7, 1, 2, 1, 1);

        Input = new QLineEdit(centralWidget);
        Input->setObjectName(QStringLiteral("Input"));
        Input->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout->addWidget(Input, 2, 0, 1, 2);

        TextPlain = new QPlainTextEdit(centralWidget);
        TextPlain->setObjectName(QStringLiteral("TextPlain"));
        TextPlain->setMaximumSize(QSize(1677725, 16777215));
        TextPlain->setAutoFillBackground(true);
        TextPlain->setLineWidth(25);
        TextPlain->setMidLineWidth(0);
        TextPlain->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        TextPlain->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        TextPlain->setReadOnly(true);

        gridLayout->addWidget(TextPlain, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        TextPlain->raise();
        widget->raise();
        Input->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_Send->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0));
        pushButton_Reset->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\351\207\207\351\233\206", 0));
        label->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", 0));
        Bound->clear();
        Bound->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "110", 0)
         << QApplication::translate("MainWindow", "300", 0)
         << QApplication::translate("MainWindow", "600", 0)
         << QApplication::translate("MainWindow", "1200", 0)
         << QApplication::translate("MainWindow", "2400", 0)
         << QApplication::translate("MainWindow", "4800", 0)
         << QApplication::translate("MainWindow", "9600", 0)
         << QApplication::translate("MainWindow", "14400", 0)
         << QApplication::translate("MainWindow", "19200", 0)
         << QApplication::translate("MainWindow", "38400", 0)
         << QApplication::translate("MainWindow", "56000", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "128000", 0)
         << QApplication::translate("MainWindow", "256000", 0)
         << QApplication::translate("MainWindow", "921600", 0)
        );
        label_3->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", 0));
        Check->clear();
        Check->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "NONE", 0)
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", 0));
        Data->clear();
        Data->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "6", 0)
        );
        label_5->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", 0));
        Stop->clear();
        Stop->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
        );
        pushButton_GetCOM->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\344\270\262\345\217\243", 0));
        pushButton_OpenSerial->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
        check_newLine->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\260\350\241\214", 0));
        pushButton_ClearText->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244\346\230\276\347\244\272", 0));
        comboBox_SampleRate->clear();
        comboBox_SampleRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "200", 0)
         << QApplication::translate("MainWindow", "100", 0)
         << QApplication::translate("MainWindow", "150", 0)
         << QApplication::translate("MainWindow", "50", 0)
         << QApplication::translate("MainWindow", "25", 0)
         << QApplication::translate("MainWindow", "10", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "1", 0)
        );
        label_6->setText(QApplication::translate("MainWindow", "Hz", 0));
        pushButton_setSampleRate->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\207\207\346\240\267\347\216\207", 0));
        pushButton_SetDeviceID->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\256\276\345\244\207\345\217\267", 0));
        pushButton_StartCollect->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", 0));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\346\263\242\345\275\242\351\200\232\351\201\223</p></body></html>", 0));
        comboBoxChannal->clear();
        comboBoxChannal->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "9", 0)
         << QApplication::translate("MainWindow", "10", 0)
         << QApplication::translate("MainWindow", "11", 0)
         << QApplication::translate("MainWindow", "12", 0)
         << QApplication::translate("MainWindow", "13", 0)
         << QApplication::translate("MainWindow", "14", 0)
         << QApplication::translate("MainWindow", "15", 0)
         << QApplication::translate("MainWindow", "16", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
