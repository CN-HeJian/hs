#ifndef HSCRIBBON_H
#define HSCRIBBON_H

#include <QMenuBar>
#include <QPropertyAnimation>

#include "MainWindow.h"
//#include "HscOnlineMonitorAction.h"
#include "HscMachineAnalysisAction.h"
#include "HscSettingAction.h"

namespace Ui
{
    class HscRibbon;
};

class HscRibbon : public QMenuBar
{
    Q_OBJECT

public:

    HscRibbon(QWidget *parent);
    ~HscRibbon();

public:
    void bindTabView(int index, QWidget *widget);

private:
    void initRibbon();

signals:

public slots:

private slots:

    void expandTab();
    void hideTab();
    void onTabChanged();
    void clickTab();

    void on_tabWidgetMenuBar_currentChanged(int index);

protected:

private:
    Ui::HscRibbon *ui;

    MainWindow *m_mainWindow;
    QPropertyAnimation m_opacityAnimation;
    QPropertyAnimation m_animationHideBar;

    bool m_bExpandStaus;

    //HscOnlineMonitorAction *m_onlineMonitor = nullptr;
    HscMachineAnalysisAction *m_machineAnalysis = nullptr;
    HscSettingAction *m_setting = nullptr;

};

#endif // HSCRIBBON_H
