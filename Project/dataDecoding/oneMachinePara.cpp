#include "oneMachinePara.h"
QLibrary qlib("GetFRSData.dll");
#include "FileSystemWatcher.h"

oneMachinePara::oneMachinePara(QString filePath,QString fileName,QString m_machineName,int MachineId,QObject*parent):QObject(parent),m_machineName(m_machineName),m_MachineId(MachineId){
    m_readDat = new ReadDat();
    m_writeToDb = new WriteToDb();
    m_writeToJson = new WriteToJson();
    m_fileManager = new FileManager();
    initParameter(filePath,fileName);
}

oneMachinePara::~oneMachinePara(){

}

/**
  * @brief  初始化参数,设置读取文件的路径，文件名，本台机台路径
  * @date   2021-05-21
  * @author hj
  */
void oneMachinePara::initParameter(QString filePath,QString fileName){
    m_readDat->setFilePath(filePath);
    m_readDat->setFileName(fileName);
    //getCurMachineMoldFile();  //fanuc服务器关闭之后，运行这一段会崩溃、没有反馈，无法解决...
    m_lastState = m_writeToJson->readJsonFile(m_moldfileName,objName);
    if(m_lastState.size()){
        m_readDat->setLastReadRow(3);
        m_writeToDb->setIsCreateTable(m_lastState[objName[0]]);
    }
    //如果有SESS0001.RSP[判断机台是否在线的响应的文件]，则删除
    m_machinePath = filePath;
    if(m_fileManager->isExit(m_machinePath,m_em63ConnectRsp)){
        m_fileManager->deleteFile(m_machinePath,m_em63ConnectRsp);
    }
    //如果有report1.data[机台返回每一个模次数据的文件],则删除，相当于每次重新寻找
    if(m_fileManager->isExit(m_machinePath,m_datFileName)){
        m_fileManager->deleteFile(m_machinePath,m_datFileName);
    }
    //在目标路径下放置通讯文件，注意需要先放置job文件再放置req文件
    sendReqFile(m_em63AbortJob);
    sendReqFile(m_em63GetInfoJob);
    sendReqFile(m_em63GetDataJob);
    sendReqFile(m_em63ConnectReq);
    sendReqFile(m_em63AbortJobReq);
}

/**
  * @brief  定时任务
  *         解析文件,存储数据，更新状态
  *         判断是否生成临时文件(FNC_report_1.Dat),文件被占用会出现？
  *         判断文件是否过大，是则发送em63请求文件,重新生成dat文件
  * @date   2021-05-21
  * @author hj
  */
void oneMachinePara::controlByUp(){
    //判断机器是否在线
    if(!m_isOnline){
        if(judgeIsOnLine()){
            sendReqFile(m_reqFileName);//发送请求文件
            m_isOnline = true;
            m_readDat->setLastReadRow(1);
            return ; //提前退出，euromap63响应需要留一个缓冲时间
        }else{
            sendReqFile(m_em63ConnectReq);//不然继续发送连接文件
            return ;
        }
    }
    //没有对应的数据库表
    if(!m_writeToDb->getIsCreateTable()){
        m_names.clear();
        m_readDat->readFirstLine(m_names);
        getCurMachineMoldFile();
        //当获取的模具名为空,或者没有读到文件，就不要创建数据库表了
        if(m_moldfileName=="" ||m_names.size()==0){
            return ;
        }
        m_writeToDb->createTableInDb(m_moldfileName,m_names);
    }else{
        m_vals.clear();
        m_dates.clear();
        m_times.clear();
        m_readDat->readNotReadedLines(m_vals,m_dates,m_times);
        if(m_dates.size()>0){
            emit MachineDataTimeUpdate(QString::fromStdString(m_times[0]),m_MachineId);
            //qDebug()<<"emit";
            getCurMachineMoldFile();//每次都需要获取对应的模具名
            qDebug()<<"m_moldFile"<<m_moldfileName;
            m_writeToDb->insertToDb(m_moldfileName,m_vals,m_dates,m_times);
            exportWaveDataByCmd(m_dates,m_times);
        }
    }
    updateJsonState();
    exceptionHandling();
    IsReSendReq();
    //updateJsonState();
}

/**
  * @brief  判断机台是否在线
  * @date   2021-05-21
  * @author hj
  */
