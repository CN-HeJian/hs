#ifndef HSCSOFTWARESETTING_H
#define HSCSOFTWARESETTING_H

#include <QWidget>

namespace Ui {
class HscSoftwareSetting;
}

class HscSoftwareSetting : public QWidget
{
    Q_OBJECT

public:
    explicit HscSoftwareSetting(QWidget *parent = nullptr);
    ~HscSoftwareSetting();

public:

private:
    Ui::HscSoftwareSetting *ui;
};

#endif // HSCSOFTWARESETTING_H
