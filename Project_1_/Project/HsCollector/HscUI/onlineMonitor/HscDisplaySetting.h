#ifndef HSCDISPLAYSETTING_H
#define HSCDISPLAYSETTING_H

#include <QWidget>

namespace Ui {
class HscDisplaySetting;
}

class HscDisplaySetting : public QWidget
{
    Q_OBJECT

public:
    explicit HscDisplaySetting(QWidget *parent = nullptr);
    ~HscDisplaySetting();

public:
    void saveSetting();

private:
    void initView();
    void loadModelData();

private:
    Ui::HscDisplaySetting *ui;
};

#endif // HSCDISPLAYSETTING_H
