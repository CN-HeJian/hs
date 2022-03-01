#ifndef GETMESSAGE_H
#define GETMESSAGE_H

#include <QDataStream>
#include <QDebug>
#include "QCoreApplication"
#include <QStandardPaths>
#include <QDir>
#include "dataDecoding/oneMachinePara.h"
#include "dataDecoding/fileManager.h"
#include <QTimer>
#include <queue>

class GetMessage: public QObject{
    Q_OBJECT
public:
    //初始化槽函数
    void initSignalSlot();
    //初始化参数
    void initParameter();
    //初始化每个任务
    oneMachinePara* initOneMachine(QString machinePath,QString fileName,QString machineName,int machineId);
    GetMessage(QObject *parent = Q_NULLPTR);
    ~GetMessage();
    //初始化
    void init();
    vector<QString> getMoldFileNames();
    void deleteMachine(int);
    void waveDataUpdate(QString,QString );
private:
    QTimer *m_Time;
    FileManager m_fileManager;

    vector<oneMachinePara*> m_machineParas;//每个机器的任务，方便管理
    vector<string> m_machineNames;//机器名称，用户配置的名字
    vector<QString> m_machinePaths;//机器路径,也就是用户输入的路径

    QString m_em63_folder_name = "em63";
    QString m_em63JobFile = "report_1.JOB";
    QString m_em63ReqFile = "SESS0000.REQ";
    QString m_em63ConnectReq = "SESS0001.REQ";
    QString m_readFileName= "report_1.dat";
    //取消任务的请求文件名
    QString m_em63AbortJobReq = "SESS0002.REQ";
    //取消任务的job文件名
    QString m_em63AbortJob = "ABORT.JOB";
    //获取信息的job文件名
    QString m_em63GetInfoJob = "GETINFO.JOB";
    void addMachine(string,QString,oneMachinePara*);
    void initEM63RequestFile();
    void replaceFile(QString);

    //保存任务的队列
    queue<string> exportWaveCmd;

private slots:
    void getInjectionMessage();
    void MachineDataTimeUpdate(QString,int);
    void addOneCmdIntoQueue(string);
    void restart(int);
signals:
    void MachineDataTimeUpdate_GetMessage(QString,int);
    void waveDataUpdate_getMessage(QString,int);
    void restart_getM(int);
};

#endif
