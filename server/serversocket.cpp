#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include "dynerandroid.h"
#include "widget/login/loginwidget.h"

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
    int bytesToRead = 1000;

    while(bytes != 0)
    {
        if(bytes < bytesToRead )
        {
            dataIn.append(serverClient->readAll());
            bytes = 0;
        }
        else
        {
            dataIn.append(serverClient->read(bytesToRead));
            bytes -= bytesToRead;
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
        case ALLAction::showNotification:
        {


            qint16 type = 0;
            QString msg;
            in >> type >> msg;

            QWidget* loginWidget = static_cast<DynerAndroid*>(myParent)->getLoginWidget();

            if(loginWidget != nullptr)
            {
                static_cast<LogInWidget*>(loginWidget)->setMsg(msg);
                return;
            }
            enum msgType{warning,informative,critical};

            switch (type)
            {
                case warning:
                {
                    QMessageBox::warning(myParent,"Warning",msg);
                    break;
                }
                case informative:
                {
                    QMessageBox::information(myParent,"Information",msg);
                    break;
                }
                case critical:
                {
                    QMessageBox::critical(myParent,"Error",msg);
                    break;
                }
            }

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
    static_cast<DynerAndroid*>(myParent)->loginWidget();
//    serverConnection::deleteAllThread();
//    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
//    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
//    QByteArray data ;
//    QDataStream out(&data,QIODevice::ReadWrite);
//    qint16 i = ALLAction::getTotaltableNo;

//    GlobalData g;
//    QString user = XmlManipulation::getData(g.getTagName(g.clientName),g.getattribute(g.clientName));
//    QString pass = XmlManipulation::getData(g.getTagName(g.clientPass),g.getattribute(g.clientPass));
//    out << i << user << pass ;
//    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
//    //sending req for total table count
//    serverSocket::serverClient->write(data);
//    serverSocket::serverClient->waitForBytesWritten(1000);

    QByteArray data1 ;
    QDataStream out1(&data1,QIODevice::ReadWrite);
    qint16 i = ALLAction::menuData;
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
