#include "receiveOperator.h"
#include "task/getMessage.h"
#include <QString>
#include "tool/templateSingle.hpp"


vector<string> ReceiveOperator::m_dataTypeTable = {"injectionPhasePressAvg","ActExtTorque6","ActTimPlst_1","OPT2PeakToPack"};

ReceiveOperator::ReceiveOperator()
{
    initHandlerFunctionPoint();

}

void ReceiveOperator::initHandlerFunctionPoint(){
    m_handler_table.resize(NUM_REQTYPE);
    m_handler_table[0] = &getRegionInfo;
    m_handler_table[1] = &getLeastMoldInfo;
    m_handler_table[2] = nullptr;
    m_handler_table[3] = &getMachineList;
    m_handler_table[4] = &getHistoryInfo;
    m_handler_table[5] = &setDetectInfo;
}



/*
 *
 * +----------------------------------------------------+
 * |   注射段压力平均值[injectionPhasePressAvg]    |   00   |
 * +----------------------------------------------------+
 * |      计量扭矩[ActExtTorque6]                 |   01   |
 * +----------------------------------------------------+
 * |      计量时间[ActTimPlst_1]                  |   02   |
 * +----------------------------------------------------+
 */


/*  获取最近区间
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(0)     ||   machineLength    ||  machineName    ||  returnDataType   ||year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |       00        ||      1             ||        s        ||     00            ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +--------------------------------------------------------------------------------------------------------------------------------------+
 */
vector<QString> ReceiveOperator::getRegionInfo(QByteArray buf){
    qDebug()<<"get region Info";
    //扩展为两位
    int ReqTypeNum = (buf[0]-'0')*10+(buf[1]-'0');
    QString ReqTypeNum_s = QString::fromStdString(to_string(ReqTypeNum));
    if(ReqTypeNum_s.size()==1){
        ReqTypeNum_s = "0"+ReqTypeNum_s;
    }

    //QString res= QString::fromStdString(to_string(ReqTypeNum));

    //组装指令
    QString buff = buf;
    qDebug()<<"buff: "<<buff;

    int nameLength = (buf.at(2)-'0')*10+(buf.at(3)-'0'); //机台的长度
    string machineName = buff.mid(4,nameLength).toStdString();        //机台的名字
    //扩展为两位
    QString nameLength_s = QString::fromStdString(to_string(nameLength));
    if(nameLength_s.size()==1){
        nameLength_s = "0"+nameLength_s;
    }


    QString dataType = buff.mid(4+nameLength,2);         //选择的数据类型
    qDebug()<<"dataType: "<<dataType;
    string year = buff.mid(6+nameLength,4).toStdString();
    string month = buff.mid(10+nameLength,2).toStdString();
    string day = buff.mid(12+nameLength,2).toStdString();
    string hour = (buff.mid(14+nameLength,2)).toStdString();
    string minute = (buff.mid(16+nameLength,2)).toStdString();
    string second = (buff.mid(18+nameLength,2)).toStdString();
    string startTime = year+'-'+month+'-'+day+" "+hour+":"+minute+":"+second;

    //qDebug()<<"machineName: "<<machineName<<"dataType: "<<dataType<<"year: "<<year<<"month: "<<month<<"day: "<<day<<"hour: "<<hour<<"minute: "<<minute<<"second："<<second;

    QString res= ReqTypeNum_s+dataType+nameLength_s+QString::fromStdString(machineName);

    sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
    //执行数据库查询指令
    vector<pair<QString,float>> selectedData;
    selectedData =  temp_sqlServer->selectData(machineName,ReceiveOperator::m_dataTypeTable[dataType.toInt()],startTime);

    qDebug()<<"selectedSize: "<<selectedData.size();

    //按照一定的规则，序列化查询的数据
    int num = selectedData.size();
    for(int i=0;i<num;i++){
        auto c = selectedData[i];
        string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
        res += QString::fromStdString(onedata);
    }

    QString res2 = getDetectInfo("region",startTime,"",0,machineName);

    return  {res,res2};
}

/*  获取最近模次
 *  +------------++-------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(1)    ||   returnDataType       ||  machineLength    ||  machineName ||   year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++-------------------------------------------------------------------------------------------------------------------------+
 *  |       01       ||         00             ||          1        ||       s      ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +---------------------------------------------------------------------------------------------------------------------------------------+
 */
