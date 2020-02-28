#include "serversocket.h"
#include <QDebug>
#include "widget/serverConnection/serverconnection.h"

QTcpSocket* serverSocket::serverClient = new QTcpSocket();

serverSocket::serverSocket()
{

}

void serverSocket::connectToSerever(QString ip)
{
    connect(serverClient,&QTcpSocket::readyRead,this,&serverSocket::myReadReady);
    serverClient->connectToHost(ip,1812);
}

void serverSocket::setAction(int action, QByteArray data)
{
    QByteArray pre = QByteArray::number(action) + "~";
    data = pre.append(data);
    qDebug() << "serverSocket (setAction) : data =" << data;
    serverClient->write(data);
}

void serverSocket::myReadReady()
{
    qDebug() << "serverSocket (myReadReady) : msg comming";
}

void serverSocket::myConnected()
{
    //serverSocket::serverClient = socket;
    qDebug() << "serverConnection (myConnected) :  : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) :  : " << serverSocket::serverClient->peerAddress() ;
}
