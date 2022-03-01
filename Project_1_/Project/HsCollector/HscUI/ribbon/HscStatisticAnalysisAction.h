#ifndef HSCSTATISTICANALYSISACTION_H
#define HSCSTATISTICANALYSISACTION_H

#include <QWidget>

namespace Ui {
class HscStatisticAnalysisAction;
}

class HscStatisticAnalysisAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscStatisticAnalysisAction(QWidget *parent = nullptr);
    ~HscStatisticAnalysisAction();

private:
    Ui::HscStatisticAnalysisAction *ui;
};

#endif // HSCSTATISTICANALYSISACTION_H