vector<QString> ReceiveOperator::getLeastMoldInfo(QByteArray buf){
    qDebug()<<"get leastMold Info";
    //扩展为两位
    int ReqTypeNum = (buf[0]-'0')*10+(buf[1]-'0');
    QString ReqTypeNum_s = QString::fromStdString(to_string(ReqTypeNum));
    if(ReqTypeNum_s.size()==1){
        ReqTypeNum_s = "0"+ReqTypeNum_s;
    }
    //QString res= QString::fromStdString(to_string(ReqTypeNum));

    QString buff = buf;
    qDebug()<<"buff: "<<buff;

    int nameLength = (buf.at(2)-'0')*10+(buf.at(3)-'0'); //机台的长度
    QString nameLength_s = QString::fromStdString(to_string(nameLength));
    if(nameLength_s.size()==1){
        nameLength_s = "0"+nameLength_s;
    }
    string machineName = buff.mid(4,nameLength).toStdString();        //机台的名字
    QString dataType = buff.mid(4+nameLength,2);         //选择的数据类型
    int moldCnt = 0;
    for(int i=6+nameLength;i<buff.size();i++){
        moldCnt = 10*moldCnt + buf[i]-'0';
    }
    qDebug()<<"moldCnt: "<<moldCnt;

    QString res= ReqTypeNum_s+dataType+nameLength_s+QString::fromStdString(machineName);
    sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
    //执行数据库查询指令
    vector<pair<QString,float>> selectedData;
    selectedData =  temp_sqlServer->selectLeastData(machineName,ReceiveOperator::m_dataTypeTable[dataType.toInt()],moldCnt);

    //按照一定的规则，序列化查询的数据
    int num = selectedData.size();
    string res1;
    for(int i=num-1;i>=0;i--){
        pair<QString,float> c = selectedData[i];
        string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
        res += QString::fromStdString(onedata);

    }

    qDebug()<<"leastMold: "<<selectedData.size()<<endl;

    QString res2 = getDetectInfo("least","","",moldCnt,machineName);

    //return {res};
    return {res,res2};
}

/*  获取机器列表
 *  +------------++-----------------------------------------------------------------------------------------------------------+
 *  |  reqType(03)   ||  MoldFileName,MoldFileName,MoldFileName,MoldFileName,
 *  +------------++-----------------------------------------------------------------------------------------------------------+
 */
vector<QString> ReceiveOperator::getMachineList(QByteArray buf){
    qDebug()<<"get MachineList Info";
    //查询有多少模具文件---返回的是当前在线的模具文件
    class GetMessage *temp_getMessage = Singleton<class GetMessage>::Instance();
    vector<QString> allMoldFile;
    allMoldFile = temp_getMessage->getMoldFileNames();
    //扩展为两位
    int ReqTypeNum = (buf[0]-'0')*10+(buf[1]-'0');
    QString ReqTypeNum_s = QString::fromStdString(to_string(ReqTypeNum));
    if(ReqTypeNum_s.size()==1){
        ReqTypeNum_s = "0"+ReqTypeNum_s;
    }
    QString res= ReqTypeNum_s;
    for(auto c:allMoldFile){
        if(c!="None"){
            c =c+',';
            res+=c;
        }
    }
    //test
    //res= ReqTypeNum_s;
    //res.append("MACH08,");
    //res.append("C02,");
    //res.append("C08,");

    return {res};
}

/*  获取历史区间
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(0)     ||   machineLength    ||  machineName    ||  returnDataType   ||year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |       04       ||      1             ||        s        ||     00            ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +--------------------------------------------------------------------------------------------------------------------------------------+
 */
vector<QString> ReceiveOperator::getHistoryInfo(QByteArray buf){
    qDebug()<<"get region Info";
    //扩展为两位
    int ReqTypeNum = (buf[0]-'0')*10+(buf[1]-'0');
    QString ReqTypeNum_s = QString::fromStdString(to_string(ReqTypeNum));
    if(ReqTypeNum_s.size()==1){
        ReqTypeNum_s = "0"+ReqTypeNum_s;
    }

    //QString res= QString::fromStdString(to_string(ReqTypeNum));

    //组装指令
    QString buff = buf;
    qDebug()<<"buff: "<<buff;

    int nameLength = (buf.at(2)-'0')*10+(buf.at(3)-'0'); //机台的长度
    string machineName = buff.mid(4,nameLength).toStdString();        //机台的名字
    //扩展为两位
    QString nameLength_s = QString::fromStdString(to_string(nameLength));
    if(nameLength_s.size()==1){
        nameLength_s = "0"+nameLength_s;
    }


    QString dataType = buff.mid(4+nameLength,2);         //选择的数据类型
    qDebug()<<"dataType: "<<dataType;

    string year = buff.mid(6+nameLength,4).toStdString();
    string month = buff.mid(10+nameLength,2).toStdString();
    string day = buff.mid(12+nameLength,2).toStdString();
    string hour = (buff.mid(14+nameLength,2)).toStdString();
    string minute = (buff.mid(16+nameLength,2)).toStdString();
    string second = (buff.mid(18+nameLength,2)).toStdString();
    string startTime = year+'-'+month+'-'+day+" "+hour+":"+minute+":"+second;


    string year_e = buff.mid(20+nameLength,4).toStdString();
    string month_e = buff.mid(24+nameLength,2).toStdString();
    string day_e = buff.mid(26+nameLength,2).toStdString();
    string hour_e = (buff.mid(28+nameLength,2)).toStdString();
    string minute_e = (buff.mid(30+nameLength,2)).toStdString();
    string second_e = (buff.mid(32+nameLength,2)).toStdString();
    string endTime = year_e+'-'+month_e+'-'+day_e+" "+hour_e+":"+minute_e+":"+second_e;

    //qDebug()<<"machineName: "<<machineName<<"dataType: "<<dataType<<"year: "<<year<<"month: "<<month<<"day: "<<day<<"hour: "<<hour<<"minute: "<<minute<<"second："<<second;

    QString res= ReqTypeNum_s+dataType+nameLength_s+QString::fromStdString(machineName);

    sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
    //执行数据库查询指令
    vector<pair<QString,float>> selectedData;
    selectedData =  temp_sqlServer->queryHistoryInfo(machineName,ReceiveOperator::m_dataTypeTable[dataType.toInt()],startTime,endTime);

    qDebug()<<"selectedSize: "<<selectedData.size();

    //按照一定的规则，序列化查询的数据
    int num = selectedData.size();
    for(int i=0;i<num;i++){
        auto c = selectedData[i];
        string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
        res += QString::fromStdString(onedata);
    }

    QString res2 = getDetectInfo("history",startTime,endTime,0,machineName);

    return  {res,res2};
}

