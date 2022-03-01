#ifndef HSCMONITORSETTING_H
#define HSCMONITORSETTING_H

#include <QWidget>

#include "HscMonitorItem.h"
#include "HscMonitorSettingModel.h"

namespace Ui {
class HscMonitorSetting;
}

class HscRealTimeMonitor;
class HscMonitorSetting : public QWidget
{
    Q_OBJECT

public:
    explicit HscMonitorSetting(QWidget *parent = nullptr);
    ~HscMonitorSetting();

signals:
    void currentChannel(int index);

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void onUpdateTopleft(int channel, int monitor, double upperPres, double lowerTime);
    void onUpdateBottomright(int channel, int monitor, double lowerPres, double upperTime);

private:
    void initView();
    void initSignalSlots();

private:
    Ui::HscMonitorSetting *ui;

    HscRealTimeMonitor *m_realTimeCurve = nullptr;

};

#endif // HSCMONITORSETTING_H
