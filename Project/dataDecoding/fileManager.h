#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include "QDir"
#include "QCoreApplication"
#include <QDebug>

class FileManager
{
public:
    FileManager();
    void copyFile(QString startPath,QString endPath,QString fileName);
    void deleteFile(QString startPath,QString fileName);
    void createFolder(QString path,QString folderName);
    bool isExit(QString path,QString name);
    bool isPathExit(QString path);
};

#endif // FILEMANAGER_H
