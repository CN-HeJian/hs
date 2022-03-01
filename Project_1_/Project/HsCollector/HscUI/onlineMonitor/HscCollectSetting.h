#ifndef HSCCOLLECTSETTING_H
#define HSCCOLLECTSETTING_H

#include <QWidget>

#include "HscConnectSetting.h"
#include "HscSensorSetting.h"
#include "HscDisplaySetting.h"

namespace Ui {
class HscCollectSetting;
}

class HscCollectSetting : public QWidget
{
    Q_OBJECT

public:
    explicit HscCollectSetting(QWidget *parent = nullptr);
    ~HscCollectSetting() override;

public:

private:
    void initView();
    void refreshSwitchBtn(int index);

protected:

    virtual void showEvent(QShowEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void applyCollectSetting();

public slots:
    void updateCollectSetting();

private slots:
    void on_btn_last_clicked();
    void on_btn_next_clicked();
    void on_btn_finish_clicked();
    void on_tabWidget_currentChanged(int index);

private:
    Ui::HscCollectSetting *ui;

    HscConnectSetting *m_connectSetting = nullptr;
    HscSensorSetting *m_sensorSetting = nullptr;
    HscDisplaySetting *m_displaySetting = nullptr;

};

#endif // HSCCOLLECTSETTING_H
