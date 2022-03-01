#ifndef WRITETOJSON_H
#define WRITETOJSON_H

#include <QString>
#include <unordered_map>
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QtCore/QCoreApplication>
using namespace std;

class WriteToJson
{
public:
    WriteToJson();
    void createJsonFile();
    void updateJsonFile(QString Obj,unordered_map<string,int> temp);
    unordered_map<string,int> readJsonFile(QString ObjName,vector<string> attributesNames);
private:
    QString m_fileName = "config.json";
};

#endif // WRITETOJSON_H
