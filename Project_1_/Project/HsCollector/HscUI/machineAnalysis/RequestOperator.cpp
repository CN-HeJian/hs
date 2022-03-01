#include "RequestOperator.h"
#include <QDebug>
#include "templateSingle.hpp"
#include <iostream>
using namespace  std;

string  RequestOperator::ip ="172.16.254.60";
//string  RequestOperator::ip ="127.0.0.1";
quint16 RequestOperator::port = 6343;

//CustomProtocolBaseTcp*  RequestOperator::m_netServe = new CustomProtocolBaseTcp(); //需要使用单例模式来进行初始化

RequestOperator::RequestOperator()
{
    initHalderPoint();
}

/*
 * --------------------------------------------------------------------------------------------------------------------------
 *
 * 函数指针，对应的中断函数
 * +-------+--------------------------
 * |   0   |    requstRegionData
 * +-------+--------------------------
 * |   1   |    requestLeastMoldInfo
 * +-------+--------------------------
 * |   2   |    connectToServer
 * +-------+--------------------------
 * |   3   |    requestMachineList
 * +-------+--------------------------
 * |   4   |    requestHistoryData
 * +-------+--------------------------
 * |   5   |    detectInfo
 * +-------+--------------------------
 * |   6   |    reqDetectedFlag
 * +-------+--------------------------
 *
 * 请求类型、暂时一共有6种请求类型
 * -------------------------------------------
 * typedef enum REQUEST_TYPE{
 *     REQ_LEASTREGION,                 ---00
 *     REQ_LEASTMOLDFEATURE,            ---01
 *     REQ_SERVERSTATE,                 ---02
 *     REQ_MACHINELIST                  ---03
 *     REQ_QUERYHISTORY                 ---04
 *     REQ_DECTMOLD                     ---05
 *     REQ_DECTMOLDFLAG                 ---06
 * }request_t;
 * -------------------------------------------
 *
 * 请求的数据类型
 * +--------+-------------------------
 * |   00   |      注射段压力平均值
 * +--------+-------------------------
 * |   01   |       注射段二阶导数
 * +--------+-------------------------
 *
 ---------------------------------------------------------------------------------------------------------------------------*/


/*
 *
 * Init  Function Point  Table
 *
 */
void RequestOperator::initHalderPoint(){
    m_handler_table.resize(NUM_REQTYPE);
    m_handler_table[0] = &requestRegionData;
    m_handler_table[1] = &requestLeastMoldInfo;
    m_handler_table[2] = &connectToServe;
    m_handler_table[3] = &requestMachineList;
    m_handler_table[4] = &requestHistoryInfo;
    m_handler_table[5] = &detectInfo;
    //m_handler_table[6] = &reqDetectedFlag;
}

/*
 *  Select Function to package cmd
 *
 */
void RequestOperator::requestToServe(request_t request_type, SingleMachine *currentShow){
    qDebug()<<request_type;
    m_handler_table[request_type](currentShow);
}

/*
 *  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+
 *  |   REQUEST_TYPE      |     MACHIENNAME_LENGHT       |     MACHINE_NAME   |     DATATYPE   |        LASTCHANGEPARAMETERTIME           |
 *  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+
 *  | REQ_LEASTREGION(xx) |           xx(2)              |       xxxx(n)      |       xx(2)    |        XXXXXXXXXXXX[4+2+2+2+2]           |
 *  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+
 *  |       00            |            01                |         s          |        01      |             20200925093000               |
 *  +---------------------+------------------------------+--------------------+----------------+-------------------------------------------
 */
