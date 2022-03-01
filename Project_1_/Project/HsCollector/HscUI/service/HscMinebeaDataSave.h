#ifndef HSCMINEBEADATASAVE_H
#define HSCMINEBEADATASAVE_H

#include <QObject>
#include "HscSqlite.h"
#include "HscCollectDataModel.h"

class HscMinebeaDataSave : public QObject
{
    Q_OBJECT

public:
    HscMinebeaDataSave(QObject *parent = nullptr);
    ~HscMinebeaDataSave();

signals:

public slots:
    void onStartCollect();
    void saveData(QList<HscCollectDataModel> *list);

private:
    HscSqlite m_databaseManage;

    QString tb_name;
    QString columns;
    QString column_headers;
    QString detail_tb_name;
    QString detail_columns;
    QString detail_column_headers;
};

#endif // HSCMINEBEADATASAVE_H
