#ifndef RECEIVEOPERATOR_H
#define RECEIVEOPERATOR_H

#include <QByteArray>
#include <vector>
using namespace std;
#include <QDebug>
#include "task/getMessage.h"
#include <QString>
#include "tool/templateSingle.hpp"
#include <functional>

#define NUM_REQTYPE  10
#define NUM_DATATYPE  10

class ReceiveOperator
{
public:
    ReceiveOperator();


    //初始化函数指针
    void initHandlerFunctionPoint();


    //获取机器列表
    static vector<QString> getMachineList(QByteArray buf);

    //获取机台时间区间内的特征值
    static vector<QString> getRegionInfo(QByteArray buf);

    //获取最近几个模次的特征值
    static vector<QString> getLeastMoldInfo(QByteArray buf);

    //获取历史模次的数据
    static vector<QString> getHistoryInfo(QByteArray buf);

    //标记检测点
    static vector<QString> setDetectInfo(QByteArray buf);


    static QString getDetectInfo(string type,string startTime,string endTime,int moldCnt,string machineName);

    //定义函数指针类型
    typedef vector<QString> (*handler_t)(QByteArray buf);

    //函数指针数组
    vector<handler_t> m_handler_table;

    //请求数据类型表
    static vector<string> m_dataTypeTable;


};

#endif // RECEIVEOPERATOR_H
