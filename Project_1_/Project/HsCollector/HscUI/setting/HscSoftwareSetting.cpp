#include "HscSoftwareSetting.h"
#include "ui_HscSoftwareSetting.h"

HscSoftwareSetting::HscSoftwareSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscSoftwareSetting)
{
    ui->setupUi(this);
}

HscSoftwareSetting::~HscSoftwareSetting()
{
    delete ui;
}
