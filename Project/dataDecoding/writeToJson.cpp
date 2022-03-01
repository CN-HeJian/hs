#include "writeToJson.h"

WriteToJson::WriteToJson()
{
    createJsonFile();
}


/**
  * @brief  创建config.json文件
  * @date   2021-05-21
  * @author hj
  */
void WriteToJson::createJsonFile(){
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    QFile file(applicationDirPath+"/"+m_fileName);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "json file create failed";
    }
}

/**
  * @brief  更新json文件
  *         原来有这项内容直接替换原来的内容
  *         没有则会新增
  * @date   2021-05-21
  * @author hj
  */
void WriteToJson::updateJsonFile(QString Name,unordered_map<string,int> temp){
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    QFile file(applicationDirPath+"/"+m_fileName);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "update json file failed 1";
    }
    QByteArray data = file.readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);
    QJsonObject rootobj=document.object();
    QJsonObject pageObject;
    for(auto iter = temp.begin();iter!=temp.end();++iter){
        pageObject.insert(QString::fromStdString(iter->first),iter->second);
    }
    QJsonObject json = document.object();
    json.insert(Name, QJsonValue(pageObject));
    QJsonDocument new_document;
    new_document.setObject(json);
    QByteArray array = new_document.toJson(QJsonDocument::Compact);
    file.remove();
    QFile new_file(applicationDirPath+"/"+m_fileName);
    if(!new_file.open(QIODevice::ReadWrite)) {
        qDebug() << "update json file failed 2";
    }
    new_file.write(new_document.toJson());
    new_file.close();
}

/**
  * @brief  解析json文件
  *         没有则返回空的哈希表
  * @date   2021-05-21
  * @author hj
  */
unordered_map<string,int> WriteToJson::readJsonFile(QString Name,vector<string> attributesNames){
    unordered_map<string,int> res;
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    QFile file(applicationDirPath+"/"+m_fileName);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "read json File failed";
    }
    QByteArray data = file.readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);
    QJsonObject rootobj=document.object();
    if(rootobj.contains(Name)){
         QJsonObject jsonObjectPost = rootobj[Name].toObject();
         for(size_t i=0;i<attributesNames.size();++i){
            res[attributesNames[i]] = jsonObjectPost.value(QString::fromStdString(attributesNames[i])).toInt();
         }
    }else{
        return {};
    }
    return res;
}
