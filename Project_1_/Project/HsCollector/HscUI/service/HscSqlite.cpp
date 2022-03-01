#include "HscSqlite.h"

#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>

HscSqlite::HscSqlite(QObject *parent)
    : QObject(parent)
{

}

void HscSqlite::openDatabase(QString db)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(db);
    if(!m_database.open()) {
        qDebug() << m_database.lastError().text();
    }
    initDatabase();
}

void HscSqlite::closeDatabase()
{
    m_database.close();
}

bool HscSqlite::createTable(QString tb_name, QString columns)
{
    QSqlQuery query;
    bool success = query.exec(QString("create table %1 (%2, time datetime)").arg(tb_name).arg(columns));
    if(success){
        qDebug()<<QObject::tr("数据库表创建成功！\n");
        return true;
    } else {
        qDebug()<<QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

bool HscSqlite::dropTable(QString tb_name)
{
    QSqlQuery query;
    bool success=query.exec("drop table "+tb_name+" ;");
    if(success){
        qDebug()<<QObject::tr("数据库表删除成功！\n");
        return true;
    }
    else{
        qDebug()<<QObject::tr("数据库表删除失败！\n");
        return false;
    }
}

bool HscSqlite::insertRecord(QString tb_name, QString columns, QString datas)
{
    QSqlQuery query;

    QString insert_sql = QString("insert into %1 (%2) values (%3)").arg(tb_name).arg(columns).arg(datas);
    query.prepare(insert_sql);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        return false;
    }

    return true;
}

bool HscSqlite::clearTable(QString tb_name)
{
    QSqlQuery query;
    query.prepare(QString("delete from %1").arg(tb_name));
    bool success=query.exec();
    if(!success) {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("删除失败"));
        return false;
    }
    return true;
}

void HscSqlite::initDatabase()
{
    // 目录表
    QSqlQuery query;
    QString table = "collect_index";
    if (isTableExist(query, table)) {
        qDebug() << "table collect_index exist";
    } else {
        // 采集数据索引
        QString sql = "create table collect_index (id int primary key, mold_no varchar(30), created_at datetime)";
        bool success = query.exec(sql);
        if (success) {
            qDebug() << "table collect_index created success";
        } else {
            qDebug() << "table collect_index created failed";
        }
    }
}

bool HscSqlite::isTableExist(QSqlQuery &query, QString table)
{
    QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
    query.exec(sql);
    return query.next();
}
