#ifndef HSCMONITORITEM_H
#define HSCMONITORITEM_H

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QDoubleSpinBox>

#include "HscMonitorSettingModel.h"

namespace Ui {
class HscMonitorItem;
}

class HscMonitorItem : public QWidget
{
    Q_OBJECT

public:
    explicit HscMonitorItem(QWidget *parent = nullptr);
    ~HscMonitorItem();

public:
    void initializer(int index);
    void setTopleft(int monitor, double upperPres, double lowerTime);
    void setBottomright(int monitor, double lowerPres, double upperTime);

private:
    void initView();
    void initSignalSlots();

signals:
    void updatePlotView();

private slots:
    void onGroupBoxClicked(bool val);
    void onComboBoxCurrentTextChanged(QString val);
    void onLowerPresChange(double val);
    void onUpperPresChange(double val);
    void onLowerTimeChange(double val);
    void onUpperTimeChange(double val);


private:
    Ui::HscMonitorItem *ui;

    QList<QGroupBox *> m_groupBoxs;
    QList<QComboBox *> m_comboBoxs;
    QList<QDoubleSpinBox *> m_lowerPresSpins;
    QList<QDoubleSpinBox *> m_upperPresSpins;
    QList<QDoubleSpinBox *> m_lowerTimeSpins;
    QList<QDoubleSpinBox *> m_upperTimeSpins;

    HscMonitorItemModel *m_model;
};

#endif // HSCMONITORITEM_H
