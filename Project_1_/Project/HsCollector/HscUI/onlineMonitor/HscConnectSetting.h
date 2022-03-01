#ifndef HSCCONNECTSETTING_H
#define HSCCONNECTSETTING_H

#include <QWidget>

#include "QMQTT.h"

namespace Ui {
class HscConnectSetting;
}

class HscConnectSetting : public QWidget
{
    Q_OBJECT

public:
    explicit HscConnectSetting(QWidget *parent = nullptr);
    ~HscConnectSetting();

private slots:
    void on_testConnectPB_clicked();

public:
    void saveSetting();

private:
    void initView();
    void loadModelData();

private:
    Ui::HscConnectSetting *ui;

    QMQTT *m_mqtt = nullptr;
    bool m_connected = false;
};

#endif // HSCCONNECTSETTING_H
