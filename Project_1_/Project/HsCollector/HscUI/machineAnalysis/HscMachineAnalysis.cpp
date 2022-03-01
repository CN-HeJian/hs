#include "HscMachineAnalysis.h"
#include "ui_HscMachineAnalysis.h"
#include "templateSingle.hpp"
#include "SingleMachine.h"
#include <QDebug>
#include <iostream>
using namespace  std;


HscMachineAnalysis::HscMachineAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscMachineAnalysis)
{
    ui->setupUi(this);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    m_netServe = Singleton<CustomProtocolBaseTcp>::Instance();
    m_request = new RequestOperator();
    m_receive = new ReceiveOperator();
    m_cycPlayTimer = new QTimer();
    initTimer();
    connect(m_netServe, SIGNAL(receiveResponceFromServer(QByteArray )), this, SLOT(receiveResponce(QByteArray )));
}

HscMachineAnalysis::~HscMachineAnalysis()
{
    delete ui;
}

//---------------------------------------------------------------------------------------------------------------------//
//  定时器配置、初始化定时器
//---------------------------------------------------------------------------------------------------------------------//
void HscMachineAnalysis::initTimer(){
    m_cycPlayTimer->setInterval(20000);
    connect(m_cycPlayTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
}

void HscMachineAnalysis::startTimer(){
    m_cycPlayTimer->start();
}

void HscMachineAnalysis::endTimer(){
    m_cycPlayTimer->stop();
}


//---------------------------------------------------------------------------------------------------------------------//
//  添加机台的操作
//---------------------------------------------------------------------------------------------------------------------//

/*
 *  添加一台机器
*/
void HscMachineAnalysis::addMachine(string machineName,QJsonObject  info){
    QPushButton* listItem =  addListItem(machineName);
    SingleMachine* plotWidget =  addPlotWidget(machineName,info);
     connect(plotWidget,SIGNAL(Alarm(string )),this,SLOT(Alarm(string )));
     connect(plotWidget,SIGNAL(detectMold(SingleMachine* )),this,SLOT(detectMold(SingleMachine* )));
    addMachineToVector(listItem,plotWidget);
    addMachineToUnorderedSet(machineName);
    itemPlotWidgetInitSlot(listItem,plotWidget);
}

/*
 *  添加机台名表项
*/
QPushButton* HscMachineAnalysis::addListItem(string machineName){
    QPushButton* pushButton;
    pushButton = new QPushButton(QString::fromStdString(machineName), ui->scrollAreaWidgetContents_5);
    setPushButtonStyle(pushButton);
    ui->verticalLayout_2->addWidget(pushButton);
    pushButton->setObjectName("machineName");

  // pushButton->setFont(QFont("Arial", 20));

    return pushButton;
}

/*
 *  手动调整pushButton的样式
*/

void HscMachineAnalysis::setPushButtonStyle(QPushButton* tmp){
    QPalette   pal;
    tmp->setStyleSheet("QPushButton{border: 1px solid rgb(25, 148, 222);background-color:rgb(243,243,243); font-family:'Segoe UI Semilight';font-size:20px;};");
    pal.setColor(QPalette::ButtonText, QColor(0,0,0));
    tmp->setPalette(pal);
}

/*
 *  初始化画图窗口
*/
SingleMachine* HscMachineAnalysis::addPlotWidget(string machineName,QJsonObject info){
    SingleMachine *singleMachine;
    qDebug()<<"INFO.SIZE()"<<info.size();
    if(info.size()==0){
        singleMachine = new SingleMachine(machineName,this);
    }else{
        int m_boxChart_HourNums = info["boxChart_HourNums"].toInt();
        dataType_t m_dateType = dataType_t(info["dataType_t"].toInt());
        display_t m_displayType = display_t(info["display_t"].toInt());
        int m_lineChart_avgNum = info["lineChart_avgNum"].toInt();
        QString m_modifyProcessParameterTime = info["modifyProcessParameterTime"].toString();
        int m_selectLatelyMoldCnt = info["selectLatelyMoldCnt"].toInt();
        selectRange_t m_selectRangeType = selectRange_t(info["selectRange_t"].toInt());
        singleMachine = new SingleMachine(machineName,m_dateType,m_displayType,m_boxChart_HourNums,m_lineChart_avgNum,m_modifyProcessParameterTime,m_selectLatelyMoldCnt,m_selectRangeType);
    }
    ui->stackedWidget->addWidget(singleMachine);
    return singleMachine;
}





/*
 *  将机台存入向量
*/
void HscMachineAnalysis::addMachineToVector(QPushButton *listItem, SingleMachine *plotWidget){
    allMachine.push_back(make_pair(listItem,plotWidget));
}

/*
 *  将机台存入哈希表
*/
void HscMachineAnalysis::addMachineToUnorderedSet(string machineName){
    currentMachine.insert(machineName);
}

/*
 *  初始化槽函数、点击左边的listItem跳转到对应的页面
 *  注意：
 *  第二个槽函数与第三个槽函数的顺序不能更换
*/
void HscMachineAnalysis::itemPlotWidgetInitSlot(QPushButton* listItem,SingleMachine* Widget){
    int index = ui->stackedWidget->indexOf(Widget);
    connect(listItem,&QPushButton::clicked,this,[=](){setCurrentPlotWidget(index);});
    connect(listItem,&QPushButton::clicked,this,[=](){setSelectPushButton(index);});
    connect(listItem,&QPushButton::clicked,this,[=](){setLastShowIndex(index);});
}

/*
 *  槽函数，页面跳转
*/
void HscMachineAnalysis::setCurrentPlotWidget(int index ){
    ui->stackedWidget->setCurrentIndex(index);
}

/*
 * 槽函数，记录上次选中的页面，方便设置PushButton的颜色
*/
void HscMachineAnalysis::setLastShowIndex(int index){
    lastShow = index;
}

/*
 * 修改PushButton的颜色
*/
void HscMachineAnalysis::setSelectPushButton(int index){
    QPalette   pal;
    QPushButton* lastSelect  =  allMachine[lastShow].first;
    lastSelect->setStyleSheet("QPushButton{border: 1px solid rgb(25, 148, 222);background-color:rgb(243,243,243); font-family:'Segoe UI Semilight';font-size:20px;}");
    pal.setColor(QPalette::ButtonText, QColor(0,0,0));
    lastSelect->setPalette(pal);
    QPushButton* selectedButton  =  allMachine[index].first;
    selectedButton->setStyleSheet("QPushButton{border: 1px solid rgb(25, 148, 222);background-color:rgb(228,236,250); font-family:'Segoe UI Semilight';font-size:20px;}");
    pal.setColor(QPalette::ButtonText, QColor(209, 68, 36));
    selectedButton->setPalette(pal);
}

/*
 * 新增的机台，判断是否需要新增机台
*/
void HscMachineAnalysis::judgeNeedCreateMachine(){
    for(int i=0;i<allMachineName.size();i++){
        if(allMachineName[i]!=""){
            if(currentMachine.find(allMachineName[i])==currentMachine.end()){
                //判断是否存在于json文件中
                bool isExitInJson = false;
                QJsonObject info =  judgeExitInJson(allMachineName[i]);
                addMachine(allMachineName[i],info);
            }
        }
    }
}

/*
 * 重新绘制
*/
void HscMachineAnalysis::rePlot(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }

    currentShow->controlPlot();
}

