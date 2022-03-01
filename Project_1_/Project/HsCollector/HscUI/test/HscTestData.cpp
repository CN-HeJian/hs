#include "HscTestData.h"

#include <math.h>
#include <ctime>
#include <QDebug>

double HscTestData::data = 0;
int HscTestData::mark = 0;

HscTestData::HscTestData(QObject *parent)
    : QThread (parent)
{

}

void HscTestData::run()
{
    m_timer = new QTimer();
    m_timer->setTimerType(Qt::PreciseTimer);
    connect(m_timer, &QTimer::timeout, this, [&]{
        QString str;
        data += 0.01;
        for (auto j(0); j<10; ++j) {
            str += QString::number(((j+1)*10)*abs(sin(data+mark))) + ",";
        }
        str += QString::number(count);
        if (count == 1200) {
            count = 1;
            data = 0;
            qsrand(time(NULL));
            mark = qrand() % 5;
        } else {
            ++count;
        }
//        qDebug() << str;
        emit testData(str);
    });
    m_timer->start(2);

    this->exec();
}

