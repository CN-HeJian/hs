#ifndef HSCSETTINGACTION_H
#define HSCSETTINGACTION_H

#include <QWidget>

namespace Ui {
class HscSettingAction;
}

class HscSettingAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscSettingAction(QWidget *parent = nullptr);
    ~HscSettingAction();

public:
    void bindWidget(QWidget *widget);

private:
    Ui::HscSettingAction *ui;
};

#endif // HSCSETTINGACTION_H
