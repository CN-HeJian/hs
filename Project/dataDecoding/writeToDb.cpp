#include "writeToDb.h"
#include "./tool/templateSingle.hpp"
#include "./database/sqlServe.h"

WriteToDb::WriteToDb(){

}

/**
  * @brief  往数据库表中插入数据
  * @date   2021-05-21
  * @author hj
  */
void WriteToDb::insertToDb(QString m_machineName , vector<vector<float>> m_vals,vector<string> dates,vector<string> times){
    if(m_isCreateTable){
        sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
        temp_sqlServer->addDataToTable(m_machineName,m_vals,dates,times);
    }
}

/**
  * @brief  创建数据库表,
  *         1、先判断表是否创建
  *         2、数据库对字段有特殊要求，先对字段做一次处理
  *         3、找到数据库实例，创建数据库表
  * @date   2021-05-21
  * @author hj
  */
void WriteToDb::createTableInDb(QString m_machineName , vector<string> m_names){
    if(!m_isCreateTable){
        sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
        operateColumns(m_names);
        if(m_names.size()){
            temp_sqlServer->createTable(m_machineName,m_names);
            m_isCreateTable = true;
        }
    }
}

/**
  * @brief  对数据库字段进行操作
  *         如果存在@，删除@
  *         将"["替换为"_"
  *         删除"]"
  * @date   2021-05-21
  * @author hj
  */
void WriteToDb::operateColumns(vector<string> &fields){
    for(auto &field:fields){
        if(field[0]=='@'){
            field = field.erase(0, 1);
        }
        replace(field.begin(), field.end(), ',', '_');
        replace(field.begin(), field.end(), '[', '_');
        char chars[] = "]";
        for (unsigned int i = 0; i < strlen(chars); ++i){
          field.erase (std::remove(field.begin(), field.end(), chars[i]), field.end());
        }
    }
}

/*
 * 在已有的数据库表项中的某一条记录再加一条属性
 *
 */
//首先需要知道那个表中，需要添加的属性、哪一行记录、需要增加的内容是什么？？？、




/**
  * @brief  设置是否创建数据库表
  * @date   2021-05-21
  * @author hj
  */
void WriteToDb::setIsCreateTable(int flag){
    m_isCreateTable = flag;
}

/**
  * @brief  获取是否创建数据库表文件
  * @date   2021-05-21
  * @author hj
  */
bool WriteToDb::getIsCreateTable(){
    return m_isCreateTable;
}
