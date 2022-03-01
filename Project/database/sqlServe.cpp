#include "sqlServe.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
//初始化数据库
sqlServer::sqlServer(){
        linkName  = "inject";
//    if (QSqlDatabase::contains(databasename))//判断testConnect连接是否存在并连接
//    {
//        m_sqlDatabase = QSqlDatabase::database(databasename);
//        qDebug()<<"y";
//    }else{
//        m_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE",databasename);
//        m_sqlDatabase.setDatabaseName(databasename);
//        m_sqlDatabase.setHostName(hostname);
//        m_sqlDatabase.setUserName(username);
//        m_sqlDatabase.setPassword(pass);
//        m_sqlDatabase.setPort(port);
//        m_sqlDatabase.open();
//        QString sql_cmd = "create database if not exists "+databasename;
//        m_sqlDatabase.exec(sql_cmd);
//        if(!m_sqlDatabase.open())
//            qDebug() << "Error: Failed to connect database." << m_sqlDatabase.lastError();
//        m_sqlDatabase.close();
//        qDebug()<<"o";
//        //unlink();
//    }
}

//连接数据库
bool sqlServer::connect(QString linkName, const QString &type){

    //linkName = "yyds";
        qDebug()<<linkName<<endl;
        if(QSqlDatabase::contains(linkName)){
            m_sqlDatabase = QSqlDatabase::database(linkName);
            qDebug()<<"g";
        }else{
            m_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE",linkName);
            m_sqlDatabase.setDatabaseName(databasename);
            m_sqlDatabase.setHostName(hostname);
            m_sqlDatabase.setUserName(username);
            m_sqlDatabase.setPassword(pass);
            m_sqlDatabase.setPort(port);
            m_sqlDatabase.open();
            QString sql_cmd = "create database if not exists "+databasename;
            m_sqlDatabase.exec(sql_cmd);
            if(!m_sqlDatabase.open())
                qDebug() << "Error: Failed to connect database." << m_sqlDatabase.lastError();
            m_sqlDatabase.close();
        }

        if (!m_sqlDatabase.open()) {
            qDebug()<<"fail to connect mysql:"<<m_sqlDatabase.lastError().text();
            return  false;
          // qFatal("failed to connect.");
        }


//    if(m_sqlDatabase.open())
//    {
//        return true;
//    }
   // m_sqlDatabase.close();
  //  m_sqlDatabase.removeDatabase("QSQLITE");
   // QSqlDatabase::removeDatabase(databasename);
    return true;
}

