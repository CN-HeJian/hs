#include "HscClient.h"

#include <iostream>
using namespace std;


HscClient::HscClient():
    mosqpp::mosquittopp()
{
    //this->m_actions["/hsc/msg"] = &HscMQTT::actionAI;
}

HscClient::~HscClient()
{

}

const std::string &HscClient::host() const
{
    return _host;
}

uint16_t HscClient::port() const
{
    return _port;
}

const std::string &HscClient::bindAdress() const
{
    return _bindAdress;
}

const std::string &HscClient::clientId() const
{
    return _clientId;
}

const std::string &HscClient::username() const
{
    return _username;
}

const std::string &HscClient::password() const
{
    return _password;
}

uint16_t HscClient::keepAlive() const
{
    return _keepAlive;
}

bool HscClient::cleanSession() const
{
    return _cleanSession;
}

bool HscClient::autoReconnect() const
{
    return _autoReconnect;
}

int HscClient::autoReconnectInterval() const
{
    return _autoReconnectInterval;
}

ConnectionState HscClient::connectionState() const
{
    return _connectionState;
}

const mqttmsg &HscClient::will() const
{
    return _will;
}

bool HscClient::isConnectedToHost() const
{
    return _connectionState == STATE_CONNECTED;
}

void HscClient::setHost(const std::string &host)
{
    _host = host;
}

void HscClient::setPort(const uint16_t port)
{
    _port = port;
}

void HscClient::setBindAdress(const string &bindAdress)
{
    _bindAdress = bindAdress;
}

void HscClient::setClientId(const std::string &clientId)
{
    _clientId = clientId;
}

void HscClient::setUsername(const std::string &username)
{
    _username = username;
}

void HscClient::setPassword(const std::string &password)
{
    _password = password;
}

void HscClient::setKeepAlive(const uint16_t keepAlive)
{
    _keepAlive = keepAlive;
}

void HscClient::setCleanSession(const bool cleanSession)
{
    _cleanSession = cleanSession;
}

void HscClient::setAutoReconnect(const bool autoReconnect)
{
    _autoReconnect = autoReconnect;
}

void HscClient::setAutoReconnectInterval(const int autoReconnectInterval)
{
    _autoReconnectInterval = autoReconnectInterval;
}

void HscClient::setWill(const mqttmsg& will){
    _will = will;
}

void HscClient::connectToHost(bool & flag)
{
    if(!initialise(nullptr, _cleanSession)) {
        _connectionState = STATE_INIT;
    } else {
        on_error();
        flag = false;
        return;
    }

    reconnect_delay_set(1,30, true);


    if(!connect(_host.c_str(), _port, _keepAlive/*, _bindAdress.c_str()*/) ){
        _connectionState = STATE_CONNECTED;
    }else{
        on_error();
        flag = false;
    }

    // needed!
    this->loop_start();
}

void HscClient::disconnectFromHost()
{
    if(!disconnect() && !loop_stop(/*true*/)){
        on_error();
    }
}

void HscClient::on_connect(int rc) {
    if(!rc){
        //cout<<"OK connected! "<<endl;
        _connectionState = STATE_CONNECTED;
    }else{
        //cout<<"ERROR connected!"<<endl;
        on_error();
    }
}

void HscClient::on_disconnect(int rc) {
    if(!rc){
        //cout<<"OK disconnect: "<<endl;
        _connectionState = STATE_DISCONNECTED;
    }else{
        //cout<<"ERROR disconnect!"<<endl;
        on_error();
    }
}

void HscClient::on_publish(int mid) {
    cout<<"publish msg id: "<<mid<<endl;
}

void HscClient::on_message(const mqttmsg *message) {
    if(message->payloadlen){
        cout<<message->topic<<", "<<(char*)message->payload<<endl;

        //(this->*m_actions[message->topic])();

        // TODO: message parse

    }else{
        cout<<message->topic<<" (null)"<<endl;
    }
}

void HscClient::on_subscribe(int mid, int qos_count, const int *granted_qos) {

    cout<<"Subscribed "<<mid<<":"<<granted_qos[0]<<endl;
    for(int i=1; i<qos_count; i++){
        cout<<", "<<granted_qos[i];
    }
    cout<<endl;
}

void HscClient::on_unsubscribe(int mid) {
    cout<<mid<<endl;
}

void HscClient::on_log(int level, const char *str) {
    //cout<<"[log]"<<"level:"<<level<<":"<<str<<endl;
}

void HscClient::on_error() {
    cout<<"[error]"<<"errno:"<<errno<<":"<<mosqpp::strerror(errno)<<endl;
}


void HscClient::onDO(int i, bool val)
{
    d_o.set(i, val);
    //mosquittopp::publish(NULL, "/hsc/do", sizeof(d_o), d_o, 1);
}


/*
 * topic: "/hsc/ai"
 *
 */
void HscClient::actionMsg(){
    cout<<"MSG"<<endl;
}
