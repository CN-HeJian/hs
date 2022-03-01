#include "getMessage.h"

GetMessage::GetMessage(QObject*parent):QObject(parent){
    m_Time = new QTimer(this);
    init();
}



GetMessage::~GetMessage(){

}

void GetMessage::init(){
    initSignalSlot();
    initParameter();
    initEM63RequestFile();
}

void GetMessage::initSignalSlot(){
    connect(m_Time,SIGNAL(timeout()),this,SLOT(getInjectionMessage()));
    //connect();
}

/**
  * @brief  拷贝em63所需要的配置文件，job文件和req文件到工程目录下
  *         debug目录下的em63即是这一段函数生成
  * @date   2021-05-21
  * @author hj
  */
void GetMessage::initEM63RequestFile(){
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    m_fileManager.createFolder(applicationDirPath,m_em63_folder_name);
    QDir temp(QDir::currentPath());
    temp.cd("../");
    QString  start = temp.absolutePath()+"/"+m_em63_folder_name;

    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63ReqFile);
    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63JobFile);
    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63ConnectReq);
    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63AbortJobReq);
    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63AbortJob);
    m_fileManager.copyFile(start,applicationDirPath+"./"+ m_em63_folder_name,m_em63GetInfoJob);
}

/**
  * @brief  创建一个机台，同时也就会开启读取任务，不管机台是否在线
  *         添加机台到机器列表中，包括机器名字，机器路径，机器参数
  * @date   2021-05-21
  * @author hj
  */
oneMachinePara* GetMessage::initOneMachine(QString machinePath,QString fileName,QString machineName,int machineId){
    oneMachinePara* m_oneMachinePara = new oneMachinePara(machinePath,fileName,machineName, machineId);
    //波形数据的时间更新了
    connect(m_oneMachinePara,SIGNAL(MachineDataTimeUpdate(QString,int)),this,SLOT(MachineDataTimeUpdate(QString,int)));
    //将需要执行的命令加到执行队列里面去
    connect(m_oneMachinePara,SIGNAL(addOneCmdIntoQueue(string)),this,SLOT(addOneCmdIntoQueue(string)));
    //重启一台机器
    connect(m_oneMachinePara,SIGNAL(restart(int)),this,SLOT(restart(int)));

    addMachine(machineName.toStdString(),machinePath,m_oneMachinePara);
    return m_oneMachinePara;
}


void GetMessage::restart(int id){
    //qDebug()<<"cmd"<<QString::fromStdString(cmd);
    emit restart_getM(id);
}



void GetMessage::addOneCmdIntoQueue(string cmd){
    qDebug()<<"cmd"<<QString::fromStdString(cmd);
    exportWaveCmd.push(cmd);
}

//直接调用！！！
void GetMessage::MachineDataTimeUpdate(QString date,int id){
    qDebug()<<"date"<<date;
    emit MachineDataTimeUpdate_GetMessage(date,id);
}

/**
  * @brief  中断设置，程序定时执行解析dat文件
  *         时间间隔单位为毫秒，当前设置为5秒
  * @date   2021-05-21
  * @author hj
  */
void GetMessage::initParameter(){
    m_Time->start(8000);
}

/**
  * @brief  定时槽函数，执行所有的机台任务,相当于中断,主任务
  *         解析新
  * @date   2012-05-21
  * @author hj
  */
void GetMessage::getInjectionMessage(){
    //直接从队列里面拿到命令进行数据导出
    if(!exportWaveCmd.empty()){
        string cmd = exportWaveCmd.front();
        WinExec(cmd.c_str(),SW_NORMAL);
        exportWaveCmd.pop();
    }

    for(auto c:m_machineParas){
        qDebug()<<"c:" <<c->getMachineName()<<endl;
        c->controlByUp();
    }
}

/**
  * @brief  添加机器名，路径名，创建的机器到向量中
  * @date   2021-05-21
  * @author hj
  */
void  GetMessage::addMachine(string name,QString path,oneMachinePara *oneMachineParas){
    m_machineNames.push_back(name);
    m_machinePaths.push_back(path);
    m_machineParas.push_back(oneMachineParas);
}

/**
  * @brief  删除机器名，机器路径，以及这一台机台
  * @date   2021-05-21
  * @author hj
  */
void GetMessage::deleteMachine(int id){
    for(size_t i=0;i<m_machineNames.size();++i){
        if(m_machineParas[i]->m_MachineId==id){
            m_machineNames.erase(m_machineNames.begin()+int(i));
            m_machinePaths.erase(m_machinePaths.begin()+int(i));
            m_machineParas.erase(m_machineParas.begin()+int(i));
        }
    }
}

/**
  * @brief  返回所有的模具名，客户端发送刷新机台指令时会调用此函数
  * @date   2021-10-10
  * @author hj
  */
vector<QString> GetMessage::getMoldFileNames(){
    vector<QString> res;
    for(auto c:m_machineParas){
        QString c_name = c->getMoldFileName();
        res.push_back(c_name);
    }
    return res;
}

void GetMessage::waveDataUpdate(QString tableName,QString date){
    qDebug()<<"tableName"<<tableName<<"date"<<date;
    for(size_t i=0;i<m_machineNames.size();++i){
       qDebug()<<m_machineParas[i]->getMachineName();
        if(m_machineParas[i]->getMoldFileName() == tableName){

           emit waveDataUpdate_getMessage(date,m_machineParas[i]->m_MachineId);
           return ;
        }
    }
}
