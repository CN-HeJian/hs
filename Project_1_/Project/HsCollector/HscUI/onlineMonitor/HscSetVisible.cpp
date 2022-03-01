#include "HscSetVisible.h"
#include "ui_HscSetVisible.h"

#include "HscCollectSettingModel.h"

HscSetVisible::HscSetVisible(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscSetVisible)
{
    ui->setupUi(this);

    initView();
    loadCollectSetting();
    initSignalSlots();
}

HscSetVisible::~HscSetVisible()
{
    delete ui;
}

void HscSetVisible::initView()
{
    if (ui->gridLayout) {
        for (auto i(1); i<ui->gridLayout->rowCount(); ++i) {
            auto cbox = static_cast<QCheckBox *>(ui->gridLayout->itemAtPosition(i, 2)->widget());
            if (cbox) {
                cbox->setEnabled(false);
            }
        }
    }
}

void HscSetVisible::loadCollectSetting()
{
    if (ui->gridLayout) {
        for (auto i(1); i<ui->gridLayout->rowCount(); ++i) {
            auto cbox = static_cast<QCheckBox *>(ui->gridLayout->itemAtPosition(i, 1)->widget());
            if (cbox) {
                cbox->setChecked(HscCollectSettingModel::sensorsModel[i-1].enable);
            }
        }
    }
}

void HscSetVisible::initSignalSlots()
{
    if (ui->gridLayout) {
        for (auto i(1); i<ui->gridLayout->rowCount(); ++i) {
            auto cbox = static_cast<QCheckBox *>(ui->gridLayout->itemAtPosition(i, 1)->widget());
            if (cbox) {
                connect(cbox, &QCheckBox::clicked, this, &HscSetVisible::updateSensorStatus);
            }
        }
    }
}

void HscSetVisible::updateSensorStatus()
{
    if (ui->gridLayout) {
        for (auto i(1); i<ui->gridLayout->rowCount(); ++i) {
            auto cbox = static_cast<QCheckBox *>(ui->gridLayout->itemAtPosition(i, 1)->widget());
            if (cbox->isChecked()) {
                HscCollectSettingModel::sensorsModel[i-1].enable = 1;
            } else {
                HscCollectSettingModel::sensorsModel[i-1].enable = 0;
            }
        }
        emit updateChannelVisible();
    }
}
