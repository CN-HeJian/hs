#ifndef HSCCAVITYANALYSISACTION_H
#define HSCCAVITYANALYSISACTION_H

#include <QWidget>

namespace Ui {
class HscCavityAnalysisAction;
}

class HscCavityAnalysisAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscCavityAnalysisAction(QWidget *parent = nullptr);
    ~HscCavityAnalysisAction();

private:
    Ui::HscCavityAnalysisAction *ui;
};

#endif // HSCCAVITYANALYSISACTION_H
