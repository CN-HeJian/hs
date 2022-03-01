#ifndef MACHINEPARAPLOT_H
#define MACHINEPARAPLOT_H
#include "../components/qcustomplot.h"
#include <QtCharts>
using namespace QtCharts;
#include <iostream>
#include <QVector>
#include <vector>
using namespace std;
#include <unordered_set>

class MachineParaPlot:public QCustomPlot
{
public:
    explicit MachineParaPlot(QWidget * parent = 0);
    ~MachineParaPlot();
public:
    void plotData(vector<string>dates,vector<float> datas,unordered_set<string> detected);
    void addCurrentShowData();
    void BoxPlot(vector<float> currentShowDatas,vector<string> dates,int hour,string label);
    void comformity();
    void deleteSelectedGraph();
    void deleteAll();
     void setxAxis2Range(string low,string hight);
     void setlegend(string label);
    void plotGraph2(double up,double down);
    void deleteGraph2();

private:
    //vector<vector<float>> currentShowDatas;
private:
    void updateCurrentShowData();

    double gaussrand();
   // void comformity();
    void getStaticVal(QVector<double> data,QVector<double> &minimumdatas,QVector<double>&lowerQuartiledatas,QVector<double>&mediandatas,QVector<double>&upperQuartiledatas,QVector<double>&maximumdatas);
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

#endif // MACHINEPARAPLOT_H


