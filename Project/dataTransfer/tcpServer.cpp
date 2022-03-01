#include "tcpServer.h"


TcpServer::TcpServer(uint16_t m_TcpPort,QObject*parent):QObject(parent),m_port(m_TcpPort){
    m_tcpServer = new QTcpServer(this);
    initSignalSlot();
}

TcpServer::~TcpServer(){

}

void TcpServer::initSignalSlot(){
    connect(m_tcpServer, &QTcpServer::newConnection, this, &TcpServer::NewConnectionSlot );
}




//槽函数---success
void TcpServer::NewConnectionSlot(){
    m_currentClient = m_tcpServer->nextPendingConnection();
    //m_currentClient->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    m_tcpClient.append(m_currentClient);
    QString ip = m_currentClient->peerAddress().toString();
    uint16_t port = m_currentClient->peerPort();
    connect(m_currentClient, SIGNAL(readyRead()), this, SLOT(receiveDataSlot()));
    connect(m_currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    qDebug()<<"New connect: "<<"ip: "<<ip<<"port: "<<port;
}

//输出：是否监听成功
bool TcpServer::listenPort(uint16_t port){
    bool ok = m_tcpServer->listen(QHostAddress::Any,port);
    if(ok){
        qDebug()<<"listen port success";
        return true;
    }
    qDebug()<<"listen port failed";
    return false;
}

//关闭当前开启的服务
bool TcpServer::closeServer(){
    qDebug()<<"try to unListen port "<<endl;
    for(int i=0;i<m_tcpClient.length();++i){
        m_tcpClient[i]->disconnectFromHost();
        bool ok = m_tcpClient[i]->waitForDisconnected(1000);
        if(!ok){
            qDebug()<<"disconnect failed"<<endl;
            return false;
        }
        m_tcpClient.removeAt(i);
    }
    m_tcpServer->close();
    return true;
}

//当某个客户端断开连接,删除这个客户端---success
void TcpServer::disconnectedSlot(){
    qDebug()<<"delete "<<"the number of client "<<m_tcpClient.size()<<endl;
    for(int i=0; i<m_tcpClient.length(); i++)
    {
        if(m_tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            QString ip = m_tcpClient[i]->peerAddress().toString();
            uint16_t port = m_tcpClient[i]->peerPort();
            qDebug()<<"delete one client "<<"ip"<<ip<<"port "<<port<<endl;
            m_tcpClient[i]->destroyed();
            m_tcpClient.removeAt(i);
        }
    }
}

//获取客户端的请求
void TcpServer::receiveDataSlot(){
    for(int i=0; i<m_tcpClient.length(); i++)
    {
        QByteArray buffer = m_tcpClient[i]->readAll();
        if(buffer.isEmpty())
            continue;
        QString ip = m_tcpClient[i]->peerAddress().toString();
        uint16_t port = m_tcpClient[i]->peerPort();
        qDebug()<<"Receive buffer from "<<"Ip: "<<ip<<"port: "<< port<<"buffer: "<<buffer;
        emit getOneRequestFromClient(buffer,ip,port);
    }
}

//给服务端发送数据
void TcpServer::sendData(QString ClientIp,uint16_t port,QString data){
    if(data==""){
        return ;
    }

    QString t_header = "##@$";
    QString t_tail = "**$#";
    //QString t_str = t_list.join(",");;
    data  = t_header+"::"+ data+"::"+t_tail;


//    if(data.size()<10000){
        //qDebug()<<"response message: "<<data;
//    }
    for(int i=0; i<m_tcpClient.length(); i++)
    {
        QString current_ip = m_tcpClient[i]->peerAddress().toString();
        uint16_t current_port = m_tcpClient[i]->peerPort();

        if(current_ip==ClientIp&&current_port==port)
        {
           // m_tcpClient[i]->setSocketOption(QAbstractSocket::LowDelayOption, 1);
            bool ok = m_tcpClient[i]->write(data.toLatin1());
            //m_tcpClient[i]->flush();
            if(!ok){
                qDebug()<<"service send failed"<<endl;
            }else{
                qDebug()<<"send success ok: "<<ok<<endl;
            }
            break;
        }
    }

}