bool oneMachinePara::judgeIsOnLine(){
    //判断是否存在响应文件
    if(m_fileManager->isExit(m_machinePath,m_em63ConnectRsp)){
        //解析这个文件
        if(check()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

/**
  * @brief  对返回的文件进行解析
  *         通过返回的字符串判断是否在线 "REQ_0001 PROCESSED;"
  * @date   2021-05-21
  * @author hj
  */
bool oneMachinePara::check(){
    ifstream op;
    string temppath = m_machinePath.toStdString()+"/"+m_em63ConnectRsp.toStdString();
    op.open(temppath);
    if(!op.is_open()){
        cout<<"read firstLine Failed"<<endl;
        return false;
    }
    string temp;
    getline(op,temp);
    if(temp == "REQ_0001 PROCESSED;")
        return true;
    return false;
}


/**
  * @brief  异常情况处理，处理存在FNC_report_1.dat文件的异常情况，先读取，然后删除，会生成新的临时文件吗？这是一个问题啊
  *         另一种异常情况，如果没有dat文件需要发送请求文件,不断的保持连接..
  *         当文件大于250行，读取完成后将其删除
  * @date
  * @author hj
  */
void oneMachinePara::exceptionHandling(){
    if(IsFncReportExit()){
        qDebug()<<"temp file is exit"<<endl;
        m_vals.clear();
        m_dates.clear();
        m_times.clear();
        m_readDat->readSpecialFile(m_fnc_tempFile,m_machinePath,m_vals,m_dates,m_times);
        m_writeToDb->insertToDb(m_machineName,m_vals,m_dates,m_times);
        deleteFncTempFile();
    }
}

/**
  * @brief 检查文件是否过大，减少读取文件的时间
  *        上次读取文件的行数大于10，删除文件
  *        注意当这个机台是断线的情况，删除了这个dat文件，并不会生成dat文件，还是原来的文件，如果不加判断就将读到的函数设置为1，则会反复读取
  *        添加一个判断条件，先将dat文件删除，产生了dat文件才说明生成了新的文件，将已经读过的行数设置为1
  * @date  2021-05-21
  * @author hj
  */
void oneMachinePara::IsReSendReq(){
    if(m_readDat->getLastReadRow()>50){
//        if(m_delay==false){
//            sendReqFile(m_em63AbortJobReq);
//            m_delay= true;
//            if(m_fileManager->isExit(m_machinePath,m_em63ConnectRsp))
//                m_fileManager->deleteFile(m_machinePath,m_em63ConnectRsp);
//            sendReqFile(m_em63ConnectReq);
//        }else{
//            if(judgeIsOnLine()){
//                sendReqFile(m_reqFileName);//发送请求文件
//                m_readDat->setLastReadRow(2);
//                updateJsonState();
//                m_delay = false;
//            }else{
//                sendReqFile(m_em63ConnectReq);//不然继续发送连接文件
//            }
//        }
        //保险起见先更改
        m_readDat->setLastReadRow(3);
        updateJsonState();

        emit restart(m_MachineId);
    }
}

/**
  * @brief 判断是否生成了临时文件(FNC_report_1.dat)，存在则返回true
  *        Fanuc软件的路径下有可能会生成临时文件
  *        导致之后的数据都会插入到临时文件中,而不会插入到report_1.dat文件中
  * @date  2021-05-21
  * @author hj
  */
bool oneMachinePara::IsFncReportExit(){
    if(m_fileManager->isExit(m_machinePath,m_fnc_tempFile)){
        return true;
    }
    return false;
}

/**
  * @brief  判断机器路径下是否有dat文件
  * @date   2021-6-15
  * @author hj
  */
bool oneMachinePara::IsDatFileExit(){
    if(m_fileManager->isExit(m_machinePath,m_datFileName)){
        return true;
    }
    return false;
}

/**
  * @brief  删除临时产生的新文件
  * @date   2021-06-10
  * @author hj
  */
void oneMachinePara::deleteFncTempFile(){
    if(m_fileManager->isExit(m_machinePath,m_fnc_tempFile)){
        m_fileManager->deleteFile(m_machinePath,m_fnc_tempFile);
    }
}

/**
  * @brief  当路径里面没有dat文件时需要发送请求文件，不断的保持连接
  * @date
  * @author hj
  */
void oneMachinePara::sendReqFile(QString fileName){
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    applicationDirPath += "/em63";
    m_fileManager->copyFile(applicationDirPath,m_machinePath,fileName);
}

/**
  * @brief  将读取文件的状态写入json文件，记录的信息包括如下：
  *         是否创建了数据库表
  *         上一次读取到的行数
  * @date   2020-05-21
  * @author hj
  */
void oneMachinePara::updateJsonState(){
    m_lastState[objName[0]] = m_writeToDb->getIsCreateTable();
    m_lastState[objName[1]] = m_readDat->getLastReadRow();
    m_writeToJson->updateJsonFile(m_moldfileName,m_lastState);
}

/**
  * @brief  获取当前机器的名称
  * @date   2021-05-21
  * @author hj
  */
QString oneMachinePara::getMachineName(){
    return m_machineName;
}

/**
  * @brief  获取当前机器中的模具名
  * @date   2021-09-09
  * @author hj
  */
typedef DWORD  WINAPI (*CallType)(unsigned char* FactolinkName,unsigned char*MoniDataBuffer,DWORD BufferSize);
typedef DWORD  WINAPI (*CallById)(DWORD dwMachineID, unsigned char* MonitDataBuffer, DWORD BufferSize);
typedef DWORD  WINAPI (*GetCurrMoldFileByID)(DWORD MachineID,unsigned char *NameBuffer,DWORD NameBufferSize);

//extern QLibrary qlib;

GetCurrMoldFileByID getCurrMoldFileByID = (GetCurrMoldFileByID) qlib.resolve("GetCurrMoldFileNameByID");

void oneMachinePara::getCurMachineMoldFile(){
     GetCurrMoldFileByID getCurrMoldFileByID = (GetCurrMoldFileByID) qlib.resolve("GetCurrMoldFileNameByID");
     //分配一大片空间..
     DWORD dwMachineID  = m_MachineId;
     unsigned char a[1000000];
     QString moldFileName;
     DWORD buffersize = 6000;
     int ok =  getCurrMoldFileByID(dwMachineID,a,buffersize);
     string b=(char*)a;
     QString curMoldfileName = QString::fromStdString(b);
     replace(curMoldfileName.begin(), curMoldfileName.end(), '-', '_');
     //如果模具文件的开始字符是数字，起见添加一个字符A作为前缀
     if(curMoldfileName[0]>='0'&&curMoldfileName[0]<='9'){
         curMoldfileName ='A'+curMoldfileName;
     }
     //防止同一个机台更换了模具文件，导致没有数据库表项
    // qDebug()<<m_machinePath<<m_moldfileName<<" "<<curMoldfileName;
     if(m_moldfileName!="None" && m_moldfileName!= curMoldfileName){
        m_writeToDb->setIsCreateTable(false);
        //qDebug()<<"uuuus";
     }
     m_moldfileName = curMoldfileName;
     replace(m_moldfileName.begin(), m_moldfileName.end(), '-', '_');
}

/**
  * @brief  导出当前机器的波形数据、当em63检测到有新的模次数据输出时，默认将波形数据存储为模具名的路径下，暂时不考虑将模具文件进行分级！！！直接存储，但是需要优化
  * 初始化机器自动创建机器路径、没有这个路径则创建这个文件架子
  * @date   2021-09-09
  * @author hj
  */
void oneMachinePara::exportWaveDataByCmd(vector<string> m_dates,vector<string> m_times){

    //获取当前文件的执行路径
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    //获取当前时间、并拆分为模具名、年、月、日、时、分、秒
    string year = m_dates[0].substr(0,4);
    string month = m_dates[0].substr(4,2);
    string day = m_dates[0].substr(6,2);
    string hour = m_times[0].substr(0,2);
    string minute = m_times[0].substr(3,2);
    string second = m_times[0].substr(6,2);
    //将文件导出到哪个路径
    string moldfile_path = applicationDirPath.toStdString() + "/"+  m_moldfileName.toStdString();
    string year_path = moldfile_path +"/" +year;
    string month_path = year_path + "/" + month;
    string day_path = month_path + "/" + day;
    //检查是否存在当前模次所需要的路径,没有则创建路径
    m_fileManager->isPathExit(QString::fromStdString(day_path));

    string fasthestDisTime = year+month+day+hour+minute+second;

    //第一次进入表示为空，则将当前的文件路径设置为监听路径
    if(m_lastExportPath==""){
        FileSystemWatcher::addWatchPath(QString::fromStdString(day_path));
    }

    if(m_lastExportTime=="" || m_lastExportPath ==""){
        m_lastExportTime = fasthestDisTime;
        m_lastExportPath = day_path;
        return ;
    }

    //依据接口执行对应的导出文件命令，注意导出时间是上一次的时间，因为fanuc服务器接收到数据的时间与euromap63接收到当前模次的信息是不同步的
    string path = string(" /Path:") + "\""+m_lastExportPath+"\"";
    string r = string("E:/FANUC/MOLD24/BIN/M24WaveAnalyzer/M24WaveAnalyzer.exe") + " /Export" + " /Machine:" + \
               to_string(m_MachineId)+ " /DrawStartDate:" + m_lastExportTime\
               +" /Item:880008803" +" /StartFlag:InjectStart /EndFlag:ExtrdEnd" + path;

   // qDebug()<<"export cmd:"<<QString::fromStdString(r);

    //开启一个非阻塞的进程执行导出文件的命令

   // WinExec(r.c_str(),SW_NORMAL);
    addOneCmdIntoQueue(r);

    //如果刚过凌晨的点，跳转到第二天，导出文件的路径变会更换，需要将新的路径放置到监听目录下面，同时取消旧的监听目录
    if(m_lastExportPath != day_path){
        FileSystemWatcher::addWatchPath(QString::fromStdString(day_path));
        m_delete_path = m_lastExportPath;
        m_lastExportTime = fasthestDisTime;
        m_lastExportPath = day_path;
        return ; //直接退出、等待一个周期再来取消原来的监听路径
    }

    //置位做标记
    if(m_delete_path != ""){
        FileSystemWatcher::removeWatchPath(QString::fromStdString(m_delete_path));
        m_delete_path = "";
    }

    //更新应该导出的路径以及导出哪一段之后的时间
    m_lastExportTime = fasthestDisTime;
    m_lastExportPath = day_path;
}

/*
 * 返回当前机台的模具名
 */
QString  oneMachinePara::getMoldFileName(){
    return m_moldfileName;
}
