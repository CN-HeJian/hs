#ifndef SINGLEMACHINE_H
#define SINGLEMACHINE_H

#include <QWidget>
#include <string>
#include <vector>
#include "DataProcess.h"
#include <unordered_set>
#include "components/qcustomplot.h"
using namespace std;

namespace Ui {
class SingleMachine;
}

//当前机器的运转状态
typedef enum MACHINESTATE{
    running,
    stop
}state_t;

//选择数据的范围
typedef enum SELECERANGE{
    latelyMold,
    regionMold
}selectRange_t;

//当前显示的数据类型
typedef enum DATATYPE{
    injectPhasePres_Avg,
    measuring_time,
    measuring_trq
}dataType_t;

//当前显示的图形示例
typedef enum DISPLAYTYPE{
    LineChart,
    BoxChart
}display_t;


class SingleMachine : public QWidget
{
    Q_OBJECT
public:
    explicit SingleMachine(string machineName,QWidget *parent = nullptr);
    explicit SingleMachine(string machineName,int dataType,int displayType,int boxChartHourNums,int lineChartLine_avgNum,QString modifyProcessParameterTime,int selectLatelyMoldCnt,int selectRange,QWidget *parent = nullptr);
    ~SingleMachine();
    unordered_set<string> mp;
private:
    void init();
private:
    Ui::SingleMachine *ui;
private:
    string m_machineName;
    /*************************************CURRENT MACHINE STATE************************************/
    state_t m_machineState;
    /****************************************DATA SELECT  SET**************************************/
    selectRange_t m_selectRangeType = regionMold;
    dataType_t m_dateType = injectPhasePres_Avg;
    string m_modifyProcessParameterTime;
    string m_queryStartTime;
    string m_queryEndTime;
    int m_selectLatelyMoldCnt = 50;
    /****************************************DATA  SHOW   SET***************************************/
    display_t m_displayType = LineChart;
    int m_lineChart_avgNum=10;
    int m_boxChart_HourNums=1;
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;
    QCPItemText *textLabel;
    /********************************************PlotData*******************************************/
    dataType_t plotDataType  = injectPhasePres_Avg; //当前图中显示的数据类型---同步修改
    //vector<pair<string,float>> plotData; //当前图中显示的数据---同步修改
    vector<string> m_dates;
    vector<float> m_vals;
     vector<float> m_slideWindow;
     //unordered_set<string> mp;
    /********************************************PlotData*******************************************/
    DataProcess m_dataProcess;//数据处理
    /********************************************PlotData*******************************************/
    QString detectMoldDate;
    bool m_enlarge = false;
public:
    /***********************************************GET*******************************************/
    string getMachineName();
    state_t getMachineState();
    selectRange_t getCurMachineSelectRangeType();
    dataType_t getDataType();
    string getModifyProcessParameterTime();
    int getSelectLatelyMoldCnt();
    display_t getDisplayType();
    int getLineChartAvgNum();
    int getBoxChart_HourNums();
    string getStartTime();
    string getEndTime();
    QString getDetectMoldDate();
    /***********************************************SET*******************************************/
    void setPlotDataType(dataType_t type);
    void setPlotdData(vector<string> dates,vector<float> vals);
    void setDetectedData(vector<string> detected);
    void initInterface();

    //设置所有界面
    void setSelectRangeType();
    void setDataType();
    void setModifyProcessParameterTime();
    void setSelectLatelyMoldCnt();
    void setDisplay_t();
    void setLineChart_avgNum();
    void setBoxChart_HourNums();
    void zoomLarge(bool flag);


    /***********************************************PLOT*******************************************/
    void controlPlot();
    void addCursor();

    /***********************************************SAVE*******************************************/
    void saveToJson(QJsonObject &json)const;

    /***********************************************EXPORT*******************************************/
    void exportData();
    QString m_lastSavePath = "";

    /***********************************************Monitor*******************************************/
    bool isStart=false;
    double UpLimit;
    double DownLimit;

    QCPItemTracer* tracer1;
    QCPItemTracer* tracer2;
    bool    bTracer1;
    bool    bTracer2;
    void staticLabel();
    bool m_isShow=false;


private slots:

    void mousePress(QMouseEvent* e);
    void mouseDoubleClick(QMouseEvent* e);
    void mouseMove(QMouseEvent *e);


    void on_spinBox_valueChanged(int arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_4_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_toolButton_3_clicked();

    void on_spinBox_5_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_checkBox_1_clicked(bool checked);
    void selectionChange();
    void mouseMove1(QMouseEvent*);

    void on_toolButton_5_clicked();

    void on_dateTimeEdit_3_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_4_dateTimeChanged(const QDateTime &dateTime);

    void on_doubleSpinBox_12_valueChanged(double arg1);

    void on_doubleSpinBox_13_valueChanged(double arg1);

    void on_toolButton_4_clicked();

private:
   bool is_CreateCursor=false;
   vector<string> label ={"注射压力均值/(kgf/cm2)","计量扭矩","计量时间/(s)"};

signals:
    void Alarm(string );
    void detectMold(SingleMachine* cur);
};

#endif // SINGLEMACHINE_H
