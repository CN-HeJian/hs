#ifndef HSCREWRITECURVE_H
#define HSCREWRITECURVE_H

#include <QWidget>

#include "qcustomplot.h"
#include "HscCollectSettingModel.h"
#include "HscCollectDataModel.h"

namespace Ui {
class HscRewriteCurve;
}

class HscRewriteCurve : public QWidget
{
    Q_OBJECT

public:
    explicit HscRewriteCurve(QWidget *parent = nullptr);
    ~HscRewriteCurve();

    friend class HscOnlineMonitor;

public:
    void startPlot();
    void setAisxValue(int x, int y);

private:
    void initView();
    void setupPlot();
    void loadCollectSetting();
    void initSignalSlots();

    void plotCurve(HscCollectDataModel data);

signals:
    void saveData(QList<HscCollectDataModel> *list);

public slots:

    void plotRewriteCurve(QList<QList<HscCollectDataModel>> *list);
    void replot();
    void updateChannelVisible();

private slots:
    void on_spinPoints_valueChanged (int arg1);
    void on_spinYStep_valueChanged(int arg1);
    void on_spinAxesMin_valueChanged(int arg1);
    void on_spinAxesMax_valueChanged(int arg1);
    void on_pushButton_AutoScale_clicked();
    void on_listWidget_Channels_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_ResetVisible_clicked();
    void on_savePNGButton_clicked();

    void onMouseWheelInPlot(QWheelEvent *event);
    void onMouseMoveInPlot(QMouseEvent *event);
    void channel_selection(void);
    void legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::HscRewriteCurve *ui;

    // 曲线颜色
    QVector<QColor> m_lineColors;

    // 绘图
    bool m_plotting = false;
    QTimer m_updateTimer;
    int m_dataPointNumber = 0;
    int m_channels = 0;

    // 统计
    int m_rewriteCount = 0;
    int m_displayCount = 5;
    QList<QList<HscCollectDataModel>> *m_totalData = nullptr;

};

#endif // HSCREWRITECURVE_H
