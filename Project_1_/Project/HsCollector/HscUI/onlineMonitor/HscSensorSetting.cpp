#include "HscSensorSetting.h"
#include "ui_HscSensorSetting.h"

#include <QColorDialog>
#include <QDebug>

#include "HscCollectSettingModel.h"

HscSensorSetting::HscSensorSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscSensorSetting)
{
    ui->setupUi(this);

    initView();
    loadModelData();
    initSignalSlots();
}

HscSensorSetting::~HscSensorSetting()
{
    delete ui;
}

void HscSensorSetting::saveSetting()
{
    for (auto i(0); i<ui->tableWidget->rowCount(); ++i) {
        HscCollectSettingModel::sensorsModel[i].enable = m_checkBoxs[i]->isChecked() ? 1 : 0;
        HscCollectSettingModel::sensorsModel[i].capacity = ui->tableWidget->item(i, 1)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].output = ui->tableWidget->item(i, 2)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].surfaceShape = m_cboxSections[i]->currentText();
        HscCollectSettingModel::sensorsModel[i].diameter = ui->tableWidget->item(i, 4)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].horizontal = ui->tableWidget->item(i, 5)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].vertical = ui->tableWidget->item(i, 6)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].sectionArea = ui->tableWidget->item(i, 7)->text().toDouble();
        HscCollectSettingModel::sensorsModel[i].channel = ui->tableWidget->item(i, 8)->text();
        HscCollectSettingModel::sensorsModel[i].sensorType = m_cboxCollects[i]->currentText();
        HscCollectSettingModel::sensorsModel[i].unit = m_cboxUnits[i]->currentText();
    }
}

void HscSensorSetting::initView()
{
    m_checkBoxs.clear();
    m_cboxSections.clear();
    m_cboxCollects.clear();
    m_pbtnColor.clear();
    m_curveColor.clear();
    m_curveColor.resize(10);
    m_cboxUnits.clear();
    QStringList sectionType = { "圆形", "矩形", "其他" };
    QStringList collectType = { "压力", "温度", "位置" };
    QStringList unitType = { "MPa", "Bar" };
    for (auto i(0); i<ui->tableWidget->rowCount(); ++i) {
        // 调整行高
        ui->tableWidget->setRowHeight(i, 24);

        // 新增组件
        QWidget *wid = new QWidget;
        QHBoxLayout *lay = new QHBoxLayout;
        wid->setLayout(lay);
        lay->setSpacing(0);
        lay->setMargin(0);
        QCheckBox *check = new QCheckBox;
        lay->addWidget(check);
        lay->setAlignment(Qt::AlignHCenter);
        ui->tableWidget->setCellWidget(i, 0, wid);
        m_checkBoxs.push_back(check);

        // 下拉选项
        QComboBox *cboxSection = new QComboBox;
        cboxSection->addItems(sectionType);
        ui->tableWidget->setCellWidget(i, 3, cboxSection);
        m_cboxSections.push_back(cboxSection);

        // 采集类型
        QComboBox *cboxCollect = new QComboBox;
        cboxCollect->addItems(collectType);
        ui->tableWidget->setCellWidget(i, 9, cboxCollect);
        m_cboxCollects.push_back(cboxCollect);

        // 颜色选择
        QPushButton *pbtnColor = new QPushButton;
        ui->tableWidget->setCellWidget(i, 10, pbtnColor);
        m_pbtnColor.push_back(pbtnColor);

        // 单位
        QComboBox *cboxUnit = new QComboBox;
        cboxUnit->addItems(unitType);
        ui->tableWidget->setCellWidget(i, 11, cboxUnit);
        m_cboxUnits.push_back(cboxUnit);

        ui->tableWidget->item(i, 5)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i, 6)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i, 7)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i, 8)->setFlags(Qt::NoItemFlags);
    }

}

