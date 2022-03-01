#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/resource/icon/mainicon.png"));

    initialize();
    initSignalSlots();
};


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    // 在线监控模块
//    m_onlineMonitor = new HscOnlineMonitor(this);
//    ui->stackedWidget->addWidget(m_onlineMonitor);
//    ui->menuBar->bindTabView(0, m_onlineMonitor);

    // 机台分析模块
    m_machineAnalysis = new HscMachineAnalysis(this);
    ui->stackedWidget->addWidget(m_machineAnalysis);
    ui->menuBar->bindTabView(1, m_machineAnalysis);

    // 设置模块
//    m_softwareSetting = new HscSoftwareSetting(this);
//    ui->stackedWidget->addWidget(m_softwareSetting);
//    ui->menuBar->bindTabView(2, m_softwareSetting);

    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if ((QMessageBox::information(this, tr("提示！"), tr("是否退出程序？"), QMessageBox::Yes|QMessageBox::No))
            == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::initSignalSlots()
{

}

void MainWindow::setCurrentTabView(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
