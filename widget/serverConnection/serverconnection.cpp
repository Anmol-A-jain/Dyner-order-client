#include "serverconnection.h"
#include "dynerandroid.h"
#include "ui_serverconnection.h"
#include <QDebug>
#include "data/globaldata.h"

serverConnection::serverConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverConnection)
{
    ui->setupUi(this);
    myParent = parent;

    QString title = "Log In";
    static_cast<DynerAndroid*>(myParent)->setTitle(title);

    connect(serverSocket::serverClient,&QTcpSocket::stateChanged,this,&serverConnection::stateChanged);

    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            baseIp = address.toString();

            while(baseIp.right(1) != "." )
            {
                baseIp = baseIp.left(baseIp.length()-1);
            }
            ui->txtIp->setText(baseIp);
        }
    }
    GlobalData::setShadow(ui->icon);

}

serverConnection::~serverConnection()
{
    delete ui;
}

void serverConnection::connectToServer(QString ip)
{
    serverSocket* s = new serverSocket(myParent);
    s->connectToSerever(ip);
}

void serverConnection::on_btnConnect_clicked()
{
    qDebug() << "serverConnection (on_btnConnect_clicked) : state : " << serverSocket::serverClient->state() ;

    if(ui->txtIp->text() == "")
        return;
    if(serverSocket::serverClient->state() == QTcpSocket::ConnectedState)
    {
        ui->lblStatus->setText("Connected");
        return;
    }
    this->connectToServer(ui->txtIp->text());

    if(serverSocket::serverClient->state() != QTcpSocket::ConnectingState || serverSocket::serverClient->state() != QTcpSocket::ConnectedState)
    {
        ui->lblStatus->setText("not Connected");
    }
}

void serverConnection::stateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "serverConnection (stateChanged) : state : " << serverSocket::serverClient->state() ;
    if(state == QTcpSocket::UnconnectedState)
    {
        ui->lblStatus->setText("Try again");
    }
    if(state == QTcpSocket::ConnectingState)
    {
        ui->lblStatus->setText("Connecting...");
    }
}

void serverConnection::on_btnauto_clicked()
{
    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            baseIp = address.toString();

            while(baseIp.right(1) != "." )
            {
                baseIp = baseIp.left(baseIp.length()-1);
            }
            ui->txtIp->setText(baseIp);
        }
    }

    QString baseNetowrk = baseIp;

    for(int i = 0; i <= 255; i++)
    {
        QString currIp = (baseNetowrk + "%1").arg(i);

        findByPing* f = new findByPing(currIp,this);
        connect(f, SIGNAL(finished()), f, SLOT(deleteLater()));
        f->start();
    }
}