/*
 * 添加游标
*/
void HscMachineAnalysis::addCursor(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }
    currentShow->addCursor();
}

/*
 * 循环播放，也就是模拟人工点击按钮
*/
void HscMachineAnalysis::cyclePlay(){
    connectToServe();//测试是长连接还是短连接
    startTimer();
    currentCycCnt = 0;
}

/*
 * 定时器时间结束
*/
void HscMachineAnalysis::onTimeOut(){
    int allSize = allMachine.size();
    if(allSize==0){
        return ;
    }
    int current = currentCycCnt%allSize;
    setCurrentPlotWidget(current);
    setSelectPushButton(current);
    setLastShowIndex(current);  //更改上一次显示的窗口
    refreshPlotWidget();
    currentCycCnt++;
}

/*
 * 保存条件
*/
void HscMachineAnalysis::saveCondition(){
    QFile saveFile("save.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
     }

     QJsonObject MachineObject;
     QJsonArray Machines;
     for(int i=0;i<allMachine.size();i++){
         QJsonObject everymachine;
         SingleMachine* tmp = allMachine[i].second;
         tmp->saveToJson(everymachine);
         Machines.append(everymachine);
     }
     MachineObject["allMachines"] = Machines;

     QJsonDocument saveDoc(MachineObject);
     saveFile.write(saveDoc.toJson());
}

