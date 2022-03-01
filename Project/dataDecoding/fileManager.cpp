#include "fileManager.h"

FileManager::FileManager()
{

}

/**
  * @brief 文件拷贝
  * @date 2021-5-21
  * @author hj
  */
void FileManager::copyFile(QString startPath,QString endPath,QString fileName){
    if(QFile::exists(startPath+"/"+fileName)){
        if (QFile::exists(endPath+"/"+fileName))
        {
            QFile::remove(endPath+"/"+fileName);//先删除再拷贝
        }
        QFile::copy(startPath+"/"+fileName,endPath+"/"+fileName);
    }
}

/**
  * @brief  删除文件
  * @date   2021-5-21
  * @author hj
  */
void FileManager::deleteFile(QString path,QString fileName){
    if(QFile::exists(path+"/"+fileName)){
        QFile fileTemp(path+"/"+fileName);
        fileTemp.remove();
    }
}

/**
  * @brief  创建文件夹
  * @date   2021-5-21
  * @author hj
  */
void FileManager::createFolder(QString path,QString folderName){
    QDir *folder = new QDir;
    QString full = path +"/"+folderName;
    bool exist = folder->exists(full);
    if(!exist)
    {
       folder->mkdir(full);
    }
}

/**
  * @brief  判断文件是否存在
  * @date   2021-05-21
  * @author hj
  */
bool FileManager::isExit(QString path,QString name){
    QDir *folder = new QDir;
    QString full = path +"/"+name;
    return   folder->exists(full);
}

/**
  * @brief  判断路径是否存在、没有则创建
  * @date   2021-09-09
  * @author hj
  */
bool  FileManager::isPathExit(QString path){
    QDir dir;
    if(!dir.exists(path)){
        bool res = dir.mkpath(path);
    }
}
