#ifndef HSCONLINEMONITORACTION_H
#define HSCONLINEMONITORACTION_H

#include <QWidget>

#include "HscOnlineMonitor.h"

namespace Ui {
class HscOnlineMonitorAction;
}

class HscOnlineMonitorAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscOnlineMonitorAction(QWidget *parent = nullptr);
    ~HscOnlineMonitorAction();

public:
    void bindWidget(QWidget *widget);

private:
    void initView();

private slots:
    void on_tBtn_collectSetting_clicked();
    void on_tBtn_connect_clicked();
    void on_tBtn_plot_clicked();
    void on_tBtn_monitorSetting_clicked();

    void on_tBtn_chSetting_clicked();
    void on_tBtn_realtime_clicked();
    void on_tBtn_rewrite_clicked();
    void on_tBtn_integral_clicked();
    void on_tBtn_peak_clicked();


private:
    Ui::HscOnlineMonitorAction *ui;

    HscOnlineMonitor *m_widget = nullptr;

};

#endif // HSCONLINEMONITORACTION_H