/*
 * 开启局部放大功能
*/
void HscMachineAnalysis::zoomLarge(bool flag){

    for(int i=0;i<allMachine.size();i++){

        SingleMachine* tmp = allMachine[i].second;
        tmp->zoomLarge(flag);
    }
}



/*
 * 读取条件
*/
QJsonObject HscMachineAnalysis::judgeExitInJson(string machineName){
    QFile loadFile(QStringLiteral("save.json"));
    if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
     }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    QJsonArray levelArray = json["allMachines"].toArray();
    for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
        QJsonObject levelObject = levelArray[levelIndex].toObject();
        if(levelObject["machineName"] == QString::fromStdString(machineName)){
            return levelObject;
        }
    }
    return {};
}

/*
 * 导出数据
*/
void HscMachineAnalysis::exportData(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }
    currentShow->exportData();
}

/*
 * 取消报警设置条件
*/
void HscMachineAnalysis::Alarm(string machineName){
    for(int i=0;i<allMachine.size();i++){
        pair<QPushButton*,SingleMachine*>  tmp = allMachine[i];
        QString temp_text = tmp.first->text();
        if(temp_text == QString::fromStdString(machineName)){
            //tmp.first->setStyleSheet("color:red");
            tmp.first->setStyleSheet("QPushButton{border: 1px solid rgb(25, 148, 222);background-color:rgb(243,243,243); font-family:'Segoe UI Semilight';font-size:20px;}");
        }
    }
}


void HscMachineAnalysis::staticLabel(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }
    currentShow->staticLabel();
}


//---------------------------------------------------------------------------------------------------------------------//
//  向服务器发起请求的操作
//---------------------------------------------------------------------------------------------------------------------//

/*
 *  远程连接获取状态
*/
void HscMachineAnalysis::connectToServe(){
    m_request->requestToServe(REQ_SERVERSTATE,nullptr);
}

/*
 *  刷新当前机台列表
*/
void HscMachineAnalysis::refreshMachineList(){
    m_request->requestToServe(REQ_MACHINELIST,nullptr);
}

/*
 *  刷新单个机台的数据
*/
void HscMachineAnalysis::refreshPlotWidget(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }
    if(currentShow->getCurMachineSelectRangeType() == latelyMold){
        m_request->requestToServe(REQ_LEASTMOLDFEATURE,currentShow);
    }else{
        m_request->requestToServe(REQ_LEASTREGION,currentShow);
    }
}

/*
 * 检测标记点的请求函数
*/
void HscMachineAnalysis::detectMold(SingleMachine* currentShow){
    qDebug()<<"dectMold"<<endl;
    qDebug()<<"cur"<<QString::fromStdString(  currentShow->getMachineName());
    m_request->requestToServe(REQ_DECTMOLD,currentShow);
}



/*
 *  请求历史数据
*/
void HscMachineAnalysis::queryHistoryData(){
    SingleMachine *currentShow = dynamic_cast<SingleMachine*>(ui->stackedWidget->currentWidget());
    if(currentShow==nullptr){
        return ;
    }
    m_request->requestToServe(REQ_QUERYHISTORY,currentShow);
}