//创建一张表
bool sqlServer::createTable(QString TableName,vector<string> columns){
    if(TableName==""){
        return false;
    }
    connect(linkName,"QSQLITE");
   // m_sqlDatabase = QSqlDatabase::database(databasename);
   // m_sqlDatabase.open();


    QSqlQuery m_sqlQuery(m_sqlDatabase);
    //选定数据库
    QString sqlCmd = "use inject";
    m_sqlQuery.exec(sqlCmd);
    //创建表
    sqlCmd = "create table " + TableName + "(id INTEGER primary key AUTOINCREMENT,DATE text not null ,COUNT real";
    for(size_t i=3;i<columns.size();++i){
        QString temp = "," + QString::fromStdString(columns[i]) + " real";
        sqlCmd +=temp;
    }
    sqlCmd+=")";


    if(!m_sqlQuery.exec(sqlCmd))
    {
        qDebug()<<"Failed to create table:"<<m_sqlQuery.lastError();
        //unlink();
        //qDebug()<<"Failed cmd:"<<sqlCmd;
        return false;
    }
    else
    {
        qDebug()<<"success to create table:" <<TableName;
    }
    //unlink();

    addOneColunmInExitTable(TableName,"injectionPhasePressAvg");

    unlink();

    return true;
}
//往表中添加数据
bool sqlServer::addDataToTable(QString TableName,vector<vector<float>> m_variables,vector<string> dates,vector<string> times){
    if(TableName==""){
       // unlink();
        return  false;
    }
    //m_sqlDatabase = QSqlDatabase::database(databasename);
   // m_sqlDatabase.open();
    connect(linkName,"QSQLITE");

    QSqlQuery m_sqlQuery(m_sqlDatabase);
    //选定数据库
    QString sqlCmd = "use inject";
    m_sqlQuery.exec(sqlCmd);
    for(size_t i=0;i<m_variables.size();++i){
        vector<float> oneValue = m_variables[i];
        //数据库表最后一项填充
        oneValue.push_back(0);

       // string date = dates[i];
       // string time = times[i];
        string date = dates[i].substr(0,4)+"-"+dates[i].substr(4,2)+"-"+dates[i].substr(6,2)+" "+times[i];

        QString temp = QString::fromStdString(date);

        sqlCmd = "INSERT INTO " + TableName + " VALUES (NULL," + "'"+ QString::fromStdString(date) + "'"  +",";
        for(size_t i=0 ;i<oneValue.size()-1;++i){
            QString temp =  QString("%2").arg(oneValue[i]) + ",";
            sqlCmd +=temp;
        }
        sqlCmd+=QString("%2").arg(oneValue[oneValue.size()-1]) + ")";
    }
       // qDebug()<<sqlCmd<<endl;
        if(!m_sqlQuery.exec(sqlCmd))
        {
            qDebug()<<"Failed to insert table:"<<m_sqlQuery.lastError();
           // qDebug()<<"failed cmd:"<<sqlCmd;
            //unlink();
            //return false;
        }
        else
        {
            qDebug()<<"success to a record "<<TableName;
        }

    unlink();
    return true;
}
//删除一张表
bool sqlServer::deleteTable(QString TableName){
   // m_sqlDatabase = QSqlDatabase::database(databasename);
   // m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    //选定数据库
    QString sql_cmd = "DROP TABLE "+ TableName;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to delete table:"<<m_sqlQuery.lastError();
        //unlink();
        return false;
    }
    else
    {
        qDebug()<<"success to delete";
    }
    unlink();
    return true;
}


//往表项中添加一列，未指定这一列的类型
void sqlServer::addOneColunmInExitTable(QString TableName,QString columnName){
    //TODO : check the table is exit
    //add
    //m_sqlDatabase = QSqlDatabase::database(databasename);
   // m_sqlDatabase.open();
    //connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    QString sql_cmd = "ALTER TABLE "+ TableName +" ADD COLUMN "+ columnName + " float";
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to add column:"<<m_sqlQuery.lastError();

    }
    else
    {
        qDebug()<<TableName<<"add "<<columnName<<" success";
    }
   // unlink();
}

//更新表中某一个字段的值
void sqlServer::updateTableField(QString TableName,QString columnName,float value,int count_val,QString dateTime ){


   //qDebug()<<"value "<<value<<endl;

    //TODO : check the table is exit
    //add
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);

    QString sql_cmd = "UPDATE "+ TableName +" SET "+ columnName + " = " + QString("%1").arg(value,0,'G',6) + " WHERE DATE > " + "'"+dateTime +"'"+ " AND ActCntCyc == " + QString("%2").arg(count_val);

    //qDebug()<<"sql update: "<<TableName<<sql_cmd<<endl;


    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to update avgPress:"<<m_sqlQuery.lastError();

    }
    else
    {
        qDebug()<<"success to update: "<<TableName<<"avgPress";
    }


    unlink();
    //m_sqlDatabase.removeDatabase(databasename);
}



//查询最近区间的数据
vector<pair<QString,float>> sqlServer::selectData(string machineName, string paraType,string startTime){
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    string cmd = "SELECT date, " + paraType + " FROM " + machineName + " where DATE >="  + "'"  + startTime +"'";
    QString sql_cmd =    QString::fromStdString(cmd);
    qDebug()<<sql_cmd;

    vector<pair<QString,float>> selectedData;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
    }
    else
    {
        while(m_sqlQuery.next()){
            //获取query所指向的记录集合中的编号
            int rowNum = m_sqlQuery.at();
            int columnNum = m_sqlQuery.record().count();
            //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
            int fieldNo = m_sqlQuery.record().indexOf("date");
            //获取name属性的值
            QString name = m_sqlQuery.value(fieldNo).toString();
            float val = m_sqlQuery.value(1).toFloat();
            selectedData.push_back(make_pair(name,val));
        }
    }
    unlink();
    return selectedData;
}

