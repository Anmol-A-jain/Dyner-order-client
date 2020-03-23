#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QWidget>
#include <QTcpSocket>
#include <QThread>
#include <QProcess>
#include <QHostInfo>
#include <QComboBox>
#include "server/serversocket.h"
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
    static void deleteAllThread();

private slots:
    void on_btnConnect_clicked();

    void stateChanged(QAbstractSocket::SocketState state);

    void on_btnauto_clicked();

    void connectToServer(QString ip);

private:
    Ui::serverConnection *ui;
    QWidget* myParent;
    QString baseIp;

    static QVector<findByPing*> threadList;
};


class findByPing : public QThread
{
    Q_OBJECT
public:
    findByPing(QString ipAddress,serverConnection* parent = nullptr)
    {
        myParent = parent;
        this->currIp = ipAddress;
        isActive = false;
    }

    void run()
    {
        socket = new QTcpSocket();
        connect(socket,&QTcpSocket::connected,this,&findByPing::myConnected);
        socket->connectToHost(this->currIp,1812);

        exec();
    }

    void disconnectAndExit()
    {
        if(socket->state() == QTcpSocket::ConnectedState)
        {
            socket->disconnectFromHost();
            exit(0);
        }
        exit(0);
    }

public slots :

    void myConnected()
    {
        emit connectToServer(currIp);
        qDebug() << "findByPing (myConnected) : state : " << socket->state() ;
    }

signals:
    void connectToServer(QString currIp);

private:
    QString currIp;
    QTcpSocket* socket;
    bool isActive;
    serverConnection* myParent;
};

#endif // SERVERCONNECTION_H
