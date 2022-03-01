#include "HscStatisticAnalysisAction.h"
#include "ui_HscStatisticAnalysisAction.h"

HscStatisticAnalysisAction::HscStatisticAnalysisAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscStatisticAnalysisAction)
{
    ui->setupUi(this);
}

HscStatisticAnalysisAction::~HscStatisticAnalysisAction()
{
    delete ui;
}
