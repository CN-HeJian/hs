#ifndef HSCSENSORSETTING_H
#define HSCSENSORSETTING_H

#include <QWidget>

#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class HscSensorSetting;
}

class HscSensorSetting : public QWidget
{
    Q_OBJECT

    friend class HscCollectSetting;

public:
    explicit HscSensorSetting(QWidget *parent = nullptr);
    ~HscSensorSetting();

public:
    void saveSetting();

private:
    void initView();
    void initSignalSlots();
    void loadModelData();

private slots:
    void setSelectedAisle();
    void setSectionType(const QString &);
    void setCollectUnit(const QString &);
    void setCurveColor();

private:
    Ui::HscSensorSetting *ui;

    QVector<QCheckBox *> m_checkBoxs;
    QVector<QComboBox *> m_cboxSections;
    QVector<QComboBox *> m_cboxCollects;
    QVector<QPushButton *> m_pbtnColor;
    QVector<QColor> m_curveColor;
    QVector<QComboBox *> m_cboxUnits;

};

#endif // HSCSENSORSETTING_H
