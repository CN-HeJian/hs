#ifndef WRITETODB_H
#define WRITETODB_H
#include <QString>
#include <unordered_map>
#include <vector>

using namespace std;

class WriteToDb
{
public:
    WriteToDb();
    bool getIsCreateTable();
    void setIsCreateTable(int flag);
    void createTableInDb(QString m_machineName , vector<string> m_names);
    //插入数据库文件
    void insertToDb(QString m_machineName , vector<vector<float>> m_names,vector<string> dates,vector<string> times);
private:
    //是否创建了数据库表
    bool m_isCreateTable=false;//---insertToDbTask
    //对字段的处理---使其符合数据库文件要求
    void operateColumns(vector<string> &fields);
    //创建一个主键
};

#endif // WRITETODB_H
