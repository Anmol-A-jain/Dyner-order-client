#include "serverconnection.h"
#include "dynerandroid.h"
#include "ui_serverconnection.h"
#include <QDebug>

serverConnection::serverConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverConnection)
{
    ui->setupUi(this);
    ui->btnLogin->hide();
    myParent = parent;

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
}

serverConnection::~serverConnection()
{
    delete ui;
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
    serverSocket* s = new serverSocket(myParent);
    s->connectToSerever(ui->txtIp->text());

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
    if(state == QTcpSocket::ConnectedState)
    {
        static_cast<DynerAndroid*>(myParent)->hideConnectionWdget();
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

    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.ipAddress),g.getattribute(g.ipAddress),"");

    for(int i = 0; i <= 255; i++)
    {
         QString currIp = (baseNetowrk + "%1").arg(i);

         findByPing* f = new findByPing(currIp);

         f->start();
    }
    ui->btnLogin->show();
    ui->btnauto->hide();
}

void serverConnection::on_btnLogin_clicked()
{
    GlobalData g;
    QString ip = XmlManipulation::getData(g.getTagName(g.ipAddress),g.getattribute(g.ipAddress));

    if(ip != "")
    {
        serverSocket* s = new serverSocket(myParent);
        s->connectToSerever(ip);
        qDebug() << "serverConnection (on_btnLogin_clicked) : ip address : " << ip;
        return;
    }

    ui->lblStatus->setText("Server not found");
    ui->btnLogin->hide();
    ui->btnauto->show();
}
