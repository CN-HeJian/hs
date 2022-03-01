#ifndef SQLSERVICE_H
#define SQLSERVICE_H
#include <map>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <vector>
using namespace std;

class  sqlServer{
public:
    //构造函数
    sqlServer();
    //连接sql文件，没有sql文件则创建一个
    bool connect(QString name,const QString &type = "QSQLITE");
    //删除一张表
    bool deleteTable(QString TableName);
    //将数据添加进表
    bool addDataToTable(QString TableName,vector<vector<float>> m_variables,vector<string> dates,vector<string> times);
    //创建一个table，传入一个key，value
    bool createTable(QString TableName,vector<string> columns);
    //依据命令从数据库选择数据
    vector<pair<QString,float>> selectData(string machineName, string paraType,string startTime );
    vector<pair<QString,float>> selectDataMoldDect(string machineName, string paraType,string startTime );
    vector<pair<QString,float>> selectLeastData(string machineName, string paraType,int cnt );
    vector<pair<QString,float>> selectLeastMoldDect(string machineName, string paraType,int cnt);
    vector<pair<QString,float>> queryHistoryInfo(string machineName, string paraType,string startTime,string endTime);
    vector<pair<QString,float>> selectHistoryMoldDect(string machineName, string paraType,string startTime,string endTime);
    //往已经存在的表项中添加一列，不指定这一列的类型
    void addOneColunmInExitTable(QString TableName,QString columnName);
    //默认为float...简化操作..累了累了
    void updateTableField(QString TableName,QString columnName,float value,int count_val,QString dateTime);
    void unlink();
    void markDectMold(string machineName, string DetectMoldTime);
private:
    QSqlDatabase m_sqlDatabase;
    QSqlQuery m_sqlQuery;
private:
    QString hostname="localhost";
    int port=3306;
    QString databasename = "inject.db";
    QString linkName;
    QString name = "yyds";
    QString username = "root";
    QString pass = "123456";
};

#endif
