#include "HscSettingAction.h"
#include "ui_HscSettingAction.h"

HscSettingAction::HscSettingAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscSettingAction)
{
    ui->setupUi(this);
}

HscSettingAction::~HscSettingAction()
{
    delete ui;
}

void HscSettingAction::bindWidget(QWidget *widget)
{

}
