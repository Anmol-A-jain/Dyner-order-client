#include "serversocket.h"
#include <QDebug>
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
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
    connect(serverClient,&QTcpSocket::disconnected,this,&serverSocket::myDisconnect);
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
    if(list.size() == 1)
    {
        return;
    }

    bool isFirst = true;
    QStringList dataList ;
    int action;

    qDebug() << "serverConnection (myReadReady) : list : " << list;
    qDebug() << "serverConnection (myReadReady) : list.size() : " << list.size();

    for(int i = 0 ;i < list.length() ; ++i)
    {
        qDebug() << "serverConnection (myReadReady) : list.at(" + QString::number(i) +"):" << list[i];
        if(isFirst)
        {
            action = list.at(i).toInt() ;
            isFirst = false;
        }
        else
        {
            dataList.push_back(list.at(i));
        }
    }

    qDebug() << "serverConnection (myReadReady) : action : " << action;
    qDebug() << "serverConnection (myReadReady) : dataList : " << dataList;

    QString value = dataList.at(0);
    qDebug() << "serverConnection (myReadReady) : total Table no : " << value;

    switch (action)
    {
        case ALLAction::error :
        {
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            for(int i = 0 ; i < list.size() ; ++i)
            {
                QString value = dataList.first();
                qDebug() << "serverConnection (myReadReady) : total Table no : " << value;
                int tbl = value.toInt();
                static_cast<DynerAndroid*>(myParent)->dinningTableList(tbl);
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
    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
    QByteArray data = serverSocket::setAction(ALLAction::getTotaltableNo,"");
    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
    //sending req for total table count
    serverSocket::serverClient->write(data);
}

void serverSocket::myDisconnect()
{
    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.ipAddress),g.getattribute(g.ipAddress),"");

    static_cast<DynerAndroid*>(myParent)->logInWidget();
    qDebug() << "serverConnection (myDiconnected) : state : " << serverSocket::serverClient->state() ;
}
