#ifndef HSCMINEBEADATAMONITOR_H
#define HSCMINEBEADATAMONITOR_H

#include <QObject>
#include <QMutex>

#include "HscCollectSettingModel.h"
#include "HscCollectDataModel.h"

class HscMinebeaDataMonitor : public QObject
{
    Q_OBJECT
public:
    HscMinebeaDataMonitor(QObject *parent = 0);
    ~HscMinebeaDataMonitor();

signals:
    void plotRewriteCurve(QList<QList<HscCollectDataModel>> *list); // 重写曲线
    void analysisData(QList<HscDataAnalysisModel> *list);

public slots:
    void dataAnalysis(QList<QList<HscCollectDataModel>> *list);

private:

private:
    QList<HscDataAnalysisModel> m_analysisData;
    int m_analysisCount = 0;

    QMutex m_qMutex;
};

#endif // HSCMINEBEADATAMONITOR_H
