#ifndef REQUESTOPERATOR_H
#define REQUESTOPERATOR_H

#include "CustomProtocolBaseTcp.h"
#include <SingleMachine.h>
#include <string>

using namespace std;

typedef enum REQUEST_TYPE
{
    REQ_LEASTREGION, //0
    REQ_LEASTMOLDFEATURE, //1
    REQ_SERVERSTATE,  //2
    REQ_MACHINELIST,  //3
    REQ_QUERYHISTORY,  //4
    REQ_DECTMOLD     //5
}request_t;

#define NUM_REQTYPE 10  //请求数据一共有多种类型

class RequestOperator
{
public:
    RequestOperator();
    //请求服务器状态
    static void connectToServe(SingleMachine* currentShow);
    //请求机器列表
    static void requestMachineList(SingleMachine* currentShow);
    //初始化函数指针
    void initHalderPoint();
    //请求某个机台时间区间内的特征值
    static void requestRegionData(SingleMachine* currentShow);
    //请求最近几个模次的平均值特征
    static void requestLeastMoldInfo(SingleMachine* currentShow);
    //请求历史数据
    static void requestHistoryInfo(SingleMachine* currentShow);
    //请求数据
    //void requestPlotWidgetData(SingleMachine *currentShow);
    //向服务器请求
    void requestToServe(request_t request_type, SingleMachine *currentShow);
    //标记信息
    static void detectInfo(SingleMachine* currentShow);
    //请求已经标记的信息
    static void reqDetectedFlag(SingleMachine* currentShow);
    //网络服务设置端口设置
    static string  ip;
    static quint16 port;
    //声明函数指针
    typedef void (*handler_t)(SingleMachine *cur);
    //初始化函数指针数组
    vector<handler_t> m_handler_table;
private:

    CustomProtocolBaseTcp *m_netServe;//网络服务
    //static CustomProtocolBaseTcp * m_netServe;//网络服务

};

#endif // REQUESTOPERATOR_H
