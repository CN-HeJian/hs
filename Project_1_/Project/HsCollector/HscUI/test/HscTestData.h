#ifndef HSCTESTDATA_H
#define HSCTESTDATA_H

#include <QObject>
#include <QThread>
#include <QTimer>

class HscTestData : public QThread
{
    Q_OBJECT
public:
    HscTestData(QObject *parent = 0);


protected:
    void run();

signals:
    void testData(QString str);

private slots:

private:
    QTimer *m_timer;

    int count = 1;
    static double data;
    static int mark;
};

#endif // HSCTESTDATA_H
