#include "HscMonitorItem.h"
#include "ui_HscMonitorItem.h"

#include <QDebug>

#define GBOX(i) ui->gBox_##i
#define CBOX(i) ui->cBox_##i
#define DSBOXLOWERPRES(i) ui->dSbox_lower_pres_##i
#define DSBOXUPPERPRES(i) ui->dSbox_upper_pres_##i
#define DSBOXLOWERTIME(i) ui->dSbox_lower_time_##i
#define DSBOXUPPERTIME(i) ui->dSbox_upper_time_##i

HscMonitorItem::HscMonitorItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscMonitorItem)
{
    ui->setupUi(this);
    initView();
    initSignalSlots();
}

HscMonitorItem::~HscMonitorItem()
{
    delete ui;
}

void HscMonitorItem::initializer(int index)
{
    m_model = &HscMonitorSettingModel::monitorSettingModel[index];

    for (auto i(0); i<m_model->listOfEigenvalueMonitor.count(); ++i) {
        auto &item = m_model->listOfEigenvalueMonitor[i];
        m_groupBoxs[i]->setChecked(item.enable);
        m_comboBoxs[i]->setCurrentText(item.type);
        m_lowerPresSpins[i]->setValue(item.lowerPres);
        m_lowerPresSpins[i]->setRange(0, 500);
        m_lowerPresSpins[i]->setSingleStep(0.01);
        m_upperPresSpins[i]->setValue(item.upperPres);
        m_upperPresSpins[i]->setRange(0, 500);
        m_upperPresSpins[i]->setSingleStep(0.01);
        m_lowerTimeSpins[i]->setValue(item.lowerTime);
        m_lowerTimeSpins[i]->setSingleStep(0.01);
        m_upperTimeSpins[i]->setValue(item.upperTime);
        m_upperTimeSpins[i]->setSingleStep(0.01);
    }
}

void HscMonitorItem::setTopleft(int monitor, double upperPres, double lowerTime)
{
    m_upperPresSpins[monitor]->setValue(upperPres);
    m_lowerTimeSpins[monitor]->setValue(lowerTime/1000);
}

void HscMonitorItem::setBottomright(int monitor, double lowerPres, double upperTime)
{
    m_lowerPresSpins[monitor]->setValue(lowerPres);
    m_upperTimeSpins[monitor]->setValue(upperTime/1000);
}

void HscMonitorItem::initView()
{
    m_groupBoxs << GBOX(1) << GBOX(2) <<  GBOX(3) << GBOX(4);
    m_comboBoxs << CBOX(1) << CBOX(2) <<  CBOX(3) << CBOX(4);
    m_lowerPresSpins << DSBOXLOWERPRES(1) << DSBOXLOWERPRES(2) << DSBOXLOWERPRES(3) << DSBOXLOWERPRES(4);
    m_upperPresSpins << DSBOXUPPERPRES(1) << DSBOXUPPERPRES(2) << DSBOXUPPERPRES(3) << DSBOXUPPERPRES(4);
    m_lowerTimeSpins << DSBOXLOWERTIME(1) << DSBOXLOWERTIME(2) << DSBOXLOWERTIME(3) << DSBOXLOWERTIME(4);
    m_upperTimeSpins << DSBOXUPPERTIME(1) << DSBOXUPPERTIME(2) << DSBOXUPPERTIME(3) << DSBOXUPPERTIME(4);
}

void HscMonitorItem::initSignalSlots()
{
    for (auto i(0); i<m_comboBoxs.count(); ++i) {
        connect(m_groupBoxs[i], SIGNAL(clicked(bool)), this, SLOT(onGroupBoxClicked(bool)));
        connect(m_comboBoxs[i], SIGNAL(currentTextChanged(QString)), this, SLOT(onComboBoxCurrentTextChanged(QString)));
        connect(m_lowerPresSpins[i], SIGNAL(valueChanged(double)), this, SLOT(onLowerPresChange(double)));
        connect(m_upperPresSpins[i], SIGNAL(valueChanged(double)), this, SLOT(onUpperPresChange(double)));
        connect(m_lowerTimeSpins[i], SIGNAL(valueChanged(double)), this, SLOT(onLowerTimeChange(double)));
        connect(m_upperTimeSpins[i], SIGNAL(valueChanged(double)), this, SLOT(onUpperTimeChange(double)));
    }
}

void HscMonitorItem::onComboBoxCurrentTextChanged(QString val)
{
    int index = m_comboBoxs.indexOf(static_cast<QComboBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].type = val;

}

void HscMonitorItem::onGroupBoxClicked(bool val)
{
    int index = m_groupBoxs.indexOf(static_cast<QGroupBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].enable = (val == true ? 1 : 0);

    emit updatePlotView();
}

void HscMonitorItem::onLowerPresChange(double val)
{
//    qDebug () << val;
    int index = m_lowerPresSpins.indexOf(static_cast<QDoubleSpinBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].lowerPres = val;

    emit updatePlotView();
}

void HscMonitorItem::onUpperPresChange(double val)
{
//    qDebug () << val;
    int index = m_upperPresSpins.indexOf(static_cast<QDoubleSpinBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].upperPres = val;

    emit updatePlotView();
}

void HscMonitorItem::onLowerTimeChange(double val)
{
//    qDebug () << val;
    int index = m_lowerTimeSpins.indexOf(static_cast<QDoubleSpinBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].lowerTime = val*1000;

    emit updatePlotView();
}

void HscMonitorItem::onUpperTimeChange(double val)
{
//    qDebug () << val;
    int index = m_upperTimeSpins.indexOf(static_cast<QDoubleSpinBox *>(sender()));
    m_model->listOfEigenvalueMonitor[index].upperTime = val*1000;

    emit updatePlotView();
}
