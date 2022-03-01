#ifndef HSCCOLLECTDATAMODEL_H
#define HSCCOLLECTDATAMODEL_H

#include <QMetaType>
#include <QVector>
#include <QDateTime>

struct HscCollectDataModel
{

    HscCollectDataModel() {
        // 线程间自定义数据传递
        qRegisterMetaType<HscCollectDataModel>("HscCollectDataModel");
        m_data.resize(m_chs);
        m_currentDateTime = QDateTime::currentDateTime();
    }
    HscCollectDataModel(quint64 id, quint64 moment, int chs);

    double &operator[] (const int index) {
        return m_data[index];
    }

    quint64 m_id = 1;
    quint64 m_moment = 1;
    int m_chs = 10;
    QVector<double> m_data;
    QDateTime m_currentDateTime;

};

struct HscDataAnalysisModel {
//    QList<HscCollectDataModel> *data;
    QVector<double> integralValues;
    QVector<double> peakPressures;
    QVector<QVector<double>> monitorValues;
    bool good = true;
};


#endif // HSCCOLLECTDATAMODEL_H
