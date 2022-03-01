
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <windef.h>
#include <QMessageBox>
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <QLibrary>
#include "tool/templateSingle.hpp"
#include "ui/allmachineWindow.h"
//#include <manager/controlCenter.h>


//QLibrary qlib("GetFRSData.dll");



int main(int argc, char *argv[])
{
    QApplication program(argc, argv);
    QMainWindow window;

    allMachineWindow *widget = new allMachineWindow();
    window.setCentralWidget(widget);

    //ControlCenter m_manager(6343);
    window.setWindowTitle("数据采集终端");
    QIcon icon;
    icon.addFile(":/dataAcq.png", QSize(400,400));
    //item->setIcon(icon);

    window.setWindowIcon(icon);
    //window.resize(1500,800);//1500 800
    window.setMinimumSize(1500, 800);

    window.show();
    return program.exec();
}

