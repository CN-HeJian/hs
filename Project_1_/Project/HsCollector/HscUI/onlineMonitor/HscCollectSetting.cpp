#include "HscCollectSetting.h"
#include "ui_HscCollectSetting.h"

#include <QDebug>
#include <QMessageBox>

HscCollectSetting::HscCollectSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscCollectSetting)
{
    ui->setupUi(this);

    this->initView();
}

HscCollectSetting::~HscCollectSetting()
{
    delete ui;
}

void HscCollectSetting::initView()
{
    // 连接设置
    m_connectSetting = new HscConnectSetting(this);
    ui->tabWidget->addTab(m_connectSetting, tr("连接设置"));

    // 传感器设置
    m_sensorSetting = new HscSensorSetting(this);
    ui->tabWidget->addTab(m_sensorSetting, tr("传感器设置"));

    // 显示设置
    m_displaySetting = new HscDisplaySetting(this);
    ui->tabWidget->addTab(m_displaySetting, tr("显示设置"));

    ui->tabWidget->setCurrentIndex(0);

}

void HscCollectSetting::refreshSwitchBtn(int index)
{
    switch (index) {
    case 0 :
        ui->btn_last->setEnabled(false);
        ui->btn_next->setEnabled(true);
        ui->btn_finish->setEnabled(false);
        break;
    case 1 :
        ui->btn_last->setEnabled(true);
        ui->btn_next->setEnabled(true);
        ui->btn_finish->setEnabled(false);
        break;
    case 2 :
        ui->btn_last->setEnabled(true);
        ui->btn_next->setEnabled(false);
        ui->btn_finish->setEnabled(true);
        break;
    }
}

void HscCollectSetting::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    refreshSwitchBtn(ui->tabWidget->currentIndex());
}

void HscCollectSetting::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    on_btn_finish_clicked();
}

void HscCollectSetting::updateCollectSetting()
{
    // 更新界面
    m_sensorSetting->loadModelData();
}

void HscCollectSetting::on_btn_last_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
    refreshSwitchBtn(ui->tabWidget->currentIndex());
}

void HscCollectSetting::on_btn_next_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
    refreshSwitchBtn(ui->tabWidget->currentIndex());
}

void HscCollectSetting::on_btn_finish_clicked()
{
    if (QMessageBox::information(this, tr("提示！"), tr("保存当前设置！"), QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes) {

        m_connectSetting->saveSetting();
        m_sensorSetting->saveSetting();
        m_displaySetting->saveSetting();

        emit applyCollectSetting();

        this->hide();
    }
}

void HscCollectSetting::on_tabWidget_currentChanged(int index)
{
    refreshSwitchBtn(index);
}