//请求最近区间
void RequestOperator::requestRegionData(SingleMachine* currentShow){
    //请求类型【扩展为两位】
    string s_reqtype = to_string(int(REQ_LEASTREGION));
    if(s_reqtype.size()==1){
        s_reqtype = "0"+s_reqtype;
    }
    string machine_name = currentShow->getMachineName();
    //模具名【扩展为两位】
    size_t machineNameSize = machine_name.size();
    string s_machineNameSize = to_string(machineNameSize);
    if(s_machineNameSize.size()==1){
        s_machineNameSize = "0"+s_machineNameSize;
    }
    //数据请求类型【扩展为两位】
    dataType_t selectDataType = currentShow->getDataType();
    string s_dataType = to_string(int(selectDataType));
    if(s_dataType.size()==1){
        s_dataType = "0"+s_dataType;
    }
    //获取一下时间+月份+日历+小时+分钟+秒数
    string leastDate = currentShow->getModifyProcessParameterTime();
    string req_dateTime = leastDate.substr(0,4) + leastDate.substr(5,2) +leastDate.substr(8,2)+leastDate.substr(11,2)+leastDate.substr(14,2)+leastDate.substr(17,2);
    //打包命令：PackageCmd
    string cmd = s_reqtype+ s_machineNameSize +machine_name+s_dataType+req_dateTime;
    qDebug()<<"requestRegionData: "<< QString::fromStdString(cmd);


    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();

    tmp_netServe->sendRequest(QString::fromStdString(cmd));
}

/*
 *  +------------------------------------------------------------------------------------------------------------------------+
 *  |   REQUEST_TYPE     |     MACHIENNAME_LENGHT       |     MACHINE_NAME   |     DATATYPE   |        LEASTMOLDCNT          |
 *  +--------------------+------------------------------+--------------------+----------------+------------------------------+
 *  |  REQ_LEASTMOLD(2)  |            xx(2)             |       xxx(n)       |       xx(2)    |            xxx(n)            |
 *  +--------------------+------------------------------+--------------------+----------------+------------------------------+
 *  |        01          |            01                |          s         |        01      |               52             |
 *  +--------------------+------------------------------+--------------------+----------------+------------------------------+
 */
//请求最近模次
void RequestOperator::requestLeastMoldInfo(SingleMachine *currentShow){
    //请求类型【扩展为两位】
    string s_reqtype = to_string(int(REQ_LEASTMOLDFEATURE));
    if(s_reqtype.size()==1){
        s_reqtype = "0"+s_reqtype;
    }
    string machine_name = currentShow->getMachineName();
    //模具名【扩展为两位】
    size_t machineNameSize = machine_name.size();
    string s_machineNameSize = to_string(machineNameSize);
    if(s_machineNameSize.size()==1){
        s_machineNameSize = "0"+s_machineNameSize;
    }
    //数据请求类型【扩展为两位】
    dataType_t selectDataType = currentShow->getDataType();
    string s_dataType = to_string(int(selectDataType));
    if(s_dataType.size()==1){
        s_dataType = "0"+s_dataType;
    }
    int moldCnt = currentShow->getSelectLatelyMoldCnt();
    string cmd = s_reqtype+s_machineNameSize+machine_name+s_dataType+to_string(moldCnt);
    qDebug()<<"requestLeastMoldInfo: "<<QString::fromStdString(cmd);

    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();

    tmp_netServe->sendRequest(QString::fromStdString(cmd));
}

/*
 *  +--------------------+
 *  | REQ_SERVERSTATE(2) |
 *  +--------------------+
 */
void RequestOperator::connectToServe(SingleMachine* currentShow){
    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();
    tmp_netServe->connectToService(QString::fromStdString(RequestOperator::ip),RequestOperator::port);
}

/*
 *  +--------------------+
 *  |    REQUEST_TYPE    |
 *  +--------------------+
 *  | REQ_MACHINELIST(3) |
 *  +--------------------+
 */
void RequestOperator::requestMachineList(SingleMachine* currentShow){
    //请求类型【扩展为两位】
    string s_reqtype = to_string(int(REQ_MACHINELIST));
    if(s_reqtype.size()==1){
        s_reqtype = "0"+s_reqtype;
    }
    string cmd = s_reqtype;
    qDebug()<<"requestMachineList: "<<QString::fromStdString(cmd);
    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();
    tmp_netServe->sendRequest(QString::fromStdString(cmd));
}

