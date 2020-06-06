#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "server/serversocket.h"
#include <QDebug>
#include "data/allaction.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"
#include "widget/serverConnection/serverconnection.h"

LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
    myParent = parent;

    GlobalData g;
    ui->txtUserName->setText(XmlManipulation::getData(g.getTagName(g.clientName),g.getattribute(g.clientName)));
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

void LogInWidget::setMsg(QString msg)
{
    ui->ErrorMessage->setText(msg);
}

void LogInWidget::on_btnLogin_clicked()
{
    QString username = ui->txtUserName->text();

    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.clientName),g.getattribute(g.clientName),username);

    serverConnection::deleteAllThread();
    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::getTotaltableNo;

//    GlobalData g;
    QString user = ui->txtUserName->text();//XmlManipulation::getData(g.getTagName(g.clientName),g.getattribute(g.clientName));
    QString pass = ui->txtPass->text();//XmlManipulation::getData(g.getTagName(g.clientPass),g.getattribute(g.clientPass));
    out << i << user << pass ;
    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
    //sending req for total table count
    serverSocket::serverClient->write(data);

//    QByteArray data1 ;
//    QDataStream out1(&data1,QIODevice::ReadWrite);
//    i = ALLAction::menuData;
//    out1 << i ;
//    qDebug() << "DynerAndroid (dinningTableList) : data to send : " << data1 ;
//    //sending req for total table count
//    serverSocket::serverClient->write(data1);
}
