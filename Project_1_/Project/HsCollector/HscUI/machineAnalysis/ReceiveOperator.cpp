#include "ReceiveOperator.h"
#include <QByteArray>
#include <QString>
#include <QDebug>
vector<string> ReceiveOperator::machineList = {};
vector<pair<string,float>> ReceiveOperator::plotData={};
vector<pair<string,float>> ReceiveOperator::detectMoldInfo={};


ReceiveOperator::ReceiveOperator(){
    //function_table
    function_table.resize(5);
    function_table[0] = &decodeLeastRegion;
    function_table[1] = &decodeLeastMold;
    function_table[2] = nullptr;
    function_table[3] = &decodeMachineList;
    function_table[4] = &decodeHistoryInfo;
    function_table[5] = &getDetectedInfo;
}


ReceiveOperator::~ReceiveOperator(){

}

/*  获取最近区间
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(0)    || returnDataType ||   machineLength    ||  machineName  ||year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |       00       ||     00         ||      1           ||        s      ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +--------------------------------------------------------------------------------------------------------------------------------------+
 */
//处理最近区间的数据
void* ReceiveOperator::decodeLeastRegion(QByteArray buff){
    qDebug()<<"receiveBuffSize"<<buff.size();
    QString buf  = buff;
    int buf_length = buf.size();
    int nameLength = (buff.at(4)-'0')*10+(buff.at(5)-'0'); //机台的长度
    string machineName = buff.mid(6,nameLength).toStdString();        //机台的名字
    QString machineName_s = buf.mid(6+nameLength,buf_length-6-nameLength);
    //qDebug()<<"MACHINNAME: "<<machineName_s;
    QString tmp="";
    plotData.clear();
    for(int i=0;i<machineName_s.size();i++){
        if(machineName_s[i]!=','){
            tmp += machineName_s[i];
        }else{
            //qDebug()<<"tmp: "<<tmp;
            string date = tmp.mid(0,19).toStdString();
            float val = stof(tmp.mid(20,6).toStdString());
            //qDebug()<<"date: "<<date<<"val: "<<val;
            pair<string,float> mold = {date,val};
            plotData.push_back(mold);
            tmp = "";
        }
    }
    return &plotData;
}
/*  获取最近模次
 *  +------------++-------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(1)    ||   returnDataType       ||  machineLength    ||  machineName ||   year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++-------------------------------------------------------------------------------------------------------------------------+
 *  |       01       ||         00             ||          1        ||       s      ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +---------------------------------------------------------------------------------------------------------------------------------------+
 */
//处理最近模次的数据
void*  ReceiveOperator::decodeLeastMold(QByteArray buff){
    QString buf  = buff;
    int buf_length = buf.size();
    int nameLength = (buff.at(4)-'0')*10+(buff.at(5)-'0'); //机台的长度
    string machineName = buff.mid(6,nameLength).toStdString();        //机台的名字
    QString machineName_s = buf.mid(6+nameLength,buf_length-6-nameLength);
    //qDebug()<<"MACHINNAME: "<<machineName_s;
    QString tmp="";
    plotData.clear();
    for(int i=0;i<machineName_s.size();i++){
        if(machineName_s[i]!=','){
            tmp += machineName_s[i];
        }else{
            //qDebug()<<"tmp: "<<tmp;
            string date = tmp.mid(0,19).toStdString();
            float val = stof(tmp.mid(20,6).toStdString());
            //qDebug()<<"date: "<<QString::fromStdString(date)<<"val: "<<val;
            pair<string,float> mold = {date,val};
            plotData.push_back(mold);
            tmp = "";
        }
    }
    return &plotData;
}

/*  获取机器列表
 *  +------------++-----------------------------------------------------------------------------------------------------------+
 *  |  reqType(03)   ||  MoldFileName,MoldFileName,MoldFileName,MoldFileName,
 *  +------------++-----------------------------------------------------------------------------------------------------------+
 */
//返回机台列表
void* ReceiveOperator::decodeMachineList(QByteArray buff){
    QString buf = buff;
    int buf_length = buf.size();
    QString machineName_s = buf.mid(2,buf_length-2);
    QString tmp="";
    machineList.clear();
    for(int i=0;i<machineName_s.size();i++){
        if(machineName_s[i]!=','){
            tmp += machineName_s[i];
        }else{
            machineList.push_back(tmp.toStdString());
            tmp = "";
        }
    }
    return &machineList;
}

/*  获取最近区间
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(0)    || returnDataType ||   machineLength    ||  machineName  ||year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |       00       ||     00         ||      1             ||        s      ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +--------------------------------------------------------------------------------------------------------------------------------------+
 */
//处理最近区间的数据
void* ReceiveOperator::decodeHistoryInfo(QByteArray buff){
    qDebug()<<"receiveBuffSize"<<buff.size();
    QString buf  = buff;
    int buf_length = buf.size();
    int nameLength = (buff.at(4)-'0')*10+(buff.at(5)-'0'); //机台的长度
    string machineName = buff.mid(6,nameLength).toStdString();        //机台的名字
    QString machineName_s = buf.mid(6+nameLength,buf_length-6-nameLength);
    //qDebug()<<"MACHINNAME: "<<machineName_s;
    QString tmp="";
    plotData.clear();
    for(int i=0;i<machineName_s.size();i++){
        if(machineName_s[i]!=','){
            tmp += machineName_s[i];
        }else{
            //qDebug()<<"tmp: "<<tmp;
            string date = tmp.mid(0,19).toStdString();
            float val = stof(tmp.mid(20,6).toStdString());
            //qDebug()<<"date: "<<date<<"val: "<<val;
            pair<string,float> mold = {date,val};
            plotData.push_back(mold);
            tmp = "";
        }
    }
    return &plotData;
}


void* ReceiveOperator::getDetectedInfo(QByteArray buff){
   qDebug()<<"getDetectedInfo: "<<buff<<endl;
//    qDebug()<<"receiveBuffSize"<<buff.size();
//    QString buf  = buff;
    int buf_length = buff.size();
    int nameLength = (buff.at(4)-'0')*10+(buff.at(5)-'0'); //机台的长度
    string machineName = buff.mid(4,nameLength).toStdString();        //机台的名字
    QString remain = buff.mid(6+nameLength,buf_length-6-nameLength);
    qDebug()<<"remain: "<<remain;
    QString tmp="";
    detectMoldInfo.clear();
    for(int i=0;i<remain.size();i++){
        if(remain[i]!=','){
            tmp += remain[i];
        }else{
            //qDebug()<<"tmp: "<<tmp;
            string date = tmp.mid(0,19).toStdString();
            float val = stof(tmp.mid(20,6).toStdString());
            qDebug()<<"date: "<<QString::fromStdString(date)<<"val: "<<val;
            pair<string,float> mold = {date,val};
            detectMoldInfo.push_back(mold);
            tmp = "";
        }
    }
    return &detectMoldInfo;
}
