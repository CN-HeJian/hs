#include "HscMinebeaDataMonitor.h"

#include <QDebug>

#include "HscMonitorSettingModel.h"

HscMinebeaDataMonitor::HscMinebeaDataMonitor(QObject *parent)
    : QObject(parent)
{

}

HscMinebeaDataMonitor::~HscMinebeaDataMonitor()
{

}

void HscMinebeaDataMonitor::dataAnalysis(QList<QList<HscCollectDataModel> > *list)
{
    qDebug() << "data analysis";

    int chs = HscCollectSettingModel::sensorsModel.count();
    auto &data = list->last();
//    for ( ; m_analysisCount < list->count(); ++m_analysisCount) {
        HscDataAnalysisModel analysisModel;
//        analysisModel.data = &((*list)[m_analysisCount]);
        analysisModel.integralValues.resize(chs);
        analysisModel.peakPressures.resize(chs);
        analysisModel.monitorValues.resize(chs);
        for (auto &item : analysisModel.monitorValues) {
            item.resize(4);
        }

        for (auto i(0); i < data.count(); ++i) {
            for (auto j(0); j<chs; ++j) {
                // 计算积分值
                analysisModel.integralValues[j] += data[i][j] / 1000;

                // 计算峰值压力
                if (data[i][j] > analysisModel.peakPressures[j]) {
                    analysisModel.peakPressures[j] =  data[i][j];
                }

                // 计算监控设置各阶段对应峰值
                auto monitorList = HscMonitorSettingModel::monitorSettingModel[j].listOfEigenvalueMonitor;
                for (auto t(0); t<monitorList.count(); ++t) {
                    // 阀
                    if (monitorList.at(t).enable == 0) {
                        continue;
                    }

                    int begin = static_cast<int>(monitorList.at(t).lowerTime);
                    int end = static_cast<int>(monitorList.at(t).upperTime);

                    if ((i >= begin)&&(i <= end)&&(data[i][j] > analysisModel.monitorValues[j][t])) {
                        qDebug() << data[i][j];
                        qDebug() << analysisModel.monitorValues[j][t];
                        analysisModel.monitorValues[j][t] = data[i][j];
                    }
                }

            }
        }

        // 分析各部分峰值，实现监控
        for (auto c(0); c<chs; ++c) {
            auto &monitorList = HscMonitorSettingModel::monitorSettingModel[c].listOfEigenvalueMonitor;
            for (auto m(0); m<monitorList.count(); ++m) {
                // 阀
                if (monitorList[m].enable == 0) {
                    continue;
                }

                double top = monitorList[m].upperPres;
                double down = monitorList[m].lowerPres;
                if (analysisModel.monitorValues[c][m] < down
                        || analysisModel.monitorValues[c][m] > top) {
                    analysisModel.good = false;
                }
            }
        }
        // 线程锁--"m_analysisData"在多个地方调用
        m_qMutex.lock();
        if (m_analysisData.count() == 100) {
            m_analysisData.clear();
        }
        m_analysisData.push_back(analysisModel);
        m_qMutex.unlock();
//    }

    emit plotRewriteCurve(list); // 重写曲线
    emit analysisData(&m_analysisData); // 更新分析结果

}

