#ifndef HSCSETVISIBLE_H
#define HSCSETVISIBLE_H

#include <QWidget>

namespace Ui {
class HscSetVisible;
}

class HscSetVisible : public QWidget
{
    Q_OBJECT

    friend class HscOnlineMonitor;
public:
    explicit HscSetVisible(QWidget *parent = nullptr);
    ~HscSetVisible();

private:
    void initView();
    void loadCollectSetting();
    void initSignalSlots();

signals:
    void updateChannelVisible();

private slots:
    void updateSensorStatus();

private:
    Ui::HscSetVisible *ui;
};

#endif // HSCSETVISIBLE_H
