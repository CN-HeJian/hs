#include "CustomProtocolBaseTcp.h".h"
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

CustomProtocolBaseTcp::CustomProtocolBaseTcp(QObject*parent):QObject(parent){
    netServe = new QTcpSocket();
    netServe->abort();

    //netServe->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    initSignalSlot();
}



void CustomProtocolBaseTcp::initSignalSlot(){
    connect(netServe,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(netServe, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));
}


CustomProtocolBaseTcp::~CustomProtocolBaseTcp(){

}

void CustomProtocolBaseTcp::connectToService(QString ip,quint16 port){
    netServe->abort();
    netServe->connectToHost(ip,port);
    qDebug()<<"try to connect";
    if(netServe->waitForConnected(1000)){
        //ToDo 连接成功之后干啥
        qDebug()<<"connect success";
        //QMessageBox msgBox;
       // msgBox.setText("连接成功      ");
        //msgBox.exec();
    }else{
        qDebug()<<"connect failed";
        QMessageBox msgBox;
        msgBox.setText("连接失败      ");
        msgBox.exec();
    }
}

void CustomProtocolBaseTcp::disConnectfromService(){
    netServe->disconnectFromHost();
    qDebug()<<"try to disconnect";
    if(netServe->state()== QAbstractSocket::UnconnectedState || netServe->waitForDisconnected(1000)){
        //ToDo 断开连接之后干啥
        qDebug()<<"disconnect success";
    }
}

//收到响应回来的数据---success
void CustomProtocolBaseTcp::ReadData(){


    myData.append(netServe->readAll());
    qDebug()<<"MyData: "<<myData;
    //char split = '::';
    QStringList t_data = myData.split("::");
    //myData.clear();

//     for(int i=0;i<t_data.size();i++){
//         //myData.clear();
//        if(t_data[i]=="##@$::"){
//            continue;
//        }else {
//            //qDebug()<<"t_data: "<<t_data[i];
//            emit receiveResponceFromServer(t_data[i].toLatin1());
//        }
//     }

    if(t_data.size()==3){
        qDebug()<<"h"<<endl;
        qDebug()<<t_data[1]<<t_data[0]<<endl;
        if(t_data[0]=="##@$" && t_data[2]=="**$#"){
            myData.clear();
            qDebug()<<t_data[1]<<endl;
            emit receiveResponceFromServer(t_data[1].toLatin1());
        }
    }

    if(t_data.size()==5){
        if(t_data[0]=="##@$" && t_data[4]=="**$#" && t_data[2]=="**$###@$"){
            myData.clear();
            emit receiveResponceFromServer(t_data[1].toLatin1());
            emit receiveResponceFromServer(t_data[3].toLatin1());
        }
    }

    /*
    char split = '::';
    QStringList t_data = myData.split("::");
    if(t_data.size()==3)
    {
        if((t_data[0]=="##@$")&&(t_data[2]=="**$#"))
       {
           myData.clear();
           QString t_repyMessage = t_data[1];
           if(!t_repyMessage.isEmpty()){
               //ToDo 当收到数据之后干啥
               emit receiveResponceFromServer(t_repyMessage.toLatin1());

           }
        }
    }
    */

    //qDebug()<<"CustomProtocolBaseTcp: "<<buffer.size();
    //if(!myData.isEmpty()){
     //  //ToDo 当收到数据之后干啥
     //   emit receiveResponceFromServer(myData.toLatin1());
    //}
}

//发送请求---success
void CustomProtocolBaseTcp::sendRequest(QString cmd){
    if(cmd.size()){
        qDebug()<<"ready to send my request "<< cmd ;
        bool ok = netServe->write(cmd.toLatin1());
        if(!ok){
//            QMessageBox msgBox;
//            msgBox.setText("数据采集中心断开");
//            msgBox.exec();
            qDebug()<<"message send failed"<<endl;
        }
    }
}

void CustomProtocolBaseTcp::ReadError(QAbstractSocket::SocketError)
{
    netServe->disconnectFromHost();
    qDebug()<<"why connect failed "<< netServe->errorString();
}
