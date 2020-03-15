#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "dynerandroid.h"

QTcpSocket* serverSocket::serverClient = new QTcpSocket();

serverSocket::serverSocket(QWidget* parent)
{
    myParent = parent;
}

void serverSocket::connectToSerever(QString ip)
{
    connect(serverClient,&QTcpSocket::readyRead,this,&serverSocket::myReadReady);
    connect(serverClient,&QTcpSocket::connected,this,&serverSocket::myConnected,Qt::DirectConnection);
    connect(serverClient,&QTcpSocket::disconnected,this,&serverSocket::myDisconnect);
    serverClient->connectToHost(ip,1812);
}

void serverSocket::myReadReady()
{
    // get the information
    QByteArray dataIn = serverClient->readAll();
    qDebug() << "serverConnection (myReadReady) : Data in: " << dataIn;

    QDataStream in(&dataIn,QIODevice::ReadWrite);

    qint16 action;
    in >> action;

    qDebug() << "serverConnection (myReadReady) : action : " << action;

    switch (action)
    {
        case ALLAction::error :
        {
            qDebug() << "serverConnection (myReadReady) : list : " << dataIn;
            break;
        }
        case ALLAction::getTotaltableNo :
        {
            qint16 tblNo;
            in >> tblNo;
            qDebug() << "serverConnection (myReadReady) : total Table no : " << tblNo;

            static_cast<DynerAndroid*>(myParent)->dinningTableList(tblNo);

            break;

        }
        case ALLAction::menuData :
        {

            qint16 count = 0;

            in >> count;

            int i = 0;
            for(i = 0;count > i ; ++i)
            {
                QString id,name,category;
                double price;
                in >> id >> name >> category >> price;
                GlobalData::setMendsduItem(id,name,category,price);
                qDebug() << endl<< "serverConnection (myReadReady) : id : " << GlobalData::menuDataList.last()->id ;
                qDebug() << "serverConnection (myReadReady) : name : " << GlobalData::menuDataList.last()->name ;
                qDebug() << "serverConnection (myReadReady) : category : " << GlobalData::menuDataList.last()->category ;
                qDebug() << "serverConnection (myReadReady) : price : " << GlobalData::menuDataList.last()->price << endl ;
            }
            qDebug() << "serverConnection (myReadReady) : Total Item : " << i;

            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << dataIn;
            QMessageBox::StandardButton reply = QMessageBox::critical(new QWidget,"Diconnected","Server has been disconnected,\n App will exit",QMessageBox::Ok);
            if(reply == QMessageBox::Ok)
                qApp->exit(0);
        }
    }

    /*QString data = serverClient->readAll();


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
    }*/
}

void serverSocket::myConnected()
{
    serverConnection::deleteAllThread();
    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::getTotaltableNo;
    out << i ;
    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
    //sending req for total table count
    serverSocket::serverClient->write(data);
    serverSocket::serverClient->waitForReadyRead(2000);

    QByteArray data1 ;
    QDataStream out1(&data1,QIODevice::ReadWrite);
    i = ALLAction::menuData;
    out1 << i ;
    qDebug() << "DynerAndroid (dinningTableList) : data to send : " << data1 ;
    //sending req for total table count
    serverSocket::serverClient->write(data1);
}

void serverSocket::myDisconnect()
{
    static_cast<DynerAndroid*>(myParent)->closeWidget();
    qDebug() << "serverConnection (myDiconnected) : state : " << serverSocket::serverClient->state() ;
}
