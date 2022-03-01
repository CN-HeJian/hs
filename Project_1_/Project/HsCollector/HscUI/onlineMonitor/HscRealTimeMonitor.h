#ifndef HSCREALTIMEMONITOR_H
#define HSCREALTIMEMONITOR_H

#include <QWidget>

#include "HscCollectDataModel.h"
#include "qcustomplot.h"

#include "HscMonitorSetting.h"
#include "HscMinebeaDataMonitor.h"

namespace Ui {
class HscRealTimeMonitor;
}

class HscRealTimeMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit HscRealTimeMonitor(QWidget *parent = nullptr);
    ~HscRealTimeMonitor();

    friend class HscOnlineMonitor;
public:
    void startPlot();
    void setAisxValue(int x, int y);
    void monitorSetting();
    void statisticData(QList<HscDataAnalysisModel> *list);

private:
    void initView();
    void initMonitorView();
    void setupPlot();
    void loadCollectSetting();
    void initSignalSlots();

signals:
    emit void updateTopleft(int channel, int monitor, double upperPres, double lowerTime);
    emit void updateBottomright(int channel, int monitor, double lowerPres, double upperTime);

public slots:

    void updateStatus(QString status);
    void plotCurve(HscCollectDataModel data);
    void replot();
    void plotItemRect();


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
    void onMousePressInPlot (QMouseEvent *event);
    void onMouseMoveInPlot (QMouseEvent *event);
    void onMouseReleaseInPlot (QMouseEvent *event);

    void channel_selection (void);
    void legend_double_click (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);

private:
    Ui::HscRealTimeMonitor *ui;

    // 曲线颜色
    QVector<QColor> m_lineColors;

    // 绘图
    bool m_plotting = false;
    QTimer m_updateTimer;
    int m_channels = 0;
    int m_dataPointNumber = 0;


    // 监控设定
    int m_totalCount = 0;
    int m_goodCount = 0;
    int m_badCount = 0;
    HscMonitorSetting *m_monitorSetting = nullptr;
    int m_selectedChannel = 0;
    int m_selectedMonitor = 0;

    QVector<QVector<QCPItemRect *>> m_monitorRects;
    QCPItemRect *m_currentRect = nullptr;

};

#endif // HSCREALTIMEMONITOR_H
