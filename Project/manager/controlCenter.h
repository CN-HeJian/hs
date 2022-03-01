#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H


//管理数据库文件
#include "./database/sqlServe.h"
//网络连接部分
#include "./dataTransfer/tcpServer.h"
//单例模式
#include "./tool/templateSingle.hpp"
//处理客户端请求部分
#include "receiveOperator.h"
//获取数据的task
#include "task/getMessage.h"



class ControlCenter: public QObject{
    Q_OBJECT
public:
    ControlCenter(uint16_t m_port,QObject *parent = Q_NULLPTR);
    friend class ReceiveOperator;
    //ControlCenter(uint16_t tcpPort);
    ~ControlCenter();
      oneMachinePara* initMachine(int id,QString path);
      void deleteMa(int MachId);
private:
    //网络连接部分
    TcpServer *m_tcpServer;
    //获取机台信息的任务
   // GetMessage *m_getMessage;
    //数据库成员
    sqlServer *m_SqlServer;
    //Tcp协议监听端口
    uint16_t m_tcpPort;
    //处理客户端请求
    ReceiveOperator m_receiveOperator;
    //获取机台信息的任务
    class GetMessage *m_getMessage;
    QString m_disk;
private:
    void initTcpServer();
    //oneMachinePara* initMachine();
    void initSignalSlot();
private slots:
    void getOneRequestFromClient(QByteArray,QString,uint16_t);
    void MachineDataTimeUpdate_GetMessage(QString,int);
    void waveDataUpdate_getMessage(QString,int );
    void restart_getM(int);
signals:
    void MachineDataTimeUpdate_ControlCenter(QString ,int);
    void waveDataTimeUpdate_ControlCenter(QString ,int);
};

#endif
