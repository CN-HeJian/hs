#ifndef RECEIVEOPERATOR_H
#define RECEIVEOPERATOR_H
#include "QByteArray"
#include <vector>
using namespace  std;




class ReceiveOperator
{
public:
     ReceiveOperator();

     ~ReceiveOperator();

     //处理最近区间的数据
     static  void* decodeLeastRegion(QByteArray buff);

     //处理最近模次的数据
     static  void*  decodeLeastMold(QByteArray buff);

     //处理机台列表的数据
     static  void* decodeMachineList(QByteArray buff);

     static  void* decodeHistoryInfo(QByteArray buff);

     //获取标记点信息
     static void* getDetectedInfo(QByteArray buff);

     //机台列表的数据
     static vector<string> machineList;

     //机台分析画图窗口的数据
     static vector<pair<string,float>> plotData;

      //监测点
     static vector<pair<string,float>> detectMoldInfo;

     //声明函数指针
     typedef void* (*handler_t)(QByteArray buff);

     //函数指针表
     vector<handler_t> function_table;

};






#endif // RECEIVEOPERATOR_H
