#include "readDat.h"
#include <QElapsedTimer>
#include <fstream>
#include <QDebug>
#include <iostream>
#include <unordered_map>

ReadDat::ReadDat(){

}

/**
  * @brief  解析第一行，用来创建数据库表
  * @date   2021-05-21
  * @author hj
  */
void ReadDat::readFirstLine(vector<string> &names){
    ifstream op;
    op.open(m_pathAddName.toStdString());
    if(!op.is_open()){
        cout<<"read firstLine Failed"<<endl;
    }
    string temp;
    if(getline(op,temp))
    getVariableName(temp,",",names);
    m_lastReadRow = 1;
    op.close();
}

/**
  * @brief  从第二行开始解析，解析数据用来存入数据库中
  * @date   2021-05-21
  * @author hj
  */
void ReadDat::readNotReadedLines(vector<vector<float>> &m_vals,vector<string> &dates,vector<string> &times){
    if(m_lastReadRow==-1){
        return ;
    }
    ifstream op;
    op.open(m_pathAddName.toStdString());
    if(!op.is_open()){
        cout<<"read remainLines Failed"<<endl;
        qDebug()<<m_filePath;
        return ;
    }
    int currentRow = 1;
    string skipTemp;
    //getline(op,skipTemp);
    while(currentRow<=m_lastReadRow){
        getline(op,skipTemp);
        currentRow++;
    }
    string SVals;
    vector<float> currentVals;
    while(getline(op,SVals)){
        currentVals.clear();
        getVaribleVal(SVals,",",currentVals,dates,times);
        m_vals.emplace_back(currentVals);
        if(currentVals.size()!=0){
            currentRow++;
        }
    }
    m_lastReadRow = currentRow-1;
    op.close();
}

/**
  * @brief  解析某一个文件，某一行
  * @date
  * @author hj
  */
void ReadDat::readSpecialFile(QString fileName,QString filePath,vector<vector<float>> &m_vals,vector<string> &dates,vector<string> &times){
    ifstream op;
    QString temp_pathAddName = filePath+"\\"+fileName;
    op.open(temp_pathAddName.toStdString());
    if(!op.is_open()){
        //cout<<"readNotReadedLines Failed"<<endl;
    }
    string SVals;
    getline(op,SVals);
    vector<float> currentVals;
    while(getline(op,SVals)){
        currentVals.clear();
        getVaribleVal(SVals,",",currentVals,dates,times);
        m_vals.emplace_back(currentVals);
    }
    op.close();
}

/**
  * @brief  解析读到的第一行字符串，将字符串拆分
  *         在最后加上一个分隔符号",",方便解析
  *         注意特殊情况,[1,4]这种是一体的，不能单纯依赖","来分割
  * @date   2021-05-21
  * @author hj
  */
void ReadDat::getVariableName(string temp,const string m_delimiters,vector<string> &m_names){
    temp +=m_delimiters;
    string::size_type head = 0;
    bool singular_flag = false;
    for(string::size_type i=0;i<temp.size();++i){
        if(temp[i]=='[')
            singular_flag = true;
        else if(temp[i]==']')
            singular_flag = false;
        else if(temp[i]==',' && !singular_flag){
            string tempName = temp.substr(head, i-head);
            m_names.emplace_back(tempName);
            head = i+1;
        }
    }
}

/**
  * @brief  解析每一行的数值，获得每个变量所对应的值
  *         单独解析时间与日期，不能转为float
  * @date   2021-05-21
  * @author hj
  */
void ReadDat::getVaribleVal(string vals,const string delimiters,vector<float> &m_vals,vector<string> &dates,vector<string> &times){
    string::size_type lastPos = vals.find_first_not_of(delimiters,0);
    string::size_type pos = vals.find_first_of(delimiters,lastPos);
    string::size_type index=0;
    int cnt=0;
    while(string::npos!=pos || string::npos != lastPos){
        string sval = vals.substr(lastPos,pos-lastPos);
        if(cnt==1){
            dates.emplace_back(sval);
        }else if(cnt==2){
            times.emplace_back(sval);
        }else{
            m_vals.emplace_back(stof(sval));
        }
        lastPos = vals.find_first_not_of(delimiters, pos);
        pos = vals.find_first_of(delimiters, lastPos);
        index++;
        cnt++;
    }
}

/**
  * @brief  改变读取report_1.dat文件的路径
  * @date
  * @author hj
  */
void ReadDat::setFilePath(QString path){
    m_filePath = path;
    addFilePathAndName();
}

/**
  * @brief  改变读取的文件的名字
  * @date
  * @author hj
  */
void ReadDat::setFileName(QString name){
    m_fileName = name;
    addFilePathAndName();
}

/**
  * @brief  设置上一次读取到的行数
  * @date
  * @author hj
  */
void ReadDat::setLastReadRow(long lastReadRow){
    m_lastReadRow = lastReadRow;
}

/**
  * @brief  路径加上名字，组合为全名
  * @date
  * @author hj
  */
void ReadDat::addFilePathAndName(){
    m_pathAddName = m_filePath+"\\"+m_fileName;
}

/**
  * @brief  获取上一次读到的行数
  * @date
  * @author hj
  */
int ReadDat::getLastReadRow(){
    return m_lastReadRow;
}

/**
  * @brief  获取需要读取的文件的路径
  * @date
  * @author hj
  */
QString ReadDat::getFilePath(){
    return m_filePath;
}
