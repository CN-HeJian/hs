#include "HscDisplaySetting.h"
#include "ui_HscDisplaySetting.h"

#include <QDateTime>

#include "HscCollectSettingModel.h"

HscDisplaySetting::HscDisplaySetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscDisplaySetting)
{
    ui->setupUi(this);

    initView();
    loadModelData();
}

HscDisplaySetting::~HscDisplaySetting()
{
    delete ui;
}

void HscDisplaySetting::saveSetting()
{
    HscCollectSettingModel::displayModel.moldNo = ui->lineEdit_Mode->text();
    HscCollectSettingModel::displayModel.displayTime = ui->displayTimeSettingSB->text().toDouble();
    HscCollectSettingModel::displayModel.displayPressure = ui->collectPreSettingSB->text().toDouble();
    HscCollectSettingModel::displayModel.collectTime = ui->collectTimeSettingSB->text().toDouble();
    HscCollectSettingModel::displayModel.displayPosition = ui->collectPosSettingSB->text().toDouble();
}

void HscDisplaySetting::initView()
{
    ui->lineEdit_Mode->setInputMask(QString("0000-00-00-000"));
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate =currentDateTime.toString("yyyy-MM-dd");
    QString modeData = currentDate + QString("-");

    //    ui->lineEdit_Mode->setText(getCurrentBatchName(modeData));
}

void HscDisplaySetting::loadModelData()
{
     ui->lineEdit_Mode->setText(HscCollectSettingModel::displayModel.moldNo);
     ui->displayTimeSettingSB->setValue(HscCollectSettingModel::displayModel.displayTime);
     ui->collectPreSettingSB->setValue(HscCollectSettingModel::displayModel.displayPressure);
     ui->collectTimeSettingSB->setValue(HscCollectSettingModel::displayModel.collectTime);
     ui->collectPosSettingSB->setValue(HscCollectSettingModel::displayModel.displayPosition);
}
