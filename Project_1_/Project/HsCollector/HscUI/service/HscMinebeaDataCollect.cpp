#include "HscMinebeaDataCollect.h"

#include <QDebug>

double HscMinebeaDataCollect::filter_buf[10][51];

HscMinebeaDataCollect::HscMinebeaDataCollect(QObject *parent)
    : QObject(parent)
{

}

HscMinebeaDataCollect::~HscMinebeaDataCollect()
{

}

double HscMinebeaDataCollect::dataFilter(const int &ch, const double &val)
{
    double sum = 0;
    double temp = 0;

    filter_buf[ch][50] = val;
    for(auto i(0); i<50; ++i) {
        filter_buf[ch][i] = filter_buf[ch][i+1]; // 所有数据左移，低位扔掉
        sum += filter_buf[ch][i];
    }
    temp = (sum / 50);
    return temp;
}

void HscMinebeaDataCollect::readMessage(const mqttmsg* msg)
{
    //Separate data by comma
    QString str(static_cast<char*>(msg->payload));
    QStringList list = str.split(',');

//    qDebug() << str;
    QString signal = list[10];
    int start = signal.toInt();

//    int newMould_flag = start - m_step - 1;
    if((start == 1)&&(m_step == 0))
    {
        qDebug() << "begin";
        //采集状态
        m_moment = 1; // 标记开始采集
        m_listData.clear();

        emit updateStatus(QString("start"));
    }

    // 状态值为0时，表示未采集
    if (m_moment == 0) {
        return;
    }

    int chs = HscCollectSettingModel::sensorsModel.count();
    HscCollectDataModel dataItem(m_id, m_moment, chs);
    for (auto i(0); i<chs; ++i) {
        // 查看传感器通道是否启用
        if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
            dataItem[i] = 0;
            continue;
        }

        // 计算压力
        double area = 0;
        if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("圆形")) {
            area = 3.14 * HscCollectSettingModel::sensorsModel[i].diameter * HscCollectSettingModel::sensorsModel[i].diameter / 4;
        } else if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("矩形")) {
            area = HscCollectSettingModel::sensorsModel[i].horizontal * HscCollectSettingModel::sensorsModel[i].vertical;
        } else if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("其他")) {
            area = HscCollectSettingModel::sensorsModel[i].sectionArea;
        }

//        dataItem[i] = QString(list[i]).toDouble() * HscCollectSettingModel::sensorsModel[i].capacity * HscCollectSettingModel::sensorsModel[i].output * 0.2 / area;
        dataItem[i] = dataFilter(i, QString(list[i]).toDouble() * HscCollectSettingModel::sensorsModel[i].capacity * HscCollectSettingModel::sensorsModel[i].output * 0.2 / area);
//        dataItem[i] = QString(list[i]).toDouble();

    }


    // 记录数据及状态
    ++m_id; // 统计id
    ++m_moment; // 数据对应的周期时刻
    ++m_step; // 设置的采集时间
    m_listData.push_back(dataItem);
    emit plotCurve(dataItem);

    if (m_step >= HscCollectSettingModel::displayModel.collectTime*1000) {
        qDebug() << "stop";
        // 停止采集
        emit updateStatus(QString("stop")); // 更新状态
        // 重置另一个周期
        m_moment = 0;
        m_step = 0;
        m_qMutex.lock();
        // 界面只保留100条数据
        if (m_collectData.count() == 100) {
            m_collectData.clear();
        }
        m_collectData.push_back(m_listData);
        m_qMutex.unlock();

        emit dataAnalysis(&m_collectData); // 数据分析
    }

}

//void HscMinebeaDataCollect::readMessage(const mqttmsg* msg)
//{
//    //Separate data by comma
//    QString str(static_cast<char*>(msg->payload));
//    QStringList list = str.split(',');

//    qDebug() << str;

//    QString signal = list[10];
//    int start = signal.toInt();

//    qDebug () << start;
//    qDebug () << m_step;
//    int newMould_flag = start - m_step - 1;
//    qDebug () << newMould_flag;
//    if(!newMould_flag)
//    {
//        qDebug() << "begin";
//        //采集状态
//        m_moment = 1; // 标记开始采集
//        //        //remove the curve in the figure
//        //        p_Data->getCollectData()->removeAll();
//        emit updateStatus(QString("start"));
//    }

//    m_step = start;

//    // 状态值为0时，表示未采集
//    if (m_moment == 0) {
//        return;
//    }

//    int chs = HscCollectSettingModel::sensorsModel.count();
//    HscCollectDataModel dataItem(m_id, m_moment, chs);
//    for (auto i(0); i<chs; ++i) {
//        // 查看传感器通道是否启用
//        if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
//            continue;
//        }

//        // 计算压力
//        double area = 0;
//        if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("圆形")) {
//            area = 3.14 * HscCollectSettingModel::sensorsModel[i].diameter * HscCollectSettingModel::sensorsModel[i].diameter / 4;
//        } else if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("矩形")) {
//            area = HscCollectSettingModel::sensorsModel[i].horizontal * HscCollectSettingModel::sensorsModel[i].vertical;
//        } else if (HscCollectSettingModel::sensorsModel[i].surfaceShape == QString("其他")) {
//            area = HscCollectSettingModel::sensorsModel[i].sectionArea;
//        }

//        dataItem[i] = QString(list[i]).toDouble() * HscCollectSettingModel::sensorsModel[i].capacity * HscCollectSettingModel::sensorsModel[i].output * 0.2 / area;
//        //        dataItem[i] = QString(list[i]).toDouble();


//    }

//    // 记录数据及状态
//    m_listData.push_back(dataItem);
//    ++m_id;
//    ++m_moment;

//    if (m_moment >= m_timing*1000) {
//        qDebug() << "stop";
//        // 停止采集
//        m_moment = 0;
//        // 重置另一个周期
//        m_step = 1;

//        emit updateStatus(QString("stop"));
//    }
//}
