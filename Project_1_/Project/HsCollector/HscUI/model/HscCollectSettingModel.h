#ifndef HSCCOLLECTSETTINGMODEL_H
#define HSCCOLLECTSETTINGMODEL_H

#include <QString>
#include <QVector>
#include <QList>


struct HscConnectModel
{
    HscConnectModel() {}
    HscConnectModel(const HscConnectModel &model);
    HscConnectModel &operator= (const HscConnectModel &model);

    QString ip = "192.168.3.1";
    int port = 6343;
    QString sensorInterface = "Minebea";
};

struct HscSensorModel
{
    HscSensorModel() {}
    HscSensorModel(const HscSensorModel &model);
    HscSensorModel &operator= (const HscSensorModel &model);

    int id;
    int enable = 0; //是否启用
    double capacity = 490.3; // 额定容量
    double output = 0.600; // 额定输出
    QString surfaceShape = "圆形"; // 受压面形状
    double diameter = 2.00; // 直径
    double horizontal = 2.00; // 横截面长度
    double vertical = 2.00; // 纵界面长度
    double sectionArea = 2.00; // 横截面积
    QString channel = "CH"; // 通道名称
    QString sensorType = "压力"; // 传感器类型
    QString curveColor = ""; // 采集项目的颜色
    QString unit = "Mpa"; // 采集项目的单位
};

struct HscDisplayModel
{
    HscDisplayModel() {}
    HscDisplayModel(const HscDisplayModel &model);
    HscDisplayModel &operator= (const HscDisplayModel &model);

    QString moldNo = "";
    double displayTime = 15.00;
    double displayPressure = 20.00;
    double collectTime = 12.00;
    double displayPosition = 10.00;

};

class HscCollectSettingModel
{

public:
    HscCollectSettingModel();

    static int status; // 0: 离线，1：正常，2：错误
    static HscConnectModel connectModel;
    static QList<HscSensorModel> sensorsModel;
    static HscDisplayModel displayModel;

private:
    void initCollectModel();
    QStringList m_colors = { "#FF0000", "#FFA500", "#FFFF00", "#00FF00", "#00FFFF",
                             "#0000FF", "#A020F0", "#FF1493", "#B8860B", "#000000"};

};

#endif // HSCCOLLECTSETTINGMODEL_H
