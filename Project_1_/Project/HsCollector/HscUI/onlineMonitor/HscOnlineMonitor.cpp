#include "HscOnlineMonitor.h"
#include "ui_HscOnlineMonitor.h"

#include <QMdiSubWindow>


#define PEAKPRESFRAMES(i) ui->frame_##i
#define PEAKPRESCHANNELS(i) ui->label_##i
#define PEAKPRESVALUES(i) ui->label_##i
#define INTEGRALFRAMES(i) ui->frame_##i
#define INTEGRALCHANNELS(i) ui->label_##i
#define INTEGRALVALUES(i) ui->label_##i

HscOnlineMonitor::HscOnlineMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscOnlineMonitor)
{
    ui->setupUi(this);

    initView();
    loadCollectSetting();
    initSignalSlots();

//    initSimulateSignal(); // 模拟数据
}

HscOnlineMonitor::~HscOnlineMonitor()
{
    delete m_mqtt;
    delete ui;
}

void HscOnlineMonitor::collectSetting()
{
    m_collectSetting->show();
}

void HscOnlineMonitor::connectMqtt()
{
    if (!m_mqtt) {
        m_mqtt = new QMQTT;
    }

    if (m_mqttConnected) {
        qDebug() << "disconnect";
        switchCollect();
        m_mqttConnected = false;
        HscCollectSettingModel::status = 0;
        loadCollectSetting();
    } else {

        // 更新状态
        m_mqttConnected = true;

        // mqtt连接服务
        m_mqtt->setClientId("/realtime");
        m_mqtt->setCleanSession(true);
//        m_mqtt->setHost("192.168.2.2");
//        m_mqtt->setHost("127.0.0.1");
        m_mqtt->setHost(HscCollectSettingModel::connectModel.ip.toStdString());
//        m_mqtt->setPort(6343);
//        m_mqtt->setPort(1883);
        m_mqtt->setPort(uint16_t(HscCollectSettingModel::connectModel.port));
        m_mqtt->setKeepAlive(60);
        m_mqtt->connectToHost(m_mqttConnected);
        m_mqtt->subscribe(nullptr,"/Minebea",0);
        if(!m_mqttConnected) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("警告");
            msgBox.setWindowIcon(QIcon(":/new/prefix1/Resources/title/title.png"));
            msgBox.setText("处于离线状态，请检查!");
            msgBox.setButtonText(QMessageBox::Ok,QString("确定"));
            msgBox.exec();
            return;
        }
        switchCollect();
        HscCollectSettingModel::status = 1;
        loadCollectSetting();
    }

}

void HscOnlineMonitor::switchCollect()
{
    if (m_mqttConnected) {
        if (m_collected == false) {
            qDebug() << "start collect";
            // 开启数据采集
            if ((m_minebeaCollect == nullptr)&&(m_minebeaMonitor == nullptr)) {

                // 数据采集&分析
                m_minebeaCollectThread = new QThread;
                m_minebeaCollect = new HscMinebeaDataCollect;
                m_minebeaMonitorThread = new QThread;
                m_minebeaMonitor = new HscMinebeaDataMonitor;
                m_minebeaSaveThread = new QThread;
                m_minebeaSave = new HscMinebeaDataSave;
                m_minebeaCollect->moveToThread(m_minebeaCollectThread);
                m_minebeaMonitor->moveToThread(m_minebeaMonitorThread);
                m_minebeaSave->moveToThread(m_minebeaSaveThread);
                // 读取数据
//                connect(m_testThread, &HscTestData::testData, m_minebeaCollect, &HscMinebeaDataCollect::readMessage);
                connect(m_mqtt, &QMQTT::minReceived, m_minebeaCollect, &HscMinebeaDataCollect::readMessage, Qt::BlockingQueuedConnection);
                // 实时曲线
                connect(m_minebeaCollect, &HscMinebeaDataCollect::updateStatus, m_realTimeCurve, &HscRealTimeMonitor::updateStatus, Qt::QueuedConnection);
                connect(m_minebeaCollect, &HscMinebeaDataCollect::plotCurve, m_realTimeCurve, &HscRealTimeMonitor::plotCurve, Qt::QueuedConnection);
                // 数值监听
                connect(m_minebeaCollect, &HscMinebeaDataCollect::dataAnalysis, m_minebeaMonitor, &HscMinebeaDataMonitor::dataAnalysis, Qt::QueuedConnection);
                // 重写曲线
                connect(m_minebeaMonitor, &HscMinebeaDataMonitor::plotRewriteCurve, m_rewriteCurve, &HscRewriteCurve::plotRewriteCurve, Qt::QueuedConnection);
                // 数值分析
                connect(m_minebeaMonitor, &HscMinebeaDataMonitor::analysisData, this, &HscOnlineMonitor::analysisData, Qt::QueuedConnection);
                // 开启采集，初始化数据库
                connect(this, &HscOnlineMonitor::startCollect, m_minebeaSave, &HscMinebeaDataSave::onStartCollect, Qt::QueuedConnection);
                // 存储单个模次数据
                connect(m_rewriteCurve, &HscRewriteCurve::saveData, m_minebeaSave, &HscMinebeaDataSave::saveData, Qt::QueuedConnection);

            }
            m_minebeaCollectThread->start();
            m_minebeaMonitorThread->start();
            m_minebeaSaveThread->start();

            emit startCollect();

            // 更新状态
            m_collected = true;
        } else {
            qDebug() << "stop collect";

            m_minebeaCollectThread->quit();
            m_minebeaCollectThread->wait();
            m_minebeaMonitorThread->quit();
            m_minebeaMonitorThread->wait();
            m_minebeaSaveThread->quit();
            m_minebeaSaveThread->wait();

            // 更新状态
            m_collected = false;
        }

    } else {
        qDebug() << "disconnected";
    }

}

