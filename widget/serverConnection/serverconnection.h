#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QWidget>
#include <QTcpSocket>
#include <QThread>
#include <QProcess>
#include <QHostInfo>
#include <QComboBox>
#include "server/serversocket.h"

namespace Ui {
class serverConnection;
}


class serverConnection : public QWidget
{
    Q_OBJECT

public:
    explicit serverConnection(QWidget *parent = nullptr);
    ~serverConnection();

private slots:
    void on_btnConnect_clicked();

    void stateChanged(QAbstractSocket::SocketState state);

    void on_btnauto_clicked();

    void on_btnLogin_clicked();

private:
    Ui::serverConnection *ui;
    QWidget* myParent;
    QString baseIp;
};


class findByPing : public QThread
{
    Q_OBJECT
public:
    findByPing(QString ipAddress)
    {
        this->currIp = ipAddress;
    }

    void run()
    {
        socket = new QTcpSocket();
        connect(socket,&QTcpSocket::connected,this,&findByPing::myConnected);
        socket->connectToHost(this->currIp,1812);

        exec();
    }

public slots :

    void myConnected()
    {
        serverSocket::serverClient = socket;
        qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
        disconnect(socket,&QTcpSocket::connected,this,&findByPing::myConnected);
        exit(0);
    }

private:
    QString currIp;
    QTcpSocket* socket;
};

#endif // SERVERCONNECTION_H
