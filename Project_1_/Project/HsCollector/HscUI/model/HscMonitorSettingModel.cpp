#include "HscMonitorSettingModel.h"

#include <QString>

QList<HscMonitorItemModel> HscMonitorSettingModel::monitorSettingModel;

HscMonitorItemModel::HscMonitorItemModel()
{
    initializer();
}

void HscMonitorItemModel::initializer()
{
    // 特征值监控
    for (auto i(0); i<4; ++i) {
        HscEigenvalueMonitorModel model;
        model.enable = 0;
        model.type = "峰值压力";
        model.lowerPres = 20.00;
        model.upperPres = 40.00;
        model.lowerTime = 1.00;
        model.upperTime = 2.00;
        listOfEigenvalueMonitor.push_back(model);
    }

    // 积分值监控
    integralMonitor.lowerIntegral = 0.00;
    integralMonitor.upperIntegral = 200.00;
    integralMonitor.basicIntegral = 0.00;

    integralMonitor.lowerPeakIntegral = 0.00;
    integralMonitor.upperPeakIntegral = 200.00;
    integralMonitor.basicPeakIntegral = 0.00;
}

HscMonitorSettingModel::HscMonitorSettingModel()
{
    initializer();
}

void HscMonitorSettingModel::initializer()
{
    // 10通道模型
    for (auto i(0); i<10; ++i) {
        HscMonitorItemModel monitorItem;
        monitorItem.channel = QString("CH%1").arg(i+1);
        monitorSettingModel.push_back(monitorItem);
    }
}
