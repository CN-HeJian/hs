#ifndef HSCCLIENT_H
#define HSCCLIENT_H

#include "HscClientHeader.h"

#include "mosquittopp.h"
#include "HscMsgIn.h"

#include <cstdint>
#include <string>
#include <unordered_map>

using mqttmsg = struct mosquitto_message;

enum ConnectionState
{
    STATE_INIT = 0,
    STATE_CONNECTING,
    STATE_CONNECTED,
    STATE_DISCONNECTED
};

class HSCCLIENTSHARED_EXPORT HscClient:
        public mosqpp::mosquittopp
{
public:
    HscClient();
    virtual ~HscClient();

    void onDO(int i, bool val);

public:
    const std::string& host() const;
    uint16_t port() const;
    const std::string &bindAdress() const;
    const std::string& clientId() const;
    const std::string& username() const;
    const std::string& password() const;
    uint16_t keepAlive() const;
    bool cleanSession() const;
    bool autoReconnect() const;
    int autoReconnectInterval() const;
    ConnectionState connectionState() const;
    const mqttmsg& will() const;
    bool isConnectedToHost() const;


    void setHost(const std::string& host);
    void setPort(const uint16_t port);
    void setBindAdress(const std::string& bindAdress);
    void setClientId(const std::string& clientId);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setKeepAlive(const uint16_t keepAlive);
    void setCleanSession(const bool cleanSession);
    void setAutoReconnect(const bool autoReconnect);
    void setAutoReconnectInterval(const int autoReconnectInterval);
    void setWill(const mqttmsg& will);
    void connectToHost(bool &flag);
    void disconnectFromHost();

public:
    virtual void on_connect(int rc);
    virtual void on_disconnect(int rc);
    virtual void on_publish(int mid);
    virtual void on_message(const struct mosquitto_message * message);
    virtual void on_subscribe(int mid, int qos_count, const int * granted_qos);
    virtual void on_unsubscribe(int mid);
    virtual void on_log(int level, const char * str);
    virtual void on_error();

private:
    void actionMsg();

private:
    HscMsgIn msg;
    HscMsgIOD<HSC_NUM_DO> d_o;

    //
    // can not use std::function
    // typedef std::function< int(int) > HscHscClientFunc;
    typedef void (HscClient::* HscHscClientFunc) (void);
    std::unordered_map<char*, HscHscClientFunc > m_actions;
public:
private:

    std::string _host;
    uint16_t _port;
    std::string _bindAdress;
    std::string _clientId;
    std::string _username;
    std::string _password;
    uint16_t _keepAlive;
    ConnectionState _connectionState;
    bool _cleanSession;
    bool _autoReconnect;
    int _autoReconnectInterval;
    mqttmsg _will;
};

#endif // HSCCLIENT_H
