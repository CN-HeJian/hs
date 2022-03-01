#include "HscCollectSettingModel.h"

int HscCollectSettingModel::status = 0;
HscConnectModel HscCollectSettingModel::connectModel;
QList<HscSensorModel> HscCollectSettingModel::sensorsModel;
HscDisplayModel HscCollectSettingModel::displayModel;

HscCollectSettingModel::HscCollectSettingModel()
{
    initCollectModel();
}

void HscCollectSettingModel::initCollectModel()
{
    // 连接设置
    HscCollectSettingModel::connectModel.ip = "192.168.3.1";
    HscCollectSettingModel::connectModel.port = 6343;
    HscCollectSettingModel::connectModel.sensorInterface = "Minebea";

    // 传感器设置, 默认设置为10通道
    for (auto i(0); i<10; ++i) {
        HscSensorModel sensor;
        sensor.id = i;
        if (i == 0)
            sensor.enable = 1;
        sensor.capacity = 490.3;
        sensor.output = 0.600;
        sensor.surfaceShape = "圆形";
        sensor.diameter = 2.00;
        sensor.horizontal = 2.00;
        sensor.vertical = 2.00;
        sensor.sectionArea = 2.00;
        sensor.channel = QString("CH%1").arg(i+1);
        sensor.sensorType = "压力";
        sensor.curveColor = m_colors[i];
        sensor.unit = "Mpa";
        HscCollectSettingModel::sensorsModel.push_back(sensor);
    }

    // 显示设置
    HscCollectSettingModel::displayModel.moldNo = "";
    HscCollectSettingModel::displayModel.displayTime = 15;
    HscCollectSettingModel::displayModel.displayPressure = 20;
    HscCollectSettingModel::displayModel.collectTime = 12;
    HscCollectSettingModel::displayModel.displayPosition = 10;
}

HscConnectModel::HscConnectModel(const HscConnectModel &model)
{
    ip = model.ip;
    port = model.port;
    sensorInterface = model.sensorInterface;
}

HscConnectModel &HscConnectModel::operator=(const HscConnectModel &model)
{
    ip = model.ip;
    port = model.port;
    sensorInterface = model.sensorInterface;

    return *this;
}

HscSensorModel::HscSensorModel(const HscSensorModel &model)
{
    id = model.id;
    enable = model.enable;
    capacity = model.capacity;
    output = model.output;
    surfaceShape = model.surfaceShape;
    diameter = model.diameter;
    horizontal = model.horizontal;
    vertical = model.vertical;
    sectionArea = model.sectionArea;
    channel = model.channel;
    sensorType = model.sensorType;
    curveColor = model.curveColor;
    unit = model.unit;
}

HscSensorModel &HscSensorModel::operator=(const HscSensorModel &model)
{
    id = model.id;
    enable = model.enable;
    capacity = model.capacity;
    output = model.output;
    surfaceShape = model.surfaceShape;
    diameter = model.diameter;
    horizontal = model.horizontal;
    vertical = model.vertical;
    sectionArea = model.sectionArea;
    channel = model.channel;
    sensorType = model.sensorType;
    curveColor = model.curveColor;
    unit = model.unit;

    return *this;
}

HscDisplayModel::HscDisplayModel(const HscDisplayModel &model)
{
    moldNo = model.moldNo;
    displayTime = model.displayTime;
    displayPressure = model.displayPressure;
    collectTime = model.collectTime;
    displayPosition = model.displayPosition;
}

HscDisplayModel &HscDisplayModel::operator=(const HscDisplayModel &model)
{
    moldNo = model.moldNo;
    displayTime = model.displayTime;
    displayPressure = model.displayPressure;
    collectTime = model.collectTime;
    displayPosition = model.displayPosition;

    return *this;
}
