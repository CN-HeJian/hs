#include "QMQTT.h"
#include <QDebug>
#include <iostream>

using namespace std;

QMQTT::QMQTT(QObject *parent) :
    QObject(parent),
    HscClient()
{
}

QMQTT::~QMQTT()
{

}

/*
*function: 根据不同topic采集不同厂商传感器
*/
void QMQTT::on_message(const mqttmsg *message) {

    if(message->payloadlen){

        if(message->topic == std::string("/Minebea"))
        {
            emit minReceived(message);
        }

        if(message->topic == std::string("/kistler"))
        {
            emit kisReceived(message);
        }

    }else{
        cout<<message->topic<<" (null)"<<endl;
    }
}
