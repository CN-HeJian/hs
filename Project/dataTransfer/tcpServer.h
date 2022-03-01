// 版权： 2021 华塑软件研究室
// 许可证： GPL
// 作者： 贺鉴
// 此类实现基于tcp协议的网络通信
#ifndef TcpServer_H
#define TcpServer_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QtNetwork>
#include <QByteArray>
#include <QDataStream>
#include <vector>
using namespace  std;

class TcpServer: public QObject{
    Q_OBJECT
public:
    TcpServer(uint16_t m_port,QObject *parent = Q_NULLPTR);
    ~TcpServer();
private:
    QTcpServer *m_tcpServer;
    QList<QTcpSocket*> m_tcpClient;
    QTcpSocket *m_currentClient;
    uint16_t m_port;
private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void receiveDataSlot();
    void initSignalSlot();
public:
    bool listenPort(uint16_t port);
    bool closeServer();
public:
    void sendData(QString ClientIp,uint16_t port,QString data);
    //void sendData(QString ClientIp,uint16_t port,vector<pair<QString,float>> data);
signals:
    void getOneRequestFromClient(QByteArray,QString,uint16_t);
};

#endif
