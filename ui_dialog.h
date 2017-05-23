/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QComboBox *comboBox_8;
    QComboBox *comboBox_9;
    QComboBox *comboBox_10;
    QComboBox *comboBox_11;
    QComboBox *comboBox_12;
    QComboBox *comboBox_13;
    QComboBox *comboBox_14;
    QComboBox *comboBox_15;
    QComboBox *comboBox_16;
    QLineEdit *lineEdit_DevID;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QComboBox *comboBox_SampleRte;
    QLabel *label_20;
    QComboBox *comboBox_SendTime2erver;
    QLabel *label_21;
    QComboBox *comboBox_SendTimeDynamic;
    QLabel *label__Message;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setEnabled(true);
        Dialog->resize(370, 503);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 440, 351, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 90, 51, 20));
        comboBox->setMaximumSize(QSize(60, 20));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 90, 20, 20));
        label->setMaximumSize(QSize(20, 20));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 90, 20, 20));
        label_2->setMaximumSize(QSize(20, 20));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 90, 20, 20));
        label_3->setMaximumSize(QSize(20, 20));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 90, 20, 20));
        label_4->setMaximumSize(QSize(20, 20));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 140, 20, 20));
        label_5->setMaximumSize(QSize(20, 20));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(100, 140, 20, 20));
        label_6->setMaximumSize(QSize(20, 20));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 140, 20, 20));
        label_7->setMaximumSize(QSize(20, 20));
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 140, 20, 20));
        label_8->setMaximumSize(QSize(20, 20));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 190, 20, 20));
        label_9->setMaximumSize(QSize(20, 20));
        label_10 = new QLabel(Dialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(100, 190, 20, 20));
        label_10->setMaximumSize(QSize(20, 20));
        label_11 = new QLabel(Dialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(190, 190, 20, 20));
        label_11->setMaximumSize(QSize(20, 20));
        label_12 = new QLabel(Dialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(280, 190, 20, 20));
        label_12->setMaximumSize(QSize(20, 20));
        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 240, 20, 20));
        label_13->setMaximumSize(QSize(20, 20));
        label_14 = new QLabel(Dialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(100, 240, 20, 20));
        label_14->setMaximumSize(QSize(20, 20));
        label_15 = new QLabel(Dialog);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(190, 240, 20, 20));
        label_15->setMaximumSize(QSize(20, 20));
        label_16 = new QLabel(Dialog);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(280, 240, 20, 20));
        label_16->setMaximumSize(QSize(20, 20));
        comboBox_2 = new QComboBox(Dialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(120, 90, 51, 20));
        comboBox_2->setMaximumSize(QSize(60, 20));
        comboBox_3 = new QComboBox(Dialog);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(210, 90, 51, 20));
        comboBox_3->setMaximumSize(QSize(60, 20));
        comboBox_4 = new QComboBox(Dialog);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setGeometry(QRect(300, 90, 51, 20));
        comboBox_4->setMaximumSize(QSize(60, 20));
        comboBox_5 = new QComboBox(Dialog);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        comboBox_5->setGeometry(QRect(30, 140, 51, 20));
        comboBox_5->setMaximumSize(QSize(60, 20));
        comboBox_6 = new QComboBox(Dialog);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));
        comboBox_6->setGeometry(QRect(120, 140, 51, 20));
        comboBox_6->setMaximumSize(QSize(60, 20));
        comboBox_7 = new QComboBox(Dialog);
        comboBox_7->setObjectName(QStringLiteral("comboBox_7"));
        comboBox_7->setGeometry(QRect(210, 140, 51, 20));
        comboBox_7->setMaximumSize(QSize(60, 20));
        comboBox_8 = new QComboBox(Dialog);
        comboBox_8->setObjectName(QStringLiteral("comboBox_8"));
        comboBox_8->setGeometry(QRect(300, 140, 51, 20));
        comboBox_8->setMaximumSize(QSize(60, 20));
        comboBox_9 = new QComboBox(Dialog);
        comboBox_9->setObjectName(QStringLiteral("comboBox_9"));
        comboBox_9->setGeometry(QRect(30, 190, 51, 20));
        comboBox_9->setMaximumSize(QSize(60, 20));
        comboBox_10 = new QComboBox(Dialog);
        comboBox_10->setObjectName(QStringLiteral("comboBox_10"));
        comboBox_10->setGeometry(QRect(120, 190, 51, 20));
        comboBox_10->setMaximumSize(QSize(60, 20));
        comboBox_11 = new QComboBox(Dialog);
        comboBox_11->setObjectName(QStringLiteral("comboBox_11"));
        comboBox_11->setGeometry(QRect(210, 190, 51, 20));
        comboBox_11->setMaximumSize(QSize(60, 20));
        comboBox_12 = new QComboBox(Dialog);
        comboBox_12->setObjectName(QStringLiteral("comboBox_12"));
        comboBox_12->setGeometry(QRect(300, 190, 51, 20));
        comboBox_12->setMaximumSize(QSize(60, 20));
        comboBox_13 = new QComboBox(Dialog);
        comboBox_13->setObjectName(QStringLiteral("comboBox_13"));
        comboBox_13->setGeometry(QRect(30, 240, 51, 20));
        comboBox_13->setMaximumSize(QSize(60, 20));
        comboBox_14 = new QComboBox(Dialog);
        comboBox_14->setObjectName(QStringLiteral("comboBox_14"));
        comboBox_14->setGeometry(QRect(120, 240, 51, 20));
        comboBox_14->setMaximumSize(QSize(60, 20));
        comboBox_15 = new QComboBox(Dialog);
        comboBox_15->setObjectName(QStringLiteral("comboBox_15"));
        comboBox_15->setGeometry(QRect(210, 240, 51, 20));
        comboBox_15->setMaximumSize(QSize(60, 20));
        comboBox_16 = new QComboBox(Dialog);
        comboBox_16->setObjectName(QStringLiteral("comboBox_16"));
        comboBox_16->setGeometry(QRect(300, 240, 51, 20));
        comboBox_16->setMaximumSize(QSize(60, 20));
        lineEdit_DevID = new QLineEdit(Dialog);
        lineEdit_DevID->setObjectName(QStringLiteral("lineEdit_DevID"));
        lineEdit_DevID->setGeometry(QRect(70, 30, 241, 20));
        label_17 = new QLabel(Dialog);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(0, 0, 361, 31));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignCenter);
        label_18 = new QLabel(Dialog);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(0, 60, 361, 21));
        label_18->setFont(font);
        label_18->setAlignment(Qt::AlignCenter);
        label_19 = new QLabel(Dialog);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(0, 270, 361, 21));
        label_19->setFont(font);
        label_19->setAlignment(Qt::AlignCenter);
        comboBox_SampleRte = new QComboBox(Dialog);
        comboBox_SampleRte->setObjectName(QStringLiteral("comboBox_SampleRte"));
        comboBox_SampleRte->setGeometry(QRect(140, 290, 69, 22));
        label_20 = new QLabel(Dialog);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(0, 330, 361, 21));
        label_20->setFont(font);
        label_20->setAlignment(Qt::AlignCenter);
        comboBox_SendTime2erver = new QComboBox(Dialog);
        comboBox_SendTime2erver->setObjectName(QStringLiteral("comboBox_SendTime2erver"));
        comboBox_SendTime2erver->setGeometry(QRect(140, 350, 69, 22));
        label_21 = new QLabel(Dialog);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(0, 390, 361, 21));
        label_21->setFont(font);
        label_21->setAlignment(Qt::AlignCenter);
        comboBox_SendTimeDynamic = new QComboBox(Dialog);
        comboBox_SendTimeDynamic->setObjectName(QStringLiteral("comboBox_SendTimeDynamic"));
        comboBox_SendTimeDynamic->setGeometry(QRect(140, 410, 69, 22));
        label__Message = new QLabel(Dialog);
        label__Message->setObjectName(QStringLiteral("label__Message"));
        label__Message->setGeometry(QRect(0, 480, 371, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(12);
        label__Message->setFont(font1);
        label__Message->setAlignment(Qt::AlignCenter);
        label_23 = new QLabel(Dialog);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(210, 290, 31, 21));
        label_23->setAlignment(Qt::AlignCenter);
        label_24 = new QLabel(Dialog);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(210, 350, 31, 21));
        label_24->setAlignment(Qt::AlignCenter);
        label_25 = new QLabel(Dialog);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(210, 410, 31, 21));
        label_25->setAlignment(Qt::AlignCenter);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        label->setText(QApplication::translate("Dialog", "1", 0));
        label_2->setText(QApplication::translate("Dialog", "2", 0));
        label_3->setText(QApplication::translate("Dialog", "3", 0));
        label_4->setText(QApplication::translate("Dialog", "4", 0));
        label_5->setText(QApplication::translate("Dialog", "5", 0));
        label_6->setText(QApplication::translate("Dialog", "6", 0));
        label_7->setText(QApplication::translate("Dialog", "7", 0));
        label_8->setText(QApplication::translate("Dialog", "8", 0));
        label_9->setText(QApplication::translate("Dialog", "9", 0));
        label_10->setText(QApplication::translate("Dialog", "10", 0));
        label_11->setText(QApplication::translate("Dialog", "11", 0));
        label_12->setText(QApplication::translate("Dialog", "12", 0));
        label_13->setText(QApplication::translate("Dialog", "13", 0));
        label_14->setText(QApplication::translate("Dialog", "14", 0));
        label_15->setText(QApplication::translate("Dialog", "15", 0));
        label_16->setText(QApplication::translate("Dialog", "16", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_6->clear();
        comboBox_6->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_7->clear();
        comboBox_7->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_8->clear();
        comboBox_8->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_9->clear();
        comboBox_9->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_10->clear();
        comboBox_10->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_11->clear();
        comboBox_11->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_12->clear();
        comboBox_12->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_13->clear();
        comboBox_13->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_14->clear();
        comboBox_14->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_15->clear();
        comboBox_15->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        comboBox_16->clear();
        comboBox_16->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\224\265\345\216\213", 0)
         << QApplication::translate("Dialog", "\347\224\265\346\265\201", 0)
        );
        label_17->setText(QApplication::translate("Dialog", "\350\256\276\345\244\207ID", 0));
        label_18->setText(QApplication::translate("Dialog", "\351\207\207\346\240\267\347\261\273\345\236\213", 0));
        label_19->setText(QApplication::translate("Dialog", "\351\207\207\346\240\267\351\242\221\347\216\207", 0));
        comboBox_SampleRte->clear();
        comboBox_SampleRte->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "200", 0)
         << QApplication::translate("Dialog", "100", 0)
         << QApplication::translate("Dialog", "50", 0)
         << QApplication::translate("Dialog", "20", 0)
         << QApplication::translate("Dialog", "10", 0)
         << QApplication::translate("Dialog", "5", 0)
         << QApplication::translate("Dialog", "2", 0)
         << QApplication::translate("Dialog", "1", 0)
        );
        label_20->setText(QApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\345\217\221\351\200\201\351\227\264\351\232\224(\345\210\206)", 0));
        comboBox_SendTime2erver->clear();
        comboBox_SendTime2erver->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "1", 0)
         << QApplication::translate("Dialog", "2", 0)
         << QApplication::translate("Dialog", "5", 0)
         << QApplication::translate("Dialog", "10", 0)
         << QApplication::translate("Dialog", "20", 0)
         << QApplication::translate("Dialog", "30", 0)
        );
        label_21->setText(QApplication::translate("Dialog", "\350\247\246\345\217\221\346\200\201\345\217\221\351\200\201\351\227\264\351\232\224(\347\247\222)", 0));
        comboBox_SendTimeDynamic->clear();
        comboBox_SendTimeDynamic->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "1", 0)
         << QApplication::translate("Dialog", "2", 0)
         << QApplication::translate("Dialog", "5", 0)
         << QApplication::translate("Dialog", "10", 0)
         << QApplication::translate("Dialog", "20", 0)
         << QApplication::translate("Dialog", "30", 0)
        );
        label__Message->setText(QString());
        label_23->setText(QApplication::translate("Dialog", "Hz", 0));
        label_24->setText(QApplication::translate("Dialog", "\345\210\206", 0));
        label_25->setText(QApplication::translate("Dialog", "\347\247\222", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
