#include "dynerandroid.h"
#include "ui_dynerandroid.h"
#include "widget/serverConnection/serverconnection.h"
#include <QDebug>
#include "data/allaction.h"
#include "widget/tableList/tablelist.h"
#include "widget/Cart/cart.h"

DynerAndroid::DynerAndroid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynerAndroid)
{
    ui->setupUi(this);

    logWindow = new serverConnection(this);
    childFrame = logWindow;
    ui->windowContainer->addWidget(childFrame);
    ui->btnHome->hide();
}

DynerAndroid::~DynerAndroid()
{
    delete ui;
}

void DynerAndroid::hideConnectionWdget()
{
    QByteArray action = QString::number(ALLAction::getTotaltableNo).toUtf8();
    QByteArray data = serverSocket::setAction(ALLAction::getTotaltableNo,"");
    //sending req for total table count
    serverSocket::serverClient->write(data);
    logWindow->hide();
}

void DynerAndroid::showConnectionWdget()
{
    ui->btnHome->hide();
    ui->widgetTitle->setText("Login");
    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.ipAddress),g.getattribute(g.ipAddress),"");
    logWindow = new serverConnection(this);
    childFrame = logWindow;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::loadTable(int tbl)
{
    this->tbl = tbl;
//    tableButtons = new tableList(tbl,this);
//    childFrame = tableButtons;
//    ui->windowContainer->addWidget(childFrame);
    this->loadTable();
}

void DynerAndroid::loadTable()
{
    ui->btnHome->show();
    ui->widgetTitle->setText("Home");
    tableButtons = new tableList(tbl,this);
    childFrame = tableButtons;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::loadCart(int tbl)
{
    ui->widgetTitle->setText("Cart: Table " + QString::number(tbl));
    tableButtons->deleteLater();
    cart = new  Cart(tbl,this);
    childFrame = cart;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::on_btnHome_clicked()
{
    if(childFrame != tableButtons)
    {
        this->loadTable();
    }
}
