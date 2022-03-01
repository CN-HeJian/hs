#include "controlCenter.h"

ControlCenter::ControlCenter(uint16_t tcpPort,QObject*parent):QObject(parent),m_tcpPort(tcpPort){
    m_SqlServer = Singleton<sqlServer>::Instance();
    m_getMessage = Singleton<class GetMessage>::Instance();
    m_tcpServer = new TcpServer(m_tcpPort);
    initTcpServer();
    //initMachine();
    initSignalSlot();
}

ControlCenter::~ControlCenter(){

}

/**
  * @brief 初始化槽函数
  * @date 2021-5-21
  * @author hj
  */
void ControlCenter::initSignalSlot(){
    connect(m_tcpServer,SIGNAL(getOneRequestFromClient(QByteArray,QString,uint16_t)),this,SLOT(getOneRequestFromClient(QByteArray,QString,uint16_t)));
    connect(m_getMessage,SIGNAL(MachineDataTimeUpdate_GetMessage(QString,int)),this,SLOT(MachineDataTimeUpdate_GetMessage(QString,int)));
    connect(m_getMessage,SIGNAL(waveDataUpdate_getMessage(QString,int )),this,SLOT(waveDataUpdate_getMessage(QString,int)));
    connect(m_getMessage,SIGNAL(restart_getM(int )),this,SLOT(restart_getM(int)));
}

//软件重启一台机器
void ControlCenter::restart_getM(int id){
    qDebug()<<"restart Machine"<<id;
    deleteMa(id);
    initMachine(id,m_disk);
}


void ControlCenter::MachineDataTimeUpdate_GetMessage(QString date,int id){
    qDebug()<<"control"<<date<<id;
    emit MachineDataTimeUpdate_ControlCenter(date,id);
}

void ControlCenter::waveDataUpdate_getMessage(QString date ,int id){
    emit waveDataTimeUpdate_ControlCenter(date,id);
}


/**
  * @brief tcp服务监听端口
  * @date  2021-5-21
  * @author hj
  */
void ControlCenter::initTcpServer(){
    m_tcpServer->listenPort(m_tcpPort);
}

/**
  * @brief 添加机台、由于机台可能会换模具、因此使用模具可能效果更好、但对em63来说是有其他需求的
  * @date 2021-5-21
  * @author hj
  */
oneMachinePara* ControlCenter::initMachine(int id,QString path){
    qDebug()<<"id"<<id;
    m_disk = path;
    QString full_path = path+":\\FANUC\\EM63\\INTERFACE\\MACH"+QString::number(id);
    QString machineName = "MACH"+QString::number(id);
    qDebug()<<"full_path:"<<full_path<<"machinename: "<<machineName;
    return m_getMessage->initOneMachine(full_path,"report_1.dat",machineName,id);
}

/*
 * 取消一个机台的数据传输！！
*/
void ControlCenter::deleteMa(int id){
    m_getMessage->deleteMachine(id);
}

/*
 * 收到来自客户端的请求并处理
*/
void ControlCenter::getOneRequestFromClient(QByteArray buff,QString ip,uint16_t port){
    //qDebug()<<"ControlCenter"<<buff;
    unsigned int ReqTypeNum = (buff[0]-'0')*10+(buff[1]-'0');
    qDebug()<<"ReqTypeNum:"<<ReqTypeNum;
    vector<QString> ans = m_receiveOperator.m_handler_table[ReqTypeNum](buff);

    for(auto c:ans){
        m_tcpServer->sendData(ip,port,c);
        //QTime time;
        //time.start();
        //while(time.elapsed()<5000);
        //break;
    }
}
