#include "HscMachineAnalysisAction.h"
#include "ui_HscMachineAnalysisAction.h"
#include <QDebug>

HscMachineAnalysisAction::HscMachineAnalysisAction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscMachineAnalysisAction)
{
    ui->setupUi(this);
}

HscMachineAnalysisAction::~HscMachineAnalysisAction()
{
    delete ui;
}


void HscMachineAnalysisAction::bindWidget(QWidget *widget)
{
    m_widget = dynamic_cast<HscMachineAnalysis *>(widget);
}



/*  点击刷新机台按钮，则需要请求获取当前所有的模具
 *
 *
 */
void HscMachineAnalysisAction::on_toolButton_2_clicked()
{
    m_widget->refreshMachineList();
    //qDebug()<<"refresh machine";
}

/*
 *   刷新数据
*/
void HscMachineAnalysisAction::on_toolButton_3_clicked()
{
    m_widget->refreshPlotWidget();
}

/*
 *  机台分析界面、点击重新绘制
*/
void HscMachineAnalysisAction::on_toolButton_4_clicked()
{
    m_widget->rePlot();
}

void HscMachineAnalysisAction::on_toolButton_5_clicked()
{
    m_widget->connectToServe();
}

/**
 * @brief HscMachineAnalysisAction::on_toolButton_6_clicked
 * 移动游标、添加辅助信息、时间日期以及模次号
 */
void HscMachineAnalysisAction::on_toolButton_6_clicked()
{
    m_widget->addCursor();
}

/*
 *  开启循环播放
*/
void HscMachineAnalysisAction::on_toolButton_7_clicked()
{
    //点击切换图标需要改变样式
    if(m_cycleplot == false){
        m_widget->cyclePlay();
        m_cycleplot = true;
        ui->toolButton_7->setStyleSheet("QToolButton{border: 2px solid rgb(255,255,255);background-image: url(:/resource/icon/xunhuanjiantingred.png)}");
    }else{
        m_widget->endTimer();
        m_cycleplot = false;
        ui->toolButton_7->setStyleSheet("QToolButton{border: 2px solid rgb(255,255,255);background-image: url(:/resource/icon/xunhuanjianting.png)}");
    }
}

/*
 * 保存设置的各种条件
*/
void HscMachineAnalysisAction::on_toolButton_8_clicked()
{
    m_widget->saveCondition();
}

void HscMachineAnalysisAction::on_toolButton_9_clicked()
{
    //点击切换图标需要改变样式
    if(m_zoomLarge == false){
        //m_widget->cyclePlay();
         m_widget->zoomLarge(true);
        m_zoomLarge = true;
        ui->toolButton_9->setStyleSheet("QToolButton{border: 2px solid rgb(255,255,255);background-image: url(:/resource/icon/fangdared.png)}");
    }else{
        //m_widget->endTimer();
        m_widget->zoomLarge(false);
        m_zoomLarge = false;
        ui->toolButton_9->setStyleSheet("QToolButton{border: 2px solid rgb(255,255,255);background-image: url(:/resource/icon/fangda.png)}");
    }
}

//历史查询
void HscMachineAnalysisAction::on_toolButton_11_clicked()
{
    m_widget->queryHistoryData();
}

//导出数据
void HscMachineAnalysisAction::on_toolButton_12_clicked()
{
    m_widget->exportData();
}

//区域统计
void HscMachineAnalysisAction::on_toolButton_13_clicked()
{
    m_widget->staticLabel();
}
