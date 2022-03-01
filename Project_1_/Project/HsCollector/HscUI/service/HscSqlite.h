#ifndef HSCSQLITE_H
#define HSCSQLITE_H

#include <QObject>
#include <QSqlDatabase>

class HscSqlite : public QObject
{
    Q_OBJECT

public:
    HscSqlite(QObject *parent = nullptr);

public:
    void openDatabase(QString db = "HscDatabase.db");
    void closeDatabase();
    QSqlDatabase *database() {
        return &m_database;
    }

    bool createTable(QString tb_name, QString columns);
    bool dropTable(QString tb_name);
    bool insertRecord(QString tb_name, QString columns, QString datas);
    bool updateRecord(QString tb_name, QString columns);
    bool delRecord(QString tb_name, QString columns);
    bool clearTable(QString tb_name);

private:
    void initDatabase();
    bool isTableExist(QSqlQuery &query, QString table);

private:
    QSqlDatabase m_database;

};


#endif // HSCSQLITE_H