vector<pair<QString,float>> sqlServer::selectDataMoldDect(string machineName, string paraType,string startTime ){

    connect(linkName,"QSQLITE");
   QSqlQuery m_sqlQuery(m_sqlDatabase);
   string cmd = "SELECT date, " + paraType + " FROM " + machineName + " WHERE " + paraType + " == 3 "   +" and"+  " DATE >="  + "'"  + startTime+"'";
   QString sql_cmd =    QString::fromStdString(cmd);
   qDebug()<<sql_cmd;

   vector<pair<QString,float>> selectedData;
   if(!m_sqlQuery.exec(sql_cmd))
   {
       qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
   }
   else
   {
       while(m_sqlQuery.next()){
           //获取query所指向的记录集合中的编号
           int rowNum = m_sqlQuery.at();
           int columnNum = m_sqlQuery.record().count();
           //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
           int fieldNo = m_sqlQuery.record().indexOf("date");
           //获取name属性的值
           QString name = m_sqlQuery.value(fieldNo).toString();

           float val = m_sqlQuery.value(1).toFloat();
           //qDebug()<<"name: "<<name<<"val: "<<val;

           selectedData.push_back(make_pair(name,val));
       }
   }
   unlink();
   return selectedData;

}

//查询最近模次的数据
vector<pair<QString,float>> sqlServer::selectLeastData(string machineName, string paraType,int cnt){
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    string cmd = "SELECT date, " + paraType + " FROM " + machineName + " ORDER by date DESC LIMIT "  + to_string(cnt);
    QString sql_cmd =    QString::fromStdString(cmd);
    qDebug()<<sql_cmd;

    vector<pair<QString,float>> selectedData;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
    }
    else
    {
        while(m_sqlQuery.next()){
            //获取query所指向的记录集合中的编号
            int rowNum = m_sqlQuery.at();
            int columnNum = m_sqlQuery.record().count();
            //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
            int fieldNo = m_sqlQuery.record().indexOf("date");
            //获取name属性的值
            QString name = m_sqlQuery.value(fieldNo).toString();

            float val = m_sqlQuery.value(1).toFloat();
            //qDebug()<<"name: "<<name<<"val: "<<val;

            selectedData.push_back(make_pair(name,val));
        }
    }
    unlink();
    return selectedData;
}

//查询最近模次内标记的点
vector<pair<QString,float>> sqlServer::selectLeastMoldDect(string machineName, string paraType,int cnt){
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    string cmd = "select  DATE , "+paraType +" from "+machineName+" WHERE "+ paraType+" ==3 AND DATE IN (select date "+ paraType +" from " + machineName +" ORDER BY date desc limit "+ to_string(cnt) + " )";
    //string cmd = "SELECT date, " + paraType + " FROM " + machineName + " WHERE " + paraType + " == 3 " +   " ORDER by date DESC LIMIT "  + to_string(cnt);
    QString sql_cmd =    QString::fromStdString(cmd);
    qDebug()<<sql_cmd;

    vector<pair<QString,float>> selectedData;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
    }
    else
    {
        while(m_sqlQuery.next()){
            //获取query所指向的记录集合中的编号
            int rowNum = m_sqlQuery.at();
            int columnNum = m_sqlQuery.record().count();
            //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
            int fieldNo = m_sqlQuery.record().indexOf("date");
            //获取name属性的值
            QString name = m_sqlQuery.value(fieldNo).toString();

            float val = m_sqlQuery.value(1).toFloat();
            //qDebug()<<"name: "<<name<<"val: "<<val;

            selectedData.push_back(make_pair(name,val));
        }
    }
    unlink();
    return selectedData;
}


//查询历史数据
vector<pair<QString,float>> sqlServer::queryHistoryInfo(string machineName, string paraType,string startTime,string endTime){
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
     connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);
    string cmd = "SELECT date, " + paraType + " FROM " + machineName + " where DATE >="  + "'"  + startTime +"'"+" and"+ " DATE <= " + "'"+endTime +"'";
    QString sql_cmd =    QString::fromStdString(cmd);
    qDebug()<<sql_cmd;

    vector<pair<QString,float>> selectedData;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
    }
    else
    {
        while(m_sqlQuery.next()){
            //获取query所指向的记录集合中的编号
            int rowNum = m_sqlQuery.at();
            int columnNum = m_sqlQuery.record().count();
            //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
            int fieldNo = m_sqlQuery.record().indexOf("date");
            //获取name属性的值
            QString name = m_sqlQuery.value(fieldNo).toString();
            float val = m_sqlQuery.value(1).toFloat();
            selectedData.push_back(make_pair(name,val));
        }
    }
    unlink();
    return selectedData;
}

