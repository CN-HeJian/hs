#include "HscOnlineMonitorAction.h"
#include "ui_HscOnlineMonitorAction.h"

HscOnlineMonitorAction::HscOnlineMonitorAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscOnlineMonitorAction)
{
    ui->setupUi(this);

    initView();
}

HscOnlineMonitorAction::~HscOnlineMonitorAction()
{
    delete ui;
}

void HscOnlineMonitorAction::bindWidget(QWidget *widget)
{
    m_widget = dynamic_cast<HscOnlineMonitor *>(widget);
}

void HscOnlineMonitorAction::initView()
{
    // 监控设置
    auto act_collectSetting = new QAction;
    act_collectSetting->setIcon(QIcon(":/resource/icon/curve.png"));
    act_collectSetting->setText("设置");
    ui->tBtn_collectSetting->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_collectSetting->setDefaultAction(act_collectSetting);

    // 数据采集
    auto act_connect = new QAction;
    act_connect->setIcon(QIcon(":/resource/icon/curve.png"));
    act_connect->setText("连接");
    ui->tBtn_connect->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_connect->setDefaultAction(act_connect);

    // 曲线显示
    auto act_plot = new QAction;
    act_plot->setIcon(QIcon(":/resource/icon/curve.png"));
    act_plot->setText("绘图");
    ui->tBtn_plot->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_plot->setDefaultAction(act_plot);

    // 监控设置
    auto act_monnitor = new QAction;
    act_monnitor->setIcon(QIcon(":/resource/icon/curve.png"));
    act_monnitor->setText("监控");
    ui->tBtn_monitorSetting->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_monitorSetting->setDefaultAction(act_monnitor);

    // ch设置
    auto act_ch = new QAction;
    act_ch->setIcon(QIcon(":/resource/icon/curve.png"));
    act_ch->setText("ch");
    ui->tBtn_chSetting->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_chSetting->setDefaultAction(act_ch);

    // 实时曲线
    auto act_realtime = new QAction;
    act_realtime->setIcon(QIcon(":/resource/icon/curve.png"));
    act_realtime->setText("实时");
    ui->tBtn_realtime->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_realtime->setDefaultAction(act_realtime);

    // 重写曲线
    auto act_rewrite = new QAction;
    act_rewrite->setIcon(QIcon(":/resource/icon/curve.png"));
    act_rewrite->setText("重写");
    ui->tBtn_rewrite->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_rewrite->setDefaultAction(act_rewrite);

    // 积分值
    auto act_integral = new QAction;
    act_integral->setIcon(QIcon(":/resource/icon/curve.png"));
    act_integral->setText("积分值");
    ui->tBtn_integral->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_integral->setDefaultAction(act_integral);

    // 峰值
    auto act_peak = new QAction;
    act_peak->setIcon(QIcon(":/resource/icon/curve.png"));
    act_peak->setText("峰值");
    ui->tBtn_peak->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tBtn_peak->setDefaultAction(act_peak);

}

void HscOnlineMonitorAction::on_tBtn_collectSetting_clicked()
{
    // 采集设置
    m_widget->collectSetting();
}

void HscOnlineMonitorAction::on_tBtn_connect_clicked()
{
    //  开启连接
    m_widget->connectMqtt();
}

void HscOnlineMonitorAction::on_tBtn_plot_clicked()
{
    // 开启绘图
    m_widget->startPlot();
}

void HscOnlineMonitorAction::on_tBtn_monitorSetting_clicked()
{
    // 监控设置
    m_widget->realTimeMonitor()->monitorSetting();
}

void HscOnlineMonitorAction::on_tBtn_chSetting_clicked()
{
    m_widget->setSubWindow(0);
}

void HscOnlineMonitorAction::on_tBtn_realtime_clicked()
{
    m_widget->setSubWindow(1);
}

void HscOnlineMonitorAction::on_tBtn_rewrite_clicked()
{
    m_widget->setSubWindow(2);
}

void HscOnlineMonitorAction::on_tBtn_integral_clicked()
{
    m_widget->setSubWindow(3);
}

void HscOnlineMonitorAction::on_tBtn_peak_clicked()
{
    m_widget->setSubWindow(4);
}