vector<QString> ReceiveOperator::setDetectInfo(QByteArray buf){
    QString buff = buf;
    qDebug()<<"buff: "<<buff;

    int nameLength = (buf.at(2)-'0')*10+(buf.at(3)-'0'); //机台的长度
    string machineName = buff.mid(4,nameLength).toStdString();        //机台的名字
    //扩展为两位
    QString nameLength_s = QString::fromStdString(to_string(nameLength));
    if(nameLength_s.size()==1){
        nameLength_s = "0"+nameLength_s;
    }

    string year = buff.mid(4+nameLength,19).toStdString();
    //cout<<year<<endl;

    sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
    //执行数据库查询指令
    vector<pair<QString,float>> selectedData;
    temp_sqlServer->markDectMold(machineName,year);


    return {""};
}




/*  获取标记点信息
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |  reqType(0)     ||   machineLength    ||  machineName    ||  returnDataType   ||year-month-day hour:minute:second val,year-month-day hour:minute:second val,
 *  +------------++------------------------------------------------------------------------------------------------------------------------+
 *  |       05        ||      1             ||        s        ||     00            ||2021-09-29 16:04:34 26.234301,2021-09-29 16:03:09 26.751200,
 *  +--------------------------------------------------------------------------------------------------------------------------------------+
 */
//使用bind 函数....执行不同的命令emmm，但是又不知道是哪一种type
QString ReceiveOperator::getDetectInfo(string type,string startTime,string endTime,int moldCnt,string machineName){
    if(type=="history"){
        sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
        vector<pair<QString,float>> selectedData;
        selectedData =  temp_sqlServer->selectHistoryMoldDect(machineName,ReceiveOperator::m_dataTypeTable[3],startTime,endTime);

        QString reqType = "05";
        int len = machineName.size();

        QString nameLength_s = QString::fromStdString(to_string(len));
        if(nameLength_s.size()==1){
            nameLength_s = "0"+nameLength_s;
        }

        QString res= reqType + "00"+nameLength_s +QString::fromStdString(machineName);
        int num = selectedData.size();
        for(int i=0;i<num;i++){
            auto c = selectedData[i];
            string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
            res += QString::fromStdString(onedata);
        }

        return  res;


    }else if(type=="least"){

       sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
       vector<pair<QString,float>> selectedData;
       selectedData =  temp_sqlServer->selectLeastMoldDect(machineName,ReceiveOperator::m_dataTypeTable[3],moldCnt);

       QString reqType = "05";
       int len = machineName.size();

       QString nameLength_s = QString::fromStdString(to_string(len));
       if(nameLength_s.size()==1){
           nameLength_s = "0"+nameLength_s;
       }



       QString res= reqType + "00"+nameLength_s +QString::fromStdString(machineName);
       int num = selectedData.size();
       for(int i=0;i<num;i++){
           auto c = selectedData[i];
           string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
           res += QString::fromStdString(onedata);
       }


       qDebug()<<res<<endl;

       //m_tcpServer->sendData(ip,port,ans);

       return  res;

    }else if(type=="region"){
        sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
        vector<pair<QString,float>> selectedData;

        selectedData =  temp_sqlServer->selectDataMoldDect(machineName,ReceiveOperator::m_dataTypeTable[3],startTime);

        QString reqType = "05";
        int len = machineName.size();

        QString nameLength_s = QString::fromStdString(to_string(len));
        if(nameLength_s.size()==1){
            nameLength_s = "0"+nameLength_s;
        }



        QString res= reqType +"00" +nameLength_s +QString::fromStdString(machineName);
        int num = selectedData.size();
        for(int i=0;i<num;i++){
            auto c = selectedData[i];
            string onedata = c.first.toStdString() + " " +to_string(c.second)+",";
            res += QString::fromStdString(onedata);
        }


        qDebug()<<res<<endl;

        //m_tcpServer->sendData(ip,port,ans);

        return  res;

        //cout<<" "<<endl;
        //qDebug()<<QString::fromStdString(startTime);
    }
    return "";
}




















