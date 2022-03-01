#include "HscRibbon.h"
#include "ui_HscRibbon.h"

#include <QDebug>

const auto MINIMUM_HEIGHT = 22;

HscRibbon::HscRibbon(QWidget *parent)
    : ui(new Ui::HscRibbon)
    , m_mainWindow(dynamic_cast<MainWindow *>(parent))
{
    ui->setupUi(this);

    initRibbon();
}

HscRibbon::~HscRibbon()
{
    delete ui;
}

void HscRibbon::bindTabView(int index, QWidget *widget)
{
    if (index == 0) {
       // m_onlineMonitor->bindWidget(widget);
    } else if (index == 1) {
        m_machineAnalysis->bindWidget(widget);
    } else if (index == 2) {
        m_setting->bindWidget(widget);
    }
}

void HscRibbon::initRibbon()
{
    // 在线监控
//    m_onlineMonitor = new HscOnlineMonitorAction(this);
//    ui->tab->layout()->addWidget(m_onlineMonitor);

    // 机台分析
    m_machineAnalysis = new HscMachineAnalysisAction(this);
    ui->tab_5->layout()->addWidget(m_machineAnalysis);

    // 设置
//    m_setting = new HscSettingAction(this);
//    ui->tab_6->layout()->addWidget(m_setting);

    connect(ui->tabWidgetMenuBar, &QTabWidget::tabBarClicked, this, &HscRibbon::clickTab);
    connect(ui->tabWidgetMenuBar, &QTabWidget::currentChanged, this, &HscRibbon::onTabChanged);

    m_bExpandStaus = true;

    // 设置透明度渐变动画
    if (!m_opacityAnimation.targetObject()) {
        m_opacityAnimation.setTargetObject(m_mainWindow);
        m_opacityAnimation.setPropertyName("windowOpacity");
        m_opacityAnimation.setStartValue(1.0);
        m_opacityAnimation.setEndValue(1.0);
    }

    m_mainWindow->installEventFilter(this);


    // hj 隐藏多余tab
    ui->tabWidgetMenuBar->removeTab(0);


    ui->tabWidgetMenuBar->setStyleSheet("QTabBar::tab {width:0;color:transparent;}");
    ui->tabWidgetMenuBar->tabBar()->hide();
    //ui->tabWidgetMenuBar->removeTab(1);
   // ui->tabWidgetMenuBar->removeTab(2);
    //ui->tabWidgetMenuBar->removeTab(0);

}

void HscRibbon::expandTab()
{
    m_animationHideBar.setDirection(QAbstractAnimation::Backward);
    m_animationHideBar.start();

    m_bExpandStaus = true;
}

void HscRibbon::hideTab()
{
    if (!m_animationHideBar.targetObject()) {
        m_animationHideBar.setTargetObject(this);
        m_animationHideBar.setPropertyName("minimumHeight");
        m_animationHideBar.setStartValue(height());
        m_animationHideBar.setEndValue(MINIMUM_HEIGHT);
        m_animationHideBar.setEasingCurve(QEasingCurve::Linear);  // 缓和曲线风格
    }

    if (m_animationHideBar.state() == QAbstractAnimation::Running) {
        m_animationHideBar.stop();
    }

    m_animationHideBar.setDirection(QAbstractAnimation::Forward);
    m_animationHideBar.start();

    m_bExpandStaus = false;
}

void HscRibbon::clickTab()
{

    if(m_bExpandStaus == false) {
        expandTab();
        m_bExpandStaus = true;
    } else {
        hideTab();
        m_bExpandStaus = false;
    }
}


void HscRibbon::onTabChanged()
{
    if(m_bExpandStaus == false) {
        expandTab();
        m_bExpandStaus = true;
    }
}


void HscRibbon::on_tabWidgetMenuBar_currentChanged(int index)
{
    m_mainWindow->setCurrentTabView(index);
}
