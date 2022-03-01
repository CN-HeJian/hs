#include "HscCurveCompareAction.h"
#include "ui_HscCurveCompareAction.h"

HscCurveCompareAction::HscCurveCompareAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscCurveCompareAction)
{
    ui->setupUi(this);
}

HscCurveCompareAction::~HscCurveCompareAction()
{
    delete ui;
}
