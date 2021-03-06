#include "cart.h"
#include "ui_cart.h"
#include "dynerandroid.h"
#include "data/globaldata.h"
#include "../menu/customWidget/orderitemdata.h"
#include <QMessageBox>
#include "server/serversocket.h"
#include "data/allaction.h"

Cart::Cart(int tbl,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);


    qDebug() << "serverConnection (myConnected) : state : " << serverSocket::serverClient->state() ;
    qDebug() << "serverConnection (myConnected) : ip address : " << serverSocket::serverClient->peerAddress() ;
    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::getCustInfo;
    out << i << tbl;
    qDebug() << "serverConnection (myConnected) : data to send : " << data ;
    //sending req for total table count
    serverSocket::serverClient->write(data);

    r1 = new QRegExpValidator(QRegExp("[0-9]*"), ui->txtMblNo);
    r2 = new QRegExpValidator(QRegExp("[A-Za-z ]*"), ui->txtMblNo);
    ui->txtMblNo->setValidator(r1);
    ui->txtCustName->setValidator(r2);

    this->tbl = tbl;
    myParent = parent;
    QString title = "Cart : Table";
    static_cast<DynerAndroid*>(myParent)->setTitle(title +" : "+ QString::number(tbl));
    loadData();

    GlobalData::setShadow(ui->AddItem,QColor(52, 149, 254));

}

Cart::~Cart()
{
    delete ui;
}

qint16 Cart::getTblNo()
{
    return tbl;
}

void Cart::loadData()
{
    QVector<orderData*>* q = &GlobalData::CartItem;

    for (int i = 0; i < q->count(); ++i)
    {
        OrderItemData* item = new OrderItemData(q->at(i)->item,q->at(i)->qty,q->at(i)->note);
        ui->verticalLayout_3->addWidget(item);
    }
}

void Cart::customerData(QString name,QString mblNo)
{
    ui->txtMblNo->setText(mblNo);
    ui->txtCustName->setText(name);
}

void Cart::on_AddItem_clicked()
{
    //AddOrderItem aoi(this);
    if(ui->txtCustName->text().isEmpty())
    {
        QMessageBox::warning(this,"Enter Name","Please enter customer name");
        return;
    }

    if(ui->txtMblNo->text().isEmpty())
    {
        QMessageBox::warning(this,"Enter Mobile no","Please enter customer Mobile No");
        return;
    }

    if(ui->txtMblNo->text().length() < 10)
    {
        QMessageBox::warning(this,"Mobile Issue","Please enter valid Mobile No");
        return;
    }

    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::cartData;


    QVector<orderData*>* q = &GlobalData::CartItem;

    qint16 count = q->count();
    if(count < 1)
    {
        QMessageBox::information(this,"Empty","Cart Is empty");
        return;
    }
    QString mblNo = ui->txtMblNo->text() ,name = ui->txtCustName->text();

    out << i ;
    out << tbl ;
    out << count ;
    out << name << mblNo ;

    qDebug() << "Cart (on_AddItem_clicked) : cart data  : " << tbl << ":" << count ;

    for (int i = 0; i < q->count(); ++i)
    {
        QString id = q->at(i)->item->id;
        QString note = q->at(i)->note;
        double qty = q->at(i)->qty;

        qDebug() << "Cart (on_AddItem_clicked) : cart data  : " ;
        qDebug() << "Cart (on_AddItem_clicked) : id : " << id ;
        qDebug() << "Cart (on_AddItem_clicked) : qty : " <<  qty ;
        qDebug() << "Cart (on_AddItem_clicked) : note : " <<  note ;

        out << id ;
        out << note;
        out << qty ;
    }

    qDebug() << "Cart (on_AddItem_clicked) : data to send : " << data ;

    //sending req for total table count
    serverSocket::serverClient->write(data);
    serverSocket::serverClient->flush();

    q->clear();

    static_cast<DynerAndroid*>(myParent)->dinningTableList();

}
