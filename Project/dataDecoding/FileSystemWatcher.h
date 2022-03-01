#ifndef FILE_SYSTEM_WATCHER_H
#define FILE_SYSTEM_WATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>


#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <QDir>
#include <QFileInfo>
#include <qDebug>
#include "tool/templateSingle.hpp"
#include "database/sqlServe.h"
#include "task/getMessage.h"

//Thread Pool
#include "tool/SafeQueue.h"
#include "tool/ThreadPool.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <QTime>
using namespace  std;

class GetMessage;

struct return_data{
    float avg;
    QString tableName;
    int count;
    QString dateTime;
};

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    static void addWatchPath(QString path);
    static void removeWatchPath(QString path);
    static void phaseCsv(string path,vector<vector<float>> &matrix);
    static float calculatePresAvg(vector<vector<float>> &matrix);

public slots:
    void directoryUpdated(const QString &path);  // 目录更新时调用，path是监控的路径
    void fileUpdated(const QString &path);   // 文件被修改时调用，path是监控的路径

private:
    explicit FileSystemWatcher(QObject *parent = 0);

private:
    static FileSystemWatcher *m_pInstance; // 单例
    QFileSystemWatcher *m_pSystemWatcher;  // QFileSystemWatcher变量
    QMap<QString, QStringList> m_currentContentsMap; // 当前每个监控的内容目录列表
    static return_data updateWaveFeature(QString,QString);
    ThreadPool pool;
    static unsigned int select;
    //static vector<bool> used;
   // static vector<string> connectName={"1","2","3"};
//signals:
  //  void waveDataUpdate(QString);

};

#endif // FILE_SYSTEM_WATCHER_H