void HscOnlineMonitor::startPlot()
{
    m_realTimeCurve->startPlot();
    m_rewriteCurve->startPlot();
    m_integralValueTendency->startPlot();
    m_peakPressureTendency->startPlot();
}

void HscOnlineMonitor::setSubWindow(int index)
{
    m_subWindows[index]->show();
    switch (index) {
    case 0 :
        m_setVisible->show();
        break;
    case 1:
        m_realTimeCurve->show();
        break;
    case 2:
        m_rewriteCurve->show();
        break;
    case 3:
        m_integralValueTendency->show();
        break;
    case 4:
        m_peakPressureTendency->show();
        break;
    }
}

void HscOnlineMonitor::initView()
{

    // 采集设置
    m_collectSetting = new HscCollectSetting(this);
    m_collectSetting->setWindowModality(Qt::ApplicationModal);
    m_collectSetting->setAttribute(Qt::WA_ShowModal, true);
    m_collectSetting->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
    m_collectSetting->setWindowTitle(tr("监控设置"));

    // 设置通道显隐
    QMdiSubWindow *subSet = new QMdiSubWindow(ui->mdiArea);
    subSet->setWindowTitle("CH设置");
    subSet->setWindowIcon(QIcon(":/resource/icon/blank.png"));
    m_setVisible = new HscSetVisible(this);
    subSet->setWidget(m_setVisible);
    subSet->resize(200, 400);
    subSet->move(0, 0);
    m_subWindows.push_back(subSet);
    m_childWidgets.push_back(subSet);

    // 实时曲线
    QMdiSubWindow *subReal = new QMdiSubWindow(ui->mdiArea);
    subReal->setWindowTitle("实时曲线");
    subReal->setWindowIcon(QIcon(":/resource/icon/blank.png"));
    m_realTimeCurve = new HscRealTimeMonitor(this);
    subReal->setWidget(m_realTimeCurve);
    subReal->resize(800, 400);
    subReal->move(200, 0);
    m_subWindows.push_back(subReal);
    m_childWidgets.push_back(subReal);

    // 重写曲线
    QMdiSubWindow *subRewrite = new QMdiSubWindow(ui->mdiArea);
    subRewrite->setWindowTitle("重写曲线");
    subRewrite->setWindowIcon(QIcon(":/resource/icon/blank.png"));
    m_rewriteCurve = new HscRewriteCurve(this);
    subRewrite->setWidget(m_rewriteCurve);
    subRewrite->resize(800, 400);
    subRewrite->move(200, 400);
    m_subWindows.push_back(subRewrite);
    m_childWidgets.push_back(subRewrite);

    // 趋势（积分值）
    QMdiSubWindow *subIntegral = new QMdiSubWindow(ui->mdiArea);
    subIntegral->setWindowTitle("趋势（积分值）");
    subIntegral->setWindowIcon(QIcon(":/resource/icon/blank.png"));
    m_integralValueTendency = new HscIntegralValueTendency(this);
    subIntegral->setWidget(m_integralValueTendency);
    subIntegral->resize(600, 400);
    subIntegral->move(1000, 0);
    m_subWindows.push_back(subIntegral);
    m_childWidgets.push_back(subIntegral);

    // 趋势（峰值压力）
    QMdiSubWindow *subPeak = new QMdiSubWindow(ui->mdiArea);
    subPeak->setWindowTitle("趋势（峰值压力）");
    subPeak->setWindowIcon(QIcon(":/resource/icon/blank.png"));
    m_peakPressureTendency = new HscPeakPressureTendency(this);
    subPeak->setWidget(m_peakPressureTendency);
    subPeak->resize(600, 400);
    subPeak->move(1000, 400);
    m_subWindows.push_back(subPeak);
    m_childWidgets.push_back(subPeak);


    // 存储控件
    // --峰值压力--
    m_peakPresFrames << PEAKPRESFRAMES(3) << PEAKPRESFRAMES(4) << PEAKPRESFRAMES(5)
                     << PEAKPRESFRAMES(6) << PEAKPRESFRAMES(7) << PEAKPRESFRAMES(8)
                     << PEAKPRESFRAMES(9) << PEAKPRESFRAMES(10) << PEAKPRESFRAMES(11)
                     << PEAKPRESFRAMES(12);
    m_peakPresChannels << PEAKPRESCHANNELS(5) << PEAKPRESCHANNELS(7) << PEAKPRESCHANNELS(9)
                       << PEAKPRESCHANNELS(11) << PEAKPRESCHANNELS(13) << PEAKPRESCHANNELS(15)
                       << PEAKPRESCHANNELS(17) << PEAKPRESCHANNELS(19) << PEAKPRESCHANNELS(21)
                       << PEAKPRESCHANNELS(23);
    m_peakPresValues << PEAKPRESVALUES(6) << PEAKPRESVALUES(8) << PEAKPRESVALUES(10)
                     << PEAKPRESVALUES(12) << PEAKPRESVALUES(14) << PEAKPRESVALUES(16)
                     << PEAKPRESVALUES(18) << PEAKPRESVALUES(20) << PEAKPRESVALUES(22)
                     << PEAKPRESVALUES(24);
    // --积分值--
    m_integralFrames << INTEGRALFRAMES(22) << INTEGRALFRAMES(21) << INTEGRALFRAMES(18)
                     << INTEGRALFRAMES(19) << INTEGRALFRAMES(16) << INTEGRALFRAMES(17)
                     << INTEGRALFRAMES(14) << INTEGRALFRAMES(15) << INTEGRALFRAMES(20)
                     << INTEGRALFRAMES(13);
    m_integralChannels << INTEGRALCHANNELS(43) << INTEGRALCHANNELS(41) << INTEGRALCHANNELS(35)
                       << INTEGRALCHANNELS(37) << INTEGRALCHANNELS(31) << INTEGRALCHANNELS(33)
                       << INTEGRALCHANNELS(27) << INTEGRALCHANNELS(29) << INTEGRALCHANNELS(39)
                       << INTEGRALCHANNELS(25);
    m_integralValues << INTEGRALVALUES(44) << INTEGRALVALUES(42) << INTEGRALVALUES(36)
                       << INTEGRALVALUES(38) << INTEGRALVALUES(32) << INTEGRALVALUES(34)
                       << INTEGRALVALUES(28) << INTEGRALVALUES(30) << INTEGRALVALUES(40)
                       << INTEGRALVALUES(26);
}

