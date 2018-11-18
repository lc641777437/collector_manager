/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
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
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_6;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_SocketConnect;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_SaveData;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *Port;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_GetCOM;
    QPushButton *pushButton_wireless;
    QPushButton *pushButton_SetParam;
    QHBoxLayout *horizontalLayout_11;
    QGridLayout *gridLayout;
    QCustomPlot *widget;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushButton_StartCollect;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(721, 601);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox_10 = new QCheckBox(centralWidget);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        gridLayout_2->addWidget(checkBox_10, 3, 1, 1, 1);

        checkBox_7 = new QCheckBox(centralWidget);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout_2->addWidget(checkBox_7, 1, 2, 1, 1);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_2->addWidget(checkBox_4, 0, 3, 1, 1);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_2->addWidget(checkBox_3, 0, 2, 1, 1);

        checkBox_1 = new QCheckBox(centralWidget);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));

        gridLayout_2->addWidget(checkBox_1, 0, 0, 1, 1);

        checkBox_8 = new QCheckBox(centralWidget);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout_2->addWidget(checkBox_8, 1, 3, 1, 1);

        checkBox_16 = new QCheckBox(centralWidget);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));

        gridLayout_2->addWidget(checkBox_16, 4, 3, 1, 1);

        checkBox_11 = new QCheckBox(centralWidget);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        gridLayout_2->addWidget(checkBox_11, 3, 2, 1, 1);

        checkBox_15 = new QCheckBox(centralWidget);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));

        gridLayout_2->addWidget(checkBox_15, 4, 2, 1, 1);

        checkBox_12 = new QCheckBox(centralWidget);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        gridLayout_2->addWidget(checkBox_12, 3, 3, 1, 1);

        checkBox_9 = new QCheckBox(centralWidget);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout_2->addWidget(checkBox_9, 3, 0, 1, 1);

        checkBox_13 = new QCheckBox(centralWidget);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));

        gridLayout_2->addWidget(checkBox_13, 4, 0, 1, 1);

        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_2->addWidget(checkBox_5, 1, 0, 1, 1);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_14 = new QCheckBox(centralWidget);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));

        gridLayout_2->addWidget(checkBox_14, 4, 1, 1, 1);

        checkBox_6 = new QCheckBox(centralWidget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout_2->addWidget(checkBox_6, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 3, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_SocketConnect = new QPushButton(centralWidget);
        pushButton_SocketConnect->setObjectName(QStringLiteral("pushButton_SocketConnect"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_SocketConnect->sizePolicy().hasHeightForWidth());
        pushButton_SocketConnect->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton_SocketConnect->setFont(font);

        verticalLayout->addWidget(pushButton_SocketConnect);


        gridLayout_3->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_SaveData = new QPushButton(centralWidget);
        pushButton_SaveData->setObjectName(QStringLiteral("pushButton_SaveData"));
        pushButton_SaveData->setEnabled(false);
        pushButton_SaveData->setMinimumSize(QSize(100, 120));
        pushButton_SaveData->setMaximumSize(QSize(100, 200));
        pushButton_SaveData->setFont(font);

        horizontalLayout_2->addWidget(pushButton_SaveData);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 7, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(30, 20));
        label->setFont(font);

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
        pushButton_GetCOM->setFont(font);

        horizontalLayout_10->addWidget(pushButton_GetCOM);


        verticalLayout_2->addLayout(horizontalLayout_10);

        pushButton_wireless = new QPushButton(centralWidget);
        pushButton_wireless->setObjectName(QStringLiteral("pushButton_wireless"));
        pushButton_wireless->setFont(font);

        verticalLayout_2->addWidget(pushButton_wireless);

        pushButton_SetParam = new QPushButton(centralWidget);
        pushButton_SetParam->setObjectName(QStringLiteral("pushButton_SetParam"));
        QFont font1;
        font1.setFamily(QStringLiteral("04b_21"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_SetParam->setFont(font1);

        verticalLayout_2->addWidget(pushButton_SetParam);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));

        verticalLayout_2->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(widget, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 8);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        pushButton_StartCollect = new QPushButton(centralWidget);
        pushButton_StartCollect->setObjectName(QStringLiteral("pushButton_StartCollect"));
        pushButton_StartCollect->setEnabled(false);
        pushButton_StartCollect->setMinimumSize(QSize(100, 120));
        pushButton_StartCollect->setMaximumSize(QSize(100, 200));
        pushButton_StartCollect->setFont(font);

        horizontalLayout_17->addWidget(pushButton_StartCollect);


        gridLayout_3->addLayout(horizontalLayout_17, 1, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        checkBox_10->setText(QApplication::translate("MainWindow", "10", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("MainWindow", "7", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        checkBox_1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        checkBox_8->setText(QApplication::translate("MainWindow", "8", Q_NULLPTR));
        checkBox_16->setText(QApplication::translate("MainWindow", "16", Q_NULLPTR));
        checkBox_11->setText(QApplication::translate("MainWindow", "11", Q_NULLPTR));
        checkBox_15->setText(QApplication::translate("MainWindow", "15", Q_NULLPTR));
        checkBox_12->setText(QApplication::translate("MainWindow", "12", Q_NULLPTR));
        checkBox_9->setText(QApplication::translate("MainWindow", "9", Q_NULLPTR));
        checkBox_13->setText(QApplication::translate("MainWindow", "13", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        checkBox_14->setText(QApplication::translate("MainWindow", "14", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        pushButton_SocketConnect->setText(QApplication::translate("MainWindow", "\345\261\200\345\237\237 \n"
"\347\275\221\347\273\234\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_SaveData->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\277\235\345\255\230", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "COM", Q_NULLPTR));
        pushButton_GetCOM->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\344\270\262\345\217\243", Q_NULLPTR));
        pushButton_wireless->setText(QApplication::translate("MainWindow", "\346\227\240\347\272\277\344\270\262\345\217\243", Q_NULLPTR));
        pushButton_SetParam->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_StartCollect->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
