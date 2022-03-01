#ifndef HSCPEAKPRESSURETENDENCY_H
#define HSCPEAKPRESSURETENDENCY_H

#include <QWidget>

#include "HscMinebeaDataMonitor.h"
#include "qcustomplot.h"

namespace Ui {
class HscPeakPressureTendency;
}

class HscPeakPressureTendency : public QWidget
{
    Q_OBJECT

    friend class HscOnlineMonitor;
public:
    explicit HscPeakPressureTendency(QWidget *parent = nullptr);
    ~HscPeakPressureTendency();

public:
    void startPlot();
    void setAisxValue(int y);
    void plotTendencyCurve(QList<HscDataAnalysisModel> *list);

private:
    void initView();
    void setupPlot();
    void loadCollectSetting();
    void initSignalSlots();
    void plotCurve(QVector<double> data);

public slots:
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

    void onMouseWheelInPlot (QWheelEvent *event);
    void onMouseMoveInPlot (QMouseEvent *event);
    void channel_selection (void);
    void legend_double_click (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);

private:
    Ui::HscPeakPressureTendency *ui;

    // 曲线颜色
    QVector<QColor> m_lineColors;

    // 绘图
    bool m_plotting = false;
    QTimer m_updateTimer;
    int m_dataPointNumber = 0;
    int m_channels = 0;

    // 统计
    int m_count = 0;
    QList<HscDataAnalysisModel> *m_totalData = nullptr;
};

#endif // HSCPEAKPRESSURETENDENCY_H
