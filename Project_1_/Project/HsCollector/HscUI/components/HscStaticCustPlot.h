#ifndef HSCSTATICCUSTPLOT_H
#define HSCSTATICCUSTPLOT_H

#ifndef _HSCPLOT_DLL_
#define _HSCPLOT_PORT_ __declspec(dllimport)
#else
#define _HSCPLOT_PORT_ __declspec(dllexport)
#endif

#include <QWidget>

#include "qcustomplot.h"

class _HSCPLOT_PORT_ HscStaticCustPlot : public QCustomPlot
{
public:
    explicit HscStaticCustPlot(QWidget * parent = nullptr);
    virtual ~HscStaticCustPlot();

public slots:
    void titleDoubleClick(QMouseEvent *event);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

    void rescaleAllAxis();

    void selectionChanged();
    void mousePress();
    void mouseWheel();

public:
    void setMouseControl(bool enable); // 设置是否可以鼠标放大缩小
};

#endif // HSCSTATICCUSTPLOT_H
