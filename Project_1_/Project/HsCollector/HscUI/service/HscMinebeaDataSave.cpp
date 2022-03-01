#include "HscMinebeaDataSave.h"

#include <QDateTime>
#include <QDebug>

HscMinebeaDataSave::HscMinebeaDataSave(QObject *parent)
    : QObject(parent)
{

}

HscMinebeaDataSave::~HscMinebeaDataSave()
{

}

void HscMinebeaDataSave::onStartCollect()
{
    m_databaseManage.openDatabase();
    // 当开启采集时，存储当前信息，创建当次采集记录表以及详细数据表
    tb_name = QString("record_") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    columns = "mold_no varchar(30), remark varchar(30), sensors_setting int";
    column_headers = "mold_no, remark, sensors_setting";
    detail_tb_name = QString("collect_") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    detail_columns = "mold_no varchar(30), remark varchar(30), count int,"
                             "ch1 double, ch2 double, ch3 double, ch4 double, ch5 double,"
                             "ch6 double, ch7 double, ch8 double, ch9 double, ch10 double";
    detail_column_headers = "mold_no, remark, count,"
                            "ch1, ch2, ch3, ch4, ch5,"
                            "ch6, ch7, ch8, ch9, ch10";
    m_databaseManage.createTable(tb_name, columns);
    m_databaseManage.createTable(detail_tb_name, detail_columns);
}

void HscMinebeaDataSave::saveData(QList<HscCollectDataModel> *list)
{
    // 存储单个模次数据
    // 存储标记
    auto listData = *list;
    QString mold_no = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString remark = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    int sensors_setting = 0;
    QString columnsValues = QString("%1, %2, %3").arg(mold_no).arg(remark).arg(sensors_setting);
    m_databaseManage.insertRecord(tb_name, column_headers, columnsValues);

    // 存储细节
    auto db = m_databaseManage.database();
    db->transaction();
    qDebug() << listData.count();
    for (auto i(0); i<listData.count(); ++i) {
        int time = int(listData.at(i).m_moment);
        auto &data = listData.at(i).m_data;
        QString parameter_detail = QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13")
                .arg(mold_no).arg(remark).arg(time).arg(data[0]).arg(data[1]).arg(data[2]).arg(data[3])
                .arg(data[4]).arg(data[5]).arg(data[6]).arg(data[7]).arg(data[8]).arg(data[9]);
        m_databaseManage.insertRecord(detail_tb_name, detail_column_headers, parameter_detail);
    }
    db->commit();
}
