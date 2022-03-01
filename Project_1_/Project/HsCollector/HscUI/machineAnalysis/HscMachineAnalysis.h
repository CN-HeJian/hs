#ifndef HSCMACHINEANALYSIS_H
#define HSCMACHINEANALYSIS_H
#include <QPushButton>
#include <QWidget>

#include <service/CustomProtocolBaseTcp.h>
#include <RequestOperator.h>
#include <ReceiveOperator.h>
#include <DataProcess.h>
#include <unordered_map>
#include <string>
#include <utility>
#include <QByteArray>
using namespace std;
#include <unordered_set>
#include <unordered_map>

namespace Ui {
class HscMachineAnalysis;
}

class HscMachineAnalysis : public QWidget
{
    Q_OBJECT
public:
    explicit HscMachineAnalysis(QWidget *parent = nullptr);
    ~HscMachineAnalysis();
public:
    void initTimer();
    //请求数据操作
    void connectToServe();
    void refreshMachineList();
    void refreshPlotWidget();
    void queryHistoryData();
    void rePlot();
    //添加机台的操作
    void addMachine(string machineName,QJsonObject info);
    QPushButton* addListItem(string machineName);
    SingleMachine* addPlotWidget(string machineName,QJsonObject  info);
    void itemPlotWidgetInitSlot(QPushButton* listIntem,SingleMachine* plotWidget);
    void addMachineToVector(QPushButton* ,SingleMachine*);
    void addMachineToUnorderedSet(string machineName);
    //判断是否需要新加机台
    void judgeNeedCreateMachine();
    //添加游标
    void addCursor();
    //循环播放
    void cyclePlay();
    //开始定时器
    void startTimer();
    //结束定时器
    void endTimer();
    void setPushButtonStyle(QPushButton* tmp);
    //保存条件
    void saveCondition();
    //读取条件
    QJsonObject judgeExitInJson(string machineName);
    //局部放大
    void zoomLarge(bool flag);
    //导出数据
    void exportData();
    //控制坐标轴是否显示
    void  staticLabel();
private slots:
    void setCurrentPlotWidget(int index);
    void receiveResponce(QByteArray buffer);
    void setSelectPushButton(int index);
    void setLastShowIndex(int index);
    void onTimeOut();
    void Alarm(string );
    void detectMold(SingleMachine* cur);
private:
    Ui::HscMachineAnalysis *ui;
    RequestOperator *m_request;  //请求的操作
    ReceiveOperator *m_receive;  //接收的操作
    CustomProtocolBaseTcp * m_netServe;//网络服务
    //DataProcess m_dataProcess;//数据处理
    vector<pair<QPushButton*,SingleMachine*>> allMachine;
    vector<string> allMachineName;//所有的机器的名称
    DataProcess m_dataProcess;//数据处理
    unordered_set<string> currentMachine;//当前存在的机台，快速判断当前机台是否存在！！！
    //检测点
   // unordered_map<string,int> m_detect_mp;
    int lastShow=0;
    QTimer *m_cycPlayTimer;
    long currentCycCnt = 0;
};

#endif // HSCMACHINEANALYSIS_H