//---------------------------------------------------------------------------------------------------------------------//
//  接收来自服务端的响应
//---------------------------------------------------------------------------------------------------------------------//
void HscMachineAnalysis::receiveResponce(QByteArray buf){
    qDebug()<<buf<<endl;
    //首先确定类型
    int ReqTypeNum = (buf[0]-'0')*10+(buf[1]-'0');
    //当获取类型为最近区间、最近模次时则需要寻找对应的机台
    SingleMachine* selectMachine;
    if(ReqTypeNum == REQ_LEASTREGION || ReqTypeNum ==  REQ_LEASTMOLDFEATURE || ReqTypeNum ==  REQ_QUERYHISTORY || ReqTypeNum ==  REQ_QUERYHISTORY || ReqTypeNum == REQ_DECTMOLD ){
        //确定机台的名字
        QString buff = buf;
        int nameLength = (buf.at(4)-'0')*10+(buf.at(5)-'0');              //机台的长度
        QString machineName = QString::fromStdString(buff.mid(6,nameLength).toStdString());        //机台的名字
        //开始寻找对应的机台,遍历一遍
        qDebug()<<"machineName:"<<machineName;
        for(size_t i=0;i<allMachine.size();i++){
            pair<QPushButton*,SingleMachine*>  tmp = allMachine[i];
            QString temp_text = tmp.first->text();
            if(temp_text == machineName){
                qDebug()<<"find one machine";
                selectMachine = tmp.second;
            }
        }
    }
    //找到了对应的机台,已知了type,则去执行对应的解码函数
    if(ReqTypeNum == REQ_LEASTREGION){
        vector<pair<string,float>>* res = static_cast<vector<pair<string,float>>*>((m_receive->function_table[ReqTypeNum](buf)));

        int DataType = (buf[2]-'0')*10+(buf[3]-'0');
        if(selectMachine==nullptr){
            qDebug()<<"DO NOT FIND ONE MACHINE";
        }else{
            vector<string> r_date;
            vector<float> originData;
            for(auto c:*res){
                string date = c.first;
                float val = c.second;
                r_date.push_back(date);
                if(selectMachine->getDataType()==injectPhasePres_Avg){
                    val = 10*val;
                }
                originData.push_back(val);
            }
            cout<<"originData: "<<originData.size()<<endl;

            vector<float> outLineDect = m_dataProcess.OutLineDect(originData);
            selectMachine->setPlotdData(r_date,outLineDect);
            selectMachine->setPlotDataType(dataType_t(DataType));
        }
        selectMachine->controlPlot();
    }
    else if(ReqTypeNum ==  REQ_LEASTMOLDFEATURE){
        vector<pair<string,float>>* res = static_cast<vector<pair<string,float>>*>((m_receive->function_table[ReqTypeNum](buf)));
        //开始赋值
        int DataType = (buf[2]-'0')*10+(buf[3]-'0');

        if(selectMachine==nullptr){
            qDebug()<<"DO NOT FIND ONE MACHINE";
        }
        else{
            vector<string> r_date;
            vector<float> originData;
            for(auto c:*res){
                string date = c.first;
                float val = c.second;
                r_date.push_back(date);
                if(selectMachine->getDataType()==injectPhasePres_Avg){
                    val = 10*val;
                }
                originData.push_back(val);
            }
            cout<<"originData: "<<originData.size()<<endl;

            vector<float> outLineDect = m_dataProcess.OutLineDect(originData);
            selectMachine->setPlotdData(r_date,outLineDect);
            selectMachine->setPlotDataType(dataType_t(DataType));
        }
        selectMachine->controlPlot();
    }else if(ReqTypeNum ==  REQ_QUERYHISTORY){
        vector<pair<string,float>>* res = static_cast<vector<pair<string,float>>*>((m_receive->function_table[ReqTypeNum](buf)));
        //开始赋值

        int DataType = (buf[2]-'0')*10+(buf[3]-'0');
        if(selectMachine==nullptr){
            qDebug()<<"DO NOT FIND ONE MACHINE";
        }
        else{
            vector<string> r_date;
            vector<float> originData;
            for(auto c:*res){
                string date = c.first;
                float val = c.second;
                r_date.push_back(date);
                if(selectMachine->getDataType()==injectPhasePres_Avg){
                    val = 10*val;
                }
                originData.push_back(val);
            }
            vector<float> outLineDect = m_dataProcess.OutLineDect(originData);
            selectMachine->setPlotdData(r_date,outLineDect);
            selectMachine->setPlotDataType(dataType_t(DataType));
        }
        selectMachine->controlPlot();
    }else if(ReqTypeNum == REQ_MACHINELIST){
        vector<string> *res = static_cast<vector<string>*>((m_receive->function_table[ReqTypeNum](buf)));
        //开始赋值
        allMachineName = *res;
        //对数据进行操作
        judgeNeedCreateMachine();
    }else if(ReqTypeNum == REQ_DECTMOLD){
        cout<<"REQ_DECTMOLD"<<endl;
        vector<pair<string,float>> *res = static_cast<vector<pair<string,float>>*>((m_receive->function_table[ReqTypeNum](buf)));



        if(selectMachine==nullptr){
            qDebug()<<"DO NOT FIND ONE MACHINE";
        }else{
            vector<string> m_detect_set;

            vector<string> r_date;
            vector<float> originData;
            for(auto c:*res){
                string date = c.first;
                float val = c.second;
                r_date.push_back(date);
                originData.push_back(val);
                m_detect_set.push_back(date);
            }

            selectMachine->setDetectedData(m_detect_set);
            selectMachine->controlPlot();
        }

        //m_detect_mp.
        //selectMachine->setDetectedData(m_detect_set);
        //m_detect_set.clear();

        //selectMachine->controlPlot();

    }

}