void HscOnlineMonitor::loadCollectSetting()
{
    // 初始化最上侧展示栏
    // --当前状态--
    if (HscCollectSettingModel::status == 0) {
        ui->lab_status->setText(tr("离线"));
        ui->frame_status->setStyleSheet("background:red");
    } else if (HscCollectSettingModel::status == 1) {
        ui->lab_status->setText(tr("正常"));
        ui->frame_status->setStyleSheet("background:green");
    }

    // --展示--
    auto &sensorModel = HscCollectSettingModel::sensorsModel;
    for (auto i(0); i<sensorModel.count(); ++i) {
        // 监控显隐
        if (sensorModel[i].enable == 0) {
            m_peakPresFrames[i]->setVisible(false);
            m_integralFrames[i]->setVisible(false);
        } else {
            m_peakPresFrames[i]->setVisible(true);
            m_integralFrames[i]->setVisible(true);
        }
        // 通道颜色
        m_peakPresChannels[i]->setStyleSheet(QString("color:%1").arg(sensorModel[i].curveColor));
        m_integralChannels[i]->setStyleSheet(QString("color:%1").arg(sensorModel[i].curveColor));
    }

    // 曲线显示区间
    int pressure = int(HscCollectSettingModel::displayModel.displayPressure);
    int time = int(HscCollectSettingModel::displayModel.displayTime * 1000);
    m_realTimeCurve->setAisxValue(time, pressure);
    m_rewriteCurve->setAisxValue(time, pressure);
    // 重置
    m_yMaxPres = pressure;
    m_xMaxTime = time;
    m_yMaxInteg = 0;
}

