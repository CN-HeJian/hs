#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/resource/qss/blue.qss");
    qss.open(QFile::ReadOnly);
    if(qss.isOpen()){
        qApp->setStyleSheet(QLatin1String(qss.readAll()));
        qss.close();
       // qDebug()<<"d";
    }

    MainWindow w;

    w.setWindowTitle("凤凰机台监控");

    w.setMinimumSize(1600, 1000);

    w.show();

    return a.exec();
}
