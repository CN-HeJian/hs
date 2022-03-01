#ifndef ONESHOTPARA_H
#define ONESHOTPARA_H
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;

#include <QDebug>
#include "QCoreApplication"
//#include <./manager/controlCenter.h>
#include <windows.h>
//#include "FileSystemWatcher.h"
#include <QLibrary>
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <winbase.h>
using namespace std;
#include "readDat.h"
#include "writeToJson.h"
#include "writeToDb.h"
#include "fileManager.h"
#include <./tool/templateSingle.hpp>
#include "./database/sqlServe.h"

typedef struct  recordTime{
    string prelast="";
    string last="";
    string current="";
}recordTime_t;


class oneMachinePara: public QObject{
    Q_OBJECT
public:
    oneMachinePara(QString filePath,QString m_fileName,QString m_machineName,int MachineId,QObject *parent = Q_NULLPTR);
    ~oneMachinePara();
public:
    void controlByUp();
    QString getMachineName();
    QString getMoldFileName();
    int m_MachineId;
private:
    void initParameter(QString filePath,QString fileName);
    //control
    void exceptionHandling();
    void IsReSendReq();
    //judge
    bool IsFncReportExit();
    bool IsDatFileExit();
    bool judgeIsOnLine();
    bool check();
    //operate
    void deleteFncTempFile();
    void sendReqFile(QString fileName);
    void updateJsonState();
    void getCurMachineMoldFile();
    void exportWaveDataByCmd(vector<string> m_dates,vector<string> m_times);
private:
    vector<string> m_names;
    vector<vector<float>> m_vals;
    vector<string> m_dates;
    vector<string> m_times;
    //int m_MachineId;
    //机台的编号
    //标识符号，自定义的机器名称，一般设置为MACH01
    QString m_machineName;
    //机器原始路径，也就是FANUC软件的安装路径
    QString m_machinePath;
    //当前机器的模具名
    QString m_moldfileName="None";
    //上一次记录的时间戳
    string m_lastExportTime = "";
    string m_lastExportPath = "";
    recordTime_t m_recordTime;
    string m_delete_path="";
    //四个任务
    WriteToJson *m_writeToJson;
    WriteToDb *m_writeToDb;
    ReadDat  *m_readDat;
    FileManager *m_fileManager;
    //用于记录状态的标识
    vector<string> objName = {"isCreateTable","lastReadRow"};
    unordered_map<string,int> m_lastState;
    //当机器离线时，不能直接判断出来，删除目录的下dat文件，通过是否还会生成dat文件是否存在判断是否离线
    bool deleteOnetimeFlag=false;
    //Fanuc产生的临时文件的名字
    QString m_fnc_tempFile = "FNC_report_1.Dat";
    //生成文件的名字
    QString m_datFileName = "report_1.dat";
    //请求文件的名字
    QString m_reqFileName = "SESS0000.REQ";
    //连接请求文件名
    QString m_em63ConnectReq = "SESS0001.REQ";
    QString m_em63ConnectRsp = "SESS0001.RSP";
    //取消job的请求文件名
    QString m_em63AbortJobReq = "SESS0002.REQ";
    //取消任务的job文件名
    QString m_em63AbortJob = "ABORT.JOB";
    //获取信息的job文件名
    QString m_em63GetInfoJob = "GETINFO.JOB";
    //获取数据的job文件名
    QString m_em63GetDataJob = "report_1.job";
    //用来计次
    //int cnt = 0;
    //判断是否添加此延时
    bool m_delay=false;
    //保证第一次发送请求文件时注塑机是连接上的
    bool m_isOnline = false;
signals:
    void MachineDataTimeUpdate(QString,int);
    void addOneCmdIntoQueue(string);
    void restart(int);
};

#endif // ONESHOTPARA_H