void HscOnlineMonitor::initSignalSlots()
{
    connect(m_setVisible, &HscSetVisible::updateChannelVisible, this, &HscOnlineMonitor::updateChannelVisible);
    connect(m_setVisible, &HscSetVisible::updateChannelVisible, m_rewriteCurve, &HscRewriteCurve::updateChannelVisible);
    connect(m_setVisible, &HscSetVisible::updateChannelVisible, m_integralValueTendency, &HscIntegralValueTendency::updateChannelVisible);
    connect(m_setVisible, &HscSetVisible::updateChannelVisible, m_peakPressureTendency, &HscPeakPressureTendency::updateChannelVisible);

    // 应用采集设置
    connect(m_collectSetting, &HscCollectSetting::applyCollectSetting, this, &HscOnlineMonitor::applyCollectSetting);
    // 响应CH设置，更新界面
    connect(this, &HscOnlineMonitor::updateCollectSetting, m_collectSetting, &HscCollectSetting::updateCollectSetting);
}

void HscOnlineMonitor::initSimulateSignal()
{
    // 测试数据模拟
    m_testThread = new HscTestData;
    m_testThread->start();
}

void HscOnlineMonitor::applyCollectSetting()
{
    // 更新采集设置
    loadCollectSetting();

    // ch设置界面刷新
    m_setVisible->loadCollectSetting();
    // 实时曲线界面刷新
    m_realTimeCurve->loadCollectSetting();
    // 重写曲线界面刷新
    m_rewriteCurve->loadCollectSetting();
    // 积分值曲线界面刷新
    m_integralValueTendency->loadCollectSetting();
    // 峰值趋势曲线界面刷新
    m_peakPressureTendency->loadCollectSetting();

}

void HscOnlineMonitor::updateChannelVisible()
{
    // 当前界面刷新
    loadCollectSetting();

    emit updateCollectSetting();
}

void HscOnlineMonitor::analysisData(QList<HscDataAnalysisModel> *list)
{
    // 界面数据
    auto &data = list->last();
    double yAxisPres = 0; // 分析y轴峰值压力变化
    double yAxisInteg = 0; // 分析y轴积分值变化
    for (auto i(0); i < HscCollectSettingModel::sensorsModel.count(); ++i) {
        // 设置界面数值显示
        m_peakPresValues[i]->setText(QString::number(data.peakPressures[i]));
        m_integralValues[i]->setText(QString::number(data.integralValues[i]));
        // 调整实时曲线曲线&重写曲线&峰值压力趋势y轴
        if (data.peakPressures[i] > yAxisPres) {
            yAxisPres = data.peakPressures[i];
        }
        // 调整积分值y轴
        if (data.integralValues[i] > yAxisInteg) {
            yAxisInteg = data.integralValues[i];
        }
    }
    if (m_yMaxPres < yAxisPres) {
        m_yMaxPres = int(yAxisPres + 0.2 * yAxisPres);
        int time = int(HscCollectSettingModel::displayModel.displayTime * 1000);
        m_realTimeCurve->setAisxValue(time, m_yMaxPres);
        m_rewriteCurve->setAisxValue(time, m_yMaxPres);
        m_peakPressureTendency->setAisxValue(m_yMaxPres);
        HscCollectSettingModel::displayModel.displayPressure = m_yMaxPres;
    }

    if (m_yMaxInteg < yAxisInteg) {
        m_yMaxInteg = int(yAxisInteg + 0.2 * yAxisInteg);
        m_integralValueTendency->setAisxValue(m_yMaxInteg);
    }

    // 峰值压力
    m_peakPressureTendency->plotTendencyCurve(list);
    // 积分值
    m_integralValueTendency->plotTendencyCurve(list);
    // 数据分析
    m_realTimeCurve->statisticData(list);
}
