#ifndef HSCMINEBEADATACOLLECT_H
#define HSCMINEBEADATACOLLECT_H

#include <QObject>
#include <QMutex>

#include "QMQTT.h"
#include "HscCollectSettingModel.h"
#include "HscCollectDataModel.h"

class HscMinebeaDataCollect : public QObject
{
    Q_OBJECT
public:
    HscMinebeaDataCollect(QObject *parent = nullptr);
    ~HscMinebeaDataCollect();

private:
    double dataFilter(const int &ch, const double &val);

signals:
    void updateStatus(QString status); // 更新实时监控状态
    void plotCurve(HscCollectDataModel data); // 绘制实时曲线
    void dataAnalysis(QList<QList<HscCollectDataModel>> *list); // 数据分析

public slots:
    void readMessage(const mqttmsg *);
//    void readMessage(QString str);

private:

    // 一个采集周期数据流个数
    quint64 m_id = 1;
    int m_step = 0;
    double m_timing = 15;
    quint64 m_moment = 0; // 0：为未采集
    static double filter_buf[10][51];
    QList<HscCollectDataModel> m_listData;

    // 所有模次采集数据
    QList<QList<HscCollectDataModel>> m_collectData;
    QMutex m_qMutex;
};

#endif // HSCMINEBEADATACOLLECT_H
