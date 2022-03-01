#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QHostAddress>

class CustomProtocolBaseTcp: public QObject{
    Q_OBJECT
public:
    explicit CustomProtocolBaseTcp(QObject *parent = nullptr);
    ~CustomProtocolBaseTcp();
private:
    QTcpSocket *netServe;
private slots:
    void ReadError(QAbstractSocket::SocketError);
    void ReadData();
signals:
    void receiveResponceFromServer(QByteArray buf);
public:
    void sendRequest(QString cmd);
    void initSignalSlot();
    void connectToService(QString ip,quint16 port);
    void disConnectfromService();

    QString myData;
};

#endif
