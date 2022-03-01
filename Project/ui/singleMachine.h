#ifndef SINGLEMACHINE_H
#define SINGLEMACHINE_H

#include <QWidget>

namespace Ui {
class SingleMachine;
}

class SingleMachine : public QWidget
{
    Q_OBJECT

public:
    explicit SingleMachine(QWidget *parent = nullptr);
    ~SingleMachine();

private:
    Ui::SingleMachine *ui;
};

#endif // SINGLEMACHINE_H
