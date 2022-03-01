#include "HscCavityAnalysisAction.h"
#include "ui_HscCavityAnalysisAction.h"

HscCavityAnalysisAction::HscCavityAnalysisAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscCavityAnalysisAction)
{
    ui->setupUi(this);
}

HscCavityAnalysisAction::~HscCavityAnalysisAction()
{
    delete ui;
}
