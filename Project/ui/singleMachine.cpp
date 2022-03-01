#include "singleMachine.h"
#include "ui_singleMachine.h"

SingleMachine::SingleMachine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleMachine)
{
    ui->setupUi(this);
}

SingleMachine::~SingleMachine()
{
    delete ui;
}
