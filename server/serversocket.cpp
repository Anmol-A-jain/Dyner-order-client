#include "serversocket.h"
#include <QDebug>
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "dynerandroid.h"

QTcpSocket* serverSocket::serverClient = new QTcpSocket();

serverSocket::serverSocket(QWidget* parent)
{
    myParent = parent;
}

void serverSocket::connectToSerever(QString ip)
{
    connect(serverClient,&QTcpSocket::readyRead,this,&serverSocket::myReadReady,Qt::DirectConnection);
    connect(serverClient,&QTcpSocket::connected,this,&serverSocket::myConnected,Qt::DirectConnection);
    connect(serverClient,&QTcpSocket::disconnected,this,&serverSocket::myDisconnect,Qt::DirectConnection);
    serverClient->connectToHost(ip,1812);
}

QByteArray serverSocket::setAction(int action, QByteArray data)
{
    QByteArray msg = QByteArray::number(action) + "~";
    msg.append(data);
    qDebug() << "serverSocket (setAction) : data =" << msg;
    return msg;
}

void serverSocket::myReadReady()
{
    QString data = serverClient->readAll();
    QStringList list = data.split('~');

    int action = list.at(0).toInt() ;
    QString value = list.at(1);

    qDebug() << "serverConnection (myReadReady) : list : " << list;

    switch (action)
    {
        case ALLAction::error :
        {
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            if(value != "")
            {
                qDebug() << "serverConnection (myReadReady) : total Table no : " << value;
                int tbl = value.toInt();
                static_cast<DynerAndroid*>(myParent)->loadTable(tbl);
            }
            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << data;
            break;
        }
    }
}

void serverSocket::myConnected()
{
    qDebug() << "serverConnection (myConnected) :  : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) :  : " << serverSocket::serverClient->peerAddress() ;
}

void serverSocket::myDisconnect()
{
    static_cast<DynerAndroid*>(myParent)->showConnectionWdget();
    qDebug() << "serverConnection (myDiconnected) :  : " << serverSocket::serverClient->state() ;
}