void HscSensorSetting::initSignalSlots()
{
    for (auto i(0); i<ui->tableWidget->rowCount(); ++i) {
        // 设置通道选项
        connect(m_checkBoxs[i], &QCheckBox::clicked, this, &HscSensorSetting::setSelectedAisle);
        // 截面形状改变
        connect(m_cboxSections[i], &QComboBox::currentTextChanged, this, &HscSensorSetting::setSectionType);
        // 设置颜色
        connect(m_pbtnColor[i], &QPushButton::clicked, this, &HscSensorSetting::setCurveColor);
        // 单位转换
        connect(m_cboxCollects[i], &QComboBox::currentTextChanged, this, &HscSensorSetting::setCollectUnit);
    }
}

void HscSensorSetting::loadModelData()
{
    for (auto i(0); i<ui->tableWidget->rowCount(); ++i) {
        auto &model = HscCollectSettingModel::sensorsModel[i];
        // 启用
        m_checkBoxs[i]->setChecked(model.enable);

        // 额定容量
        ui->tableWidget->item(i, 1)->setText(QString::number(model.capacity));

        // 额定输出
        ui->tableWidget->item(i, 2)->setText(QString::number(model.capacity));

        // 受压面形状
        m_cboxSections[i]->setCurrentText(model.surfaceShape);

        // 直径
        ui->tableWidget->item(i, 4)->setText(QString::number(model.diameter));

        // 横截面长度
        ui->tableWidget->item(i, 5)->setText(QString::number(model.horizontal));

        // 纵界面长度
        ui->tableWidget->item(i, 6)->setText(QString::number(model.vertical));

        // 横截面积
        ui->tableWidget->item(i, 7)->setText(QString::number(model.sectionArea));

        // 通道名称
        ui->tableWidget->item(i, 8)->setText(model.channel);

        // 传感器类型
        m_cboxCollects[i]->setCurrentText(model.sensorType);

        // 曲线颜色
        m_pbtnColor[i]->setStyleSheet(tr("background-color:%1").arg(model.curveColor));

        // 单位
        m_cboxUnits[i]->setCurrentText(model.unit);
    }
}

void HscSensorSetting::setSelectedAisle()
{
    int index = m_checkBoxs.indexOf(static_cast<QCheckBox *>(sender()));
    qDebug() << index;
}

void HscSensorSetting::setSectionType(const QString &str)
{
    int index = m_cboxSections.indexOf(static_cast<QComboBox *>(sender()));
    if (str == "圆形") {
        ui->tableWidget->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
        ui->tableWidget->item(index, 5)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 6)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 7)->setFlags(Qt::NoItemFlags);
    } else if (str == "矩形") {
        ui->tableWidget->item(index, 4)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 5)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
        ui->tableWidget->item(index, 6)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
        ui->tableWidget->item(index, 7)->setFlags(Qt::NoItemFlags);
    } else if (str == "其他") {
        ui->tableWidget->item(index, 4)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 5)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 6)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(index, 7)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
    }
}

void HscSensorSetting::setCollectUnit(const QString &str)
{
    int index = m_cboxCollects.indexOf(static_cast<QComboBox *>(sender()));
    if (str == "压力") {
        QStringList list = { "MPa", "Bar" };
        m_cboxUnits[index]->clear();
        m_cboxUnits[index]->addItems(list);
    } else if (str == "温度") {
        QStringList list = { "℃", "℉", "K" };
        m_cboxUnits[index]->clear();
        m_cboxUnits[index]->addItems(list);
    } else if (str == "位置") {
        QStringList list = { "mm", "inch" };
        m_cboxUnits[index]->clear();
        m_cboxUnits[index]->addItems(list);
    }
}

void HscSensorSetting::setCurveColor()
{
    int index = m_pbtnColor.indexOf(static_cast<QPushButton *>(sender()));
    QColorDialog colorSelect;
    QColor color = colorSelect.getColor();
    if (color.isValid()) {
//        qDebug() << color.name();
        m_pbtnColor[index]->setStyleSheet(tr("background-color:%1").arg(color.name()));
        HscCollectSettingModel::sensorsModel[index].curveColor = color.name();
    }

}
