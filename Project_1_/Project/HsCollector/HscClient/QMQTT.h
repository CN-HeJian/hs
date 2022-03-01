#ifndef QMQTT_H
#define QMQTT_H

#include <QObject>

#include "HscClient.h"

class QMQTT : public QObject, public HscClient
{
    Q_OBJECT
public:
    explicit QMQTT(QObject *parent = 0);
    virtual ~QMQTT();

signals:
    void minReceived(const mqttmsg* message);
    void kisReceived(const mqttmsg* message);

    void send(const mqttmsg* message);

private:
    virtual void on_message(const mqttmsg* message);

    mqttmsg msg;
};

#endif // QMQTT_H
