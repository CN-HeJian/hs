#include "HscMonitorSetting.h"
#include "ui_HscMonitorSetting.h"

#include "HscRealTimeMonitor.h"

HscMonitorSetting::HscMonitorSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscMonitorSetting)
{
    ui->setupUi(this);

    m_realTimeCurve = static_cast<HscRealTimeMonitor *>(parent);
    initView();
    initSignalSlots();
}

HscMonitorSetting::~HscMonitorSetting()
{
    delete ui;
}

void HscMonitorSetting::initView()
{
    // 10通道
    for (auto i(0); i<10; ++i) {
        HscMonitorItem *item = new HscMonitorItem(this);
        item->initializer(i);
        connect(item, &HscMonitorItem::updatePlotView, m_realTimeCurve, &HscRealTimeMonitor::plotItemRect);
        ui->stackedWidget->addWidget(item);
    }
}

void HscMonitorSetting::initSignalSlots()
{
    connect(m_realTimeCurve, &HscRealTimeMonitor::updateTopleft, this, &HscMonitorSetting::onUpdateTopleft);
    connect(m_realTimeCurve, &HscRealTimeMonitor::updateBottomright, this, &HscMonitorSetting::onUpdateBottomright);
}

void HscMonitorSetting::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    emit currentChannel(index);
}

void HscMonitorSetting::onUpdateTopleft(int channel, int monitor, double upperPres, double lowerTime)
{
    auto widget = static_cast<HscMonitorItem *>(ui->stackedWidget->widget(channel));
    widget->setTopleft(monitor, upperPres, lowerTime);
}

void HscMonitorSetting::onUpdateBottomright(int channel, int monitor, double lowerPres, double upperTime)
{
    auto widget = static_cast<HscMonitorItem *>(ui->stackedWidget->widget(channel));
    widget->setBottomright(monitor, lowerPres, upperTime);
}
