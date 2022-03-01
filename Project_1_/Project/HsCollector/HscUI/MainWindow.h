#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include "HscOnlineMonitor.h"
#include "HscMachineAnalysis.h"
#include "HscSoftwareSetting.h"

//#include "HscCollectSettingModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public:
    void setCurrentTabView(int index);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void initialize();
    void initSignalSlots();


private:
    Ui::MainWindow *ui;

    // 采集模型
//    HscCollectSettingModel m_settingModel;
    // 监控设置模型
   // HscMonitorSettingModel m_monitorSettingModel;

    // 各窗口界面
   // HscOnlineMonitor *m_onlineMonitor = nullptr;
    HscMachineAnalysis *m_machineAnalysis = nullptr;
    HscSoftwareSetting *m_softwareSetting = nullptr;
};

#endif // MAINWINDOW_H
