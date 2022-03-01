#ifndef HSCMONITORSETTINGMODEL_H
#define HSCMONITORSETTINGMODEL_H

#include <QList>
#include <QString>

struct HscEigenvalueMonitorModel
{
    int enable;
    QString type;
    double lowerPres;
    double upperPres;
    double lowerTime;
    double upperTime;
};

struct HscIntegralMonitorModel
{

    double lowerIntegral;
    double upperIntegral;
    double basicIntegral;

    double lowerPeakIntegral;
    double upperPeakIntegral;
    double basicPeakIntegral;
};

class HscMonitorItemModel
{

public:
    HscMonitorItemModel();

    QString channel;
    QList<HscEigenvalueMonitorModel> listOfEigenvalueMonitor;
    HscIntegralMonitorModel integralMonitor;

private:
    void initializer();

};

class HscMonitorSettingModel
{
public:
    HscMonitorSettingModel();

    static QList<HscMonitorItemModel> monitorSettingModel;

private:
    void initializer();

};

#endif // HSCMONITORSETTINGMODEL_H
