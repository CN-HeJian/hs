#include "HscConnectSetting.h"
#include "ui_HscConnectSetting.h"

#include "HscCollectSettingModel.h"

#include <QDebug>

HscConnectSetting::HscConnectSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscConnectSetting)
{
    ui->setupUi(this);

    initView();
    loadModelData();
}

HscConnectSetting::~HscConnectSetting()
{
    delete ui;
}

void HscConnectSetting::initView()
{
    // ip
    QString ipFormat = "^([1-9][0-9]?|[1-2][0-4][0-9]|[1-2][0-5][0-5])"
                       "\\.([0-9]|[1-9][0-9]|[1-2][0-4][0-9]|[1-2][0-5][0-5])"
                       "\\.([0-9]|[1-9][0-9]|[1-2][0-4][0-9]|[1-2][0-5][0-5])"
                       "\\.([0-9]|[1-9][0-9]|[1-2][0-4][0-9]|[1-2][0-5][0-5])$";
    QRegExp ipRegExp(ipFormat);

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegExp, this);
    ui->ipLE->setValidator(ipValidator);
    ui->ipLE->setText("192.168.3.1"); // demo
//    ui->ipLE->setInputMask("127.0.0.1");

    // port
    ui->portLE->setValue(6343);

    // 接口类型
    ui->cbox_interfaceType->setCurrentText("Minebea");

}

void HscConnectSetting::loadModelData()
{
    // 初始化数据
    ui->ipLE->setText(HscCollectSettingModel::connectModel.ip);
    qDebug() << HscCollectSettingModel::connectModel.ip;
    ui->portLE->setValue(HscCollectSettingModel::connectModel.port);
    ui->cbox_interfaceType->setCurrentText(HscCollectSettingModel::connectModel.sensorInterface);
}

void HscConnectSetting::on_testConnectPB_clicked()
{
    if (!m_mqtt) {
        m_mqtt = new QMQTT;
    }
    m_mqtt->setClientId("/realtime");
    m_mqtt->setCleanSession(true);
    m_mqtt->setHost(ui->ipLE->text().toStdString());
    m_mqtt->setPort(uint16_t(ui->portLE->value()));
    m_mqtt->setKeepAlive(60);
    m_connected = true;
    m_mqtt->connectToHost(m_connected);
    m_mqtt->subscribe(nullptr,"/Minebea",0);

    if(m_connected) {
        ui->resultTB->setEnabled(true);
        ui->resultTB->setChecked(true);
        ui->resultTE->clear();
        ui->resultTE->setText("连接成功!");
    } else {
        ui->resultTB->setEnabled(true);
        ui->resultTB->setChecked(false);
        ui->resultTE->clear();
        ui->resultTE->setText("连接失败!\r\n"
                              "原因:\r\n"
                              "1、网线未连接或松动\r\n"
                              "2、地址或端口输入有误\r\n"
                              "3、智能采集卡未通电");
    }
}

void HscConnectSetting::saveSetting()
{
    HscCollectSettingModel::connectModel.ip = ui->ipLE->text();
    HscCollectSettingModel::connectModel.port = ui->portLE->text().toInt();
    HscCollectSettingModel::connectModel.sensorInterface = ui->cbox_interfaceType->currentText();

}
