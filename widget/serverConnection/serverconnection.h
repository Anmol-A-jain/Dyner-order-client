#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QWidget>
#include <QTcpSocket>
#include <QThread>
#include <QProcess>
#include <QHostInfo>
#include <QComboBox>
#include "server/serversocket.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"

class findByPing;

namespace Ui {
class serverConnection;
}


class serverConnection : public QWidget
{
    Q_OBJECT

public:
    explicit serverConnection(QWidget *parent = nullptr);
    ~serverConnection();
    void connectToServer(QString ip);

private slots:
    void on_btnConnect_clicked();

    void stateChanged(QAbstractSocket::SocketState state);

    void on_btnauto_clicked();

private:
    Ui::serverConnection *ui;
    QWidget* myParent;
    QString baseIp;
};


class findByPing : public QThread
{
    Q_OBJECT
public:
    findByPing(QString ipAddress,QWidget* parent = nullptr)
    {
        myParent = parent;
        this->currIp = ipAddress;
        isActive = false;
    }

    void run()
    {
        socket = new QTcpSocket();
        connect(socket,&QTcpSocket::connected,this,&findByPing::myConnected);
        connect(socket,&QTcpSocket::stateChanged,this,&findByPing::mystateChange);
        socket->connectToHost(this->currIp,1812);

        exec();
    }

public slots :

    void myConnected()
    {
        static_cast<serverConnection*>(myParent)->connectToServer(currIp);

        //serverSocket::serverClient = socket;
        /*GlobalData g;
        XmlManipulation::setData(g.getTagName(g.ipAddress),g.getattribute(g.ipAddress),socket->peerAddress().toString());
        qDebug() << "serverConnection (myConnected) : ip address : " << socket->peerAddress().toString() ;*/

        socket->disconnectFromHost();
        qDebug() << "findByPing (myConnected) : state : " << socket->state() ;

        //exit(0);

    }
    void mystateChange(QAbstractSocket::SocketState state)
    {
        //qDebug() << "findByPing (stateChanged) : state : " << serverSocket::serverClient->state() ;
        if(state == QTcpSocket::ConnectingState)
        {
            isActive = true;
        }
        if(state == QTcpSocket::UnconnectedState && isActive)
        {
            exit(0);
        }
    }

private:
    QString currIp;
    QTcpSocket* socket;
    bool isActive;
    QWidget* myParent;
};

#endif // SERVERCONNECTION_H