vector<pair<QString,float>> sqlServer::selectHistoryMoldDect(string machineName, string paraType,string startTime,string endTime){
    //
    qDebug()<<"d"<<endl;
    connect(linkName,"QSQLITE");
   QSqlQuery m_sqlQuery(m_sqlDatabase);
   string cmd = "SELECT date, " + paraType + " FROM " + machineName + " WHERE " + paraType + " == 3 "  +" and"+  " DATE >="  + "'"  + startTime +"'"+" and"+ " DATE <= " + "'"+endTime+"'";
   //string cmd = "SELECT date, " + paraType + " FROM " + machineName + " where DATE >="  + "'"  + startTime +"'"+" and"+ " DATE <= " + "'"+endTime +"'";
  // string cmd = "SELECT date, " + paraType + " FROM " + machineName + " WHERE " + paraType + " == 3 " +   " ORDER by date DESC LIMIT "  + to_string(cnt);
   QString sql_cmd =    QString::fromStdString(cmd);
   qDebug()<<sql_cmd;

   vector<pair<QString,float>> selectedData;
   if(!m_sqlQuery.exec(sql_cmd))
   {
       qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
   }
   else
   {
       while(m_sqlQuery.next()){
           //获取query所指向的记录集合中的编号
           int rowNum = m_sqlQuery.at();
           int columnNum = m_sqlQuery.record().count();
           //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
           int fieldNo = m_sqlQuery.record().indexOf("date");
           //获取name属性的值
           QString name = m_sqlQuery.value(fieldNo).toString();

           float val = m_sqlQuery.value(1).toFloat();
           //qDebug()<<"name: "<<name<<"val: "<<val;

           selectedData.push_back(make_pair(name,val));
       }
   }
   unlink();
   return selectedData;
}


//更该数据
void sqlServer::markDectMold(string machineName, string DetectMoldTime){
    //m_sqlDatabase = QSqlDatabase::database(databasename);
    //m_sqlDatabase.open();
    connect(linkName,"QSQLITE");
    QSqlQuery m_sqlQuery(m_sqlDatabase);

    qDebug()<<"sqlServer: "<<QString::fromStdString(machineName)<<QString::fromStdString(DetectMoldTime)<<endl;

    float value=3;
    QString sql_cmd = "UPDATE "+ QString::fromStdString(machineName) +" SET OPT2PeakToPack  = "  + QString("%1").arg(value,0,'G',6) + " WHERE DATE = " +'"'+QString::fromStdString(DetectMoldTime)+'"';
//    //string cmd = "SELECT date, " + paraType + " FROM " + machineName + " where DATE >="  + "'"  + startTime +"'"+" and"+ " DATE <= " + "'"+endTime +"'";
//    QString sql_cmd =    QString::fromStdString(cmd);
    qDebug()<<sql_cmd;

//    vector<pair<QString,float>> selectedData;
    if(!m_sqlQuery.exec(sql_cmd))
    {
        qDebug()<<"Failed to select table:"<<m_sqlQuery.lastError();
    }
//    else
//    {
//        while(m_sqlQuery.next()){
//            //获取query所指向的记录集合中的编号
//            int rowNum = m_sqlQuery.at();
//            int columnNum = m_sqlQuery.record().count();
//            //获取"name"属性所在列的编号，列从左向右编号，最左边的编号为0
//            int fieldNo = m_sqlQuery.record().indexOf("date");
//            //获取name属性的值
//            QString name = m_sqlQuery.value(fieldNo).toString();
//            float val = m_sqlQuery.value(1).toFloat();
//            selectedData.push_back(make_pair(name,val));
//        }
//    }

    unlink();
    //return selectedData;
}





void sqlServer::unlink(){
    QString connection;
    connection = m_sqlDatabase.connectionName();
    m_sqlDatabase.close();
    m_sqlDatabase = QSqlDatabase();
    m_sqlDatabase.removeDatabase(connection);
}


