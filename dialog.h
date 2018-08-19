#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class MainWindow;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, unsigned char devIDH, unsigned char devIDL, unsigned char ctrlH, unsigned char ctrlL,\
                    unsigned char fre, unsigned char sendTimeServer, unsigned char sendTimeDynamic,QString _proId,QString _proName, \
                    QString _testPointName[]);
    ~Dialog();
    MainWindow  *pMainWindow;
    bool isReject;
    unsigned char pDevIDH;
    unsigned char pDevIDL;              // deviceID设备ID
    unsigned char pCtrlH;
    unsigned char pCtrlL;               // 采样类型
    unsigned char pFre;                 // 采样频率
    unsigned char pSendTimeServer;      // 服务器发送间隔
    unsigned char pSendTimeDynamic;     // 触发态发送间隔

    QString ProjectID;                  // 工程流水号
    QString proId;        //  下传到设备的工程流水号
    QString proName;      //  下传到设备的项目名称
    QString testPointName[16];    //  测试点的名称

    char last_baseValue;       // 记录上一次的基准值
    QTimer *oneMinuteTimer;    // 定时1分钟采集数据
    QMessageBox* msgBox;       // 提示等待一分钟
    int cnt;                   // 计时60s
    bool isSelected[20];

    // 报警阈值
    int redLine;
    int orangeLine;

private:
    Ui::Dialog *ui;
    // 辅助函数系列
    void help_setP(QString s,bool isMax);
    void help_readP();
    void help_setChannel(bool a[]);      // 设置通道数
    void help_setTestName(QString s);    // 设置测试点名称
    void help_setH(QString s);           // 设置H初值
    void help_setBase(QString s);        // 设置基准点
    bool help_saveParam();               // 保存参数
public slots:
    virtual void accept();          // ok 按钮响应函数
    virtual void reject();          // cancel 按钮响应函数
    virtual void handlerTimerOut();
signals:
    void SendCTRL(int ctrl);         // 发送采样类型触发器

private slots:
    void on_pushButton_selectFile_clicked();
    void on_pushButton_Reset_2_clicked();
    void on_comboBox_SaveDataDynamic_activated(const QString &arg1);
    void on_pushButton_readH0_clicked();
    void on_checkBox_BaseValue_clicked();
    void on_checkBox_ChannelSelected_clicked();
    void on_pushButton_saveParam_clicked();

    // 单选按钮选中
    void on_Pbtn_11_clicked();
    void on_Pbtn_12_clicked();
    void on_Pbtn_13_clicked();

    void on_Pbtn_21_clicked();
    void on_Pbtn_22_clicked();
    void on_Pbtn_23_clicked();

    void on_Pbtn_31_clicked();
    void on_Pbtn_32_clicked();
    void on_Pbtn_33_clicked();

    void on_Pbtn_41_clicked();
    void on_Pbtn_42_clicked();
    void on_Pbtn_43_clicked();

    void on_Pbtn_51_clicked();
    void on_Pbtn_52_clicked();
    void on_Pbtn_53_clicked();

    void on_Pbtn_61_clicked();
    void on_Pbtn_62_clicked();
    void on_Pbtn_63_clicked();

    void on_Pbtn_71_clicked();
    void on_Pbtn_72_clicked();
    void on_Pbtn_73_clicked();

    void on_Pbtn_81_clicked();
    void on_Pbtn_82_clicked();
    void on_Pbtn_83_clicked();

    void on_Pbtn_91_clicked();
    void on_Pbtn_92_clicked();
    void on_Pbtn_93_clicked();

    void on_Pbtn_a1_clicked();
    void on_Pbtn_a2_clicked();
    void on_Pbtn_a3_clicked();

    void on_Pbtn_b1_clicked();
    void on_Pbtn_b2_clicked();
    void on_Pbtn_b3_clicked();

    void on_Pbtn_c1_clicked();
    void on_Pbtn_c2_clicked();
    void on_Pbtn_c3_clicked();

    void on_Pbtn_d1_clicked();
    void on_Pbtn_d2_clicked();
    void on_Pbtn_d3_clicked();

    void on_Pbtn_e1_clicked();
    void on_Pbtn_e2_clicked();
    void on_Pbtn_e3_clicked();

    void on_Pbtn_f1_clicked();
    void on_Pbtn_f2_clicked();
    void on_Pbtn_f3_clicked();

    void on_Pbtn_g1_clicked();
    void on_Pbtn_g2_clicked();
    void on_Pbtn_g3_clicked();


    void on_comboBox_range1_currentIndexChanged(const QString &arg1);
    void on_comboBox_range2_currentTextChanged(const QString &arg1);
    void on_comboBox_range3_currentTextChanged(const QString &arg1);
    void on_comboBox_range4_currentTextChanged(const QString &arg1);
    void on_comboBox_range5_currentTextChanged(const QString &arg1);
    void on_comboBox_range6_currentTextChanged(const QString &arg1);
    void on_comboBox_range7_currentTextChanged(const QString &arg1);
    void on_comboBox_range8_currentTextChanged(const QString &arg1);
    void on_comboBox_range9_currentTextChanged(const QString &arg1);
    void on_comboBox_range10_currentTextChanged(const QString &arg1);
    void on_comboBox_range11_currentTextChanged(const QString &arg1);
    void on_comboBox_range12_currentTextChanged(const QString &arg1);
    void on_comboBox_range13_currentTextChanged(const QString &arg1);
    void on_comboBox_range14_currentTextChanged(const QString &arg1);
    void on_comboBox_range15_currentTextChanged(const QString &arg1);
    void on_comboBox_range16_currentTextChanged(const QString &arg1);
};

#endif // DIALOG_H