/*
*  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+------------------------------------------+
*  |   REQUEST_TYPE      |     MACHIENNAME_LENGHT       |     MACHINE_NAME   |     DATATYPE   |                 STARTTIME                |                 ENDTIME                  |
*  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+------------------------------------------+
*  | REQ_LEASTREGION(xx) |           xx(2)              |       xxxx(n)      |       xx(2)    |        XXXXXXXXXXXX[4+2+2+2+2]           |        XXXXXXXXXXXX[4+2+2+2+2]           |
*  +---------------------+------------------------------+--------------------+----------------+------------------------------------------+------------------------------------------+
*  |       04            |            01                |         s          |        01      |             20200925093000               |             20200925093000               |
*  +---------------------+------------------------------+--------------------+----------------+-------------------------------------------------------------------------------------+
*/
//请求历史信息
void RequestOperator::requestHistoryInfo(SingleMachine* currentShow){
    qDebug()<<"d";

    //请求类型【扩展为两位】
    string s_reqtype = to_string(int(REQ_QUERYHISTORY));
    if(s_reqtype.size()==1){
        s_reqtype = "0"+s_reqtype;
    }
    string machine_name = currentShow->getMachineName();
    //模具名【扩展为两位】
    size_t machineNameSize = machine_name.size();
    string s_machineNameSize = to_string(machineNameSize);
    if(s_machineNameSize.size()==1){
        s_machineNameSize = "0"+s_machineNameSize;
    }
    //数据请求类型【扩展为两位】
    dataType_t selectDataType = currentShow->getDataType();
    string s_dataType = to_string(int(selectDataType));
    if(s_dataType.size()==1){
        s_dataType = "0"+s_dataType;
    }
    //获取一下时间+月份+日历+小时+分钟+秒数
    string Start = currentShow->getStartTime();
    qDebug()<<QString::fromStdString(Start);
    string req_dateTime_start = Start.substr(0,4) + Start.substr(5,2) +Start.substr(8,2)+Start.substr(11,2)+Start.substr(14,2)+Start.substr(17,2);
    string End = currentShow->getEndTime();
    string req_dateTime_end = End.substr(0,4) + End.substr(5,2) +End.substr(8,2)+End.substr(11,2)+End.substr(14,2)+End.substr(17,2);
    //打包命令：PackageCmd
    string cmd = s_reqtype+ s_machineNameSize +machine_name+s_dataType+req_dateTime_start+req_dateTime_end;
    qDebug()<<"requestRegionData: "<< QString::fromStdString(cmd);


    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();

    tmp_netServe->sendRequest(QString::fromStdString(cmd));

}

/*
 *  +--------------------------+------------------------+-------------------------+----------------------+------------------------+--------------------------+
 *          RUQEST_TYPE            MACHIENNAME_LENGHT       MACHINE_NAME                  MoldDate
 *  +--------------------------+------------------------+------------- -----------+----------------------+------------------------+--------------------------+
 *             05
 *  +--------------------------+----------------------+-------------------------+----------------------+------------------------+--------------------------+
 */
//人工将已经请求的模次标记作为待检测点
void RequestOperator::detectInfo(SingleMachine* currentShow){
    qDebug()<<"reqMOld"<<endl;

    qDebug()<<"MoldName:" <<QString::fromStdString(currentShow->getMachineName());


    qDebug()<<"UpdateLastMoldInfo: "<<currentShow->getDetectMoldDate();

    //请求类型【扩展为两位】
    string s_reqtype = to_string(int(REQ_DECTMOLD));
    if(s_reqtype.size()==1){
        s_reqtype = "0"+s_reqtype;
    }
    string machine_name = currentShow->getMachineName();
    //模具名【扩展为两位】
    size_t machineNameSize = machine_name.size();
    string s_machineNameSize = to_string(machineNameSize);
    if(s_machineNameSize.size()==1){
        s_machineNameSize = "0"+s_machineNameSize;
    }

    string cmd = s_reqtype+ s_machineNameSize +machine_name+ currentShow->getDetectMoldDate().toStdString();


    connectToServe(nullptr);

    CustomProtocolBaseTcp * tmp_netServe = Singleton<CustomProtocolBaseTcp>::Instance();


    tmp_netServe->sendRequest(QString::fromStdString(cmd));

}

/*
 *  +--------------------------+------------------------+-------------------------+----------------------+------------------------+--------------------------+
 *          RUQEST_TYPE            MACHIENNAME_LENGHT       MACHINE_NAME                  MoldDate
 *  +--------------------------+------------------------+------------- -----------+----------------------+------------------------+--------------------------+
 *             06
 *  +--------------------------+------------------------+-------------------------+----------------------+------------------------+--------------------------+
 */
//请求已经标记的信息
//void RequestOperator::reqDetectedFlag(SingleMachine* currentShow){

//}





























