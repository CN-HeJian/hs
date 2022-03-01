#ifndef ALLMACHINEWINDOW_H
#define ALLMACHINEWINDOW_H


#include <QWidget>
#include <QTableWidgetItem>
#include "./manager/controlCenter.h"
#include "./dataDecoding/oneMachinePara.h"
#include <QDebug>
#include <QToolButton>
#include <QTextEdit>

namespace Ui {
class allMachineWindow;
}

class allMachineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit allMachineWindow(QWidget *parent = nullptr);
    ~allMachineWindow();
    void uiInit();
private:
    Ui::allMachineWindow *ui;
    ControlCenter *m_manager;
    void newMachine(int id,QString path,QTableWidgetItem* item);
    void deleteMachine(int id,QTableWidgetItem* item);
    void startAll();
    vector<bool> IdUsed;
private slots:
    void slotHeaderClicked(int index);
    void on_pushButton_clicked();
    void getItem(QTableWidgetItem *);
    void saveConfig();
    void readConfig();
    void MachineDataTimeUpdate_ControlCenter(QString date,int id);
    void waveDataTimeUpdate_ControlCenter(QString date,int id);
};

#endif // ALLMACHINEWINDOW_H
