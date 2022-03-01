#ifndef HSCCURVECOMPAREACTION_H
#define HSCCURVECOMPAREACTION_H

#include <QWidget>

namespace Ui {
class HscCurveCompareAction;
}

class HscCurveCompareAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscCurveCompareAction(QWidget *parent = nullptr);
    ~HscCurveCompareAction();

private:
    Ui::HscCurveCompareAction *ui;
};

#endif // HSCCURVECOMPAREACTION_H
