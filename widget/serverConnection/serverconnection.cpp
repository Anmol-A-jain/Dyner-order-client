#include "serverconnection.h"
#include "dynerandroid.h"
#include "ui_serverconnection.h"
#include <QDebug>
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include <QMessageBox>

QVector<findByPing*> serverConnection::threadList;

serverConnection::serverConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverConnection)
{
    ui->setupUi(this);
    myParent = parent;

    QString title = "Log In";
    static_cast<DynerAndroid*>(myParent)->setTitle(title);

    GlobalData g;
    ui->txtUserName->setText(XmlManipulation::getData(g.getTagName(g.clientName),g.getattribute(g.clientName)));

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

void serverConnection::deleteAllThread()
{
    for(int i = 0; i < threadList.size(); ++i)
    {
        threadList[i]->disconnectAndExit();
    }
    qDebug() << "serverConnection (deleteAllThread) : deleted thread all thread =";
}

void serverConnection::on_btnConnect_clicked()
{
    QString username = ui->txtUserName->text();
    QString pass = ui->txtPass->text();
    if(username.isEmpty() || pass.isEmpty())
    {
        QMessageBox::warning(this,"Empty!","Please fill all fields");
        return;
    }
    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.clientName),g.getattribute(g.clientName),username);
    XmlManipulation::setData(g.getTagName(g.clientPass),g.getattribute(g.clientPass),pass);
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
    QString username = ui->txtUserName->text();
    QString pass = ui->txtPass->text();
    if(username.isEmpty() || pass.isEmpty())
    {
        QMessageBox::warning(this,"Empty!","Please fill all fields");
        return;
    }
    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.clientName),g.getattribute(g.clientName),username);
    XmlManipulation::setData(g.getTagName(g.clientPass),g.getattribute(g.clientPass),pass);


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
        f->start();
        serverConnection::threadList.push_back(f);
        connect(f,SIGNAL(connectToServer(QString)),this,SLOT(connectToServer(QString)));
    }
    ui->btnauto->hide();
    ui->btnConnect->hide();
    ui->label_2->hide();
}


