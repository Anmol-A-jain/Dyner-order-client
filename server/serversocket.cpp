#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
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
    connect(serverClient,&QTcpSocket::readyRead,this,&serverSocket::myReadReady);
    connect(serverClient,&QTcpSocket::connected,this,&serverSocket::myConnected,Qt::DirectConnection);
    connect(serverClient,&QTcpSocket::disconnected,this,&serverSocket::myDisconnect);
    serverClient->connectToHost(ip,1812);
}

void serverSocket::myReadReady()
{
    // get the information
    //serverClient->waitForReadyRead(1000);
    int bytes = serverClient->bytesAvailable();
    QByteArray dataIn ;//= serverClient->readAll();
    qDebug() << "serverConnection (myReadReady) : Data available count: " << bytes;

    while(bytes != 0)
    {
        if(bytes < 1000 )
        {
            dataIn.append(serverClient->readAll());
            bytes = 0;
        }
        else
        {
            dataIn.append(serverClient->read(1000));
            bytes -= 1000;
        }
        qDebug() << "serverConnection (myReadReady) : Data in: " << dataIn;
        qDebug() << "serverConnection (myReadReady) : Data count: " << bytes;
    }

    qDebug() << "serverConnection (myReadReady) : Data in: " << dataIn;
    qDebug() << "serverConnection (myReadReady) : Data count: " << bytes;

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
                GlobalData::setMenuItem(id,name,category,price);
                qDebug() << endl<< "serverConnection (myReadReady) : id : " << GlobalData::menuDataList.last()->id ;
                qDebug() << "serverConnection (myReadReady) : name : " << GlobalData::menuDataList.last()->name ;
                qDebug() << "serverConnection (myReadReady) : category : " << GlobalData::menuDataList.last()->category ;
                qDebug() << "serverConnection (myReadReady) : price : " << GlobalData::menuDataList.last()->price << endl ;
            }
            qDebug() << "serverConnection (myReadReady) : Total Item : " << i;
            break;
        }
        case ALLAction::getCustInfo:
        {
            QString name,mblNo;
            in >> name >> mblNo;
            qDebug() << "serverConnection (myReadReady) : cust data : " << name << ":" << mblNo ;
            static_cast<DynerAndroid*>(myParent)->callCartObject(name,mblNo);
            break;
        }
        default:
        {
            qDebug() << "serverConnection (myReadReady) : default case called : " << dataIn;
            QMessageBox::StandardButton reply = QMessageBox::critical(new QWidget,"incomplete data","Something went wrong,\n App will exit",QMessageBox::Ok);
            if(reply == QMessageBox::Ok)
                qApp->exit(0);
        }
    }
}

void serverSocket::myConnected()
{
    serverConnection::deleteAllThread();
    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::getTotaltableNo;

    GlobalData g;
    QString name = XmlManipulation::getData(g.getTagName(g.clientName),g.getattribute(g.clientName));
    out << i << name ;
    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
    //sending req for total table count
    serverSocket::serverClient->write(data);
    serverSocket::serverClient->waitForBytesWritten(1000);

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
