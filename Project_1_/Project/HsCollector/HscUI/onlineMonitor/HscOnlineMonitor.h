#ifndef HSCONLINEMONITOR_H
#define HSCONLINEMONITOR_H

#include <QWidget>
#include <QThread>
#include <QMdiSubWindow>

#include "HscCollectSetting.h"


#include "HscSetVisible.h"
#include "HscRealTimeMonitor.h"
#include "HscRewriteCurve.h"
#include "HscIntegralValueTendency.h"
#include "HscPeakPressureTendency.h"

#include "QMQTT.h"
#include "HscTestData.h"
#include "HscMinebeaDataCollect.h"
#include "HscMinebeaDataMonitor.h"
#include "HscMinebeaDataSave.h"

namespace Ui {
class HscOnlineMonitor;
}

class HscOnlineMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit HscOnlineMonitor(QWidget *parent = nullptr);
    ~HscOnlineMonitor();

public:
    void collectSetting();
    void connectMqtt();
    void switchCollect();
    void startPlot();

    HscRealTimeMonitor *realTimeMonitor() {
        return m_realTimeCurve;
    }

    void setSubWindow(int index);

private:
    void initView();
    void loadCollectSetting();
    void initSignalSlots();
    void initSimulateSignal(); // 模拟信号

signals:
    void updateCollectSetting();
    void startCollect();

public slots:
    void applyCollectSetting();
    void updateChannelVisible();
    void analysisData(QList<HscDataAnalysisModel> *list);

private:
    Ui::HscOnlineMonitor *ui;

    // 监控设置界面
    HscCollectSetting *m_collectSetting = nullptr;

    // 子界面
    HscSetVisible *m_setVisible = nullptr;
    HscRealTimeMonitor *m_realTimeCurve = nullptr;
    HscRewriteCurve *m_rewriteCurve = nullptr;
    HscIntegralValueTendency *m_integralValueTendency = nullptr;
    HscPeakPressureTendency *m_peakPressureTendency = nullptr;
    QVector<QMdiSubWindow *> m_subWindows;
    QVector<QWidget *> m_childWidgets;

    // 最上侧展示栏
    QVector<QFrame *> m_peakPresFrames;
    QVector<QFrame *> m_integralFrames;
    QVector<QLabel *> m_peakPresChannels;
    QVector<QLabel *> m_peakPresValues;
    QVector<QLabel *> m_integralChannels;
    QVector<QLabel *> m_integralValues;

    // 连接
    int m_collectType = 0; // 0-Minebea 1-Kistler
    QMQTT *m_mqtt = nullptr;
    bool m_mqttConnected = false;
    bool m_collected = false;

    HscTestData *m_testThread = nullptr; // 测试数据
    QThread *m_minebeaCollectThread = nullptr; // minebea数据采集工作线程
    HscMinebeaDataCollect *m_minebeaCollect = nullptr;
    QThread *m_minebeaMonitorThread = nullptr; // minebea数据监控工作线程
    HscMinebeaDataMonitor *m_minebeaMonitor = nullptr;
    QThread *m_minebeaSaveThread = nullptr; // minebea数据存储工作线程
    HscMinebeaDataSave *m_minebeaSave = nullptr;

    // 图表的一些标记值
    int m_yMaxPres = 0;
    int m_xMaxTime = 0;
    int m_yMaxInteg = 0;
};

#endif // HSCONLINEMONITOR_H
