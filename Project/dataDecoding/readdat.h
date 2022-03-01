#ifndef READDAT_H
#define READDAT_H
#include <string>
#include <vector>
#include <QString>
using namespace std;

class ReadDat
{
public:
    ReadDat();
    void setFilePath(QString path);
    void setFileName(QString name);
    void setLastReadRow(long lastReadRow);
    //读取文件第一行获取变量名
    void readFirstLine(vector<string>& names);
    //读取文件之后的名字
    void readNotReadedLines(vector<vector<float>> &m_vals,vector<string> &dates,vector<string> &times);
    //获取读取到哪一行
    int getLastReadRow();
    //获取文件路径
    QString getFilePath();
    //读取某一行
    void readSpecialFile(QString fileName,QString filePath,vector<vector<float>> &m_vals,vector<string> &dates,vector<string> &times);
private:
    //读取变量名
    void getVariableName(string names,const string m_delimiters,vector<string> &m_names);
    //读取变量值
    void getVaribleVal(string vals,const string m_delimiters,vector<float> &m_vals,vector<string> &dates,vector<string> &times);
    //文件读取路径
    QString m_filePath;
    //文件名
    QString m_fileName;
    //全局路径
    QString  m_pathAddName;
    //字符串分割符号
    string m_delimiters=",";
    //记录上一次读取的行数
    int m_lastReadRow=-1;
    //传入需要接受的函数
    void addFilePathAndName();
};

#endif // READDAT_H
