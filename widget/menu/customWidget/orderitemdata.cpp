#include "orderitemdata.h"
#include "ui_orderitemdata.h"
#include <QDebug>
#include <QMessageBox>

OrderItemData::OrderItemData(menuData* item,double qty,QString note, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItemData)
{
    ui->setupUi(this);
    myparent = parent;
    this->item = item;

    ui->txtNote->hide();

    //set data if data came from cart.cpp
    if(qty > 0.0 )
    {
        ui->txtNote->show();
        ui->txtQty->setValue(qty);
        ui->txtNote->setText(note);
    }


    //set data if data came from addOrderItem.cpp
    QVector<orderData*>* q = &GlobalData::CartItem;

    if(qty == 0.0)
    {
        for (int i = 0; i < q->count(); ++i)
        {
           if(q->at(i)->item->id == item->id)
           {
                ui->txtNote->show();
                ui->txtQty->setValue(q->at(i)->qty);
                ui->txtNote->setText(q->at(i)->note);
           }
        }
    }

    ui->lblId->setText(item->id);
    ui->lblName->setText(item->name);
    ui->lblCategory->setText(item->category);
    ui->lblRate->setText("Rs."+QString::number(item->price));

    ui->txtQty->setButtonSymbols(QAbstractSpinBox::NoButtons);
    GlobalData::setShadow(this,QColor(0, 0, 0),0,10);
    GlobalData::setShadow(ui->btnPlus,QColor(52, 149, 254),0,10);
    GlobalData::setShadow(ui->btnMinus,QColor(255,0,0),0,10);
}

OrderItemData::~OrderItemData()
{
    delete ui;
}

QString OrderItemData::getId()
{
    return ui->lblId->text();
}

QString OrderItemData::getName()
{
    return ui->lblName->text();
}

QString OrderItemData::getCategory()
{
    return ui->lblCategory->text();
}

QString OrderItemData::getPrice()
{
    return ui->lblRate->text();
}

void OrderItemData::on_btnPlus_clicked()
{
    ui->txtNote->show();
    if(ui->txtQty->text().toDouble() == 0.0)
    {
        ui->txtQty->stepUp();

        GlobalData::setItemQty(item,ui->txtQty->text().toDouble());
        ui->txtNote->show();
        return;
    }
    ui->txtQty->stepUp();

    QVector<orderData*>* q = &GlobalData::CartItem;

    for (int i = 0; i < q->count(); ++i)
    {
        if(q->at(i)->item->id == item->id)
        {
            q->at(i)->qty = q->at(i)->qty+1;
            qDebug() << "OrderItemData (on_btnPlus_clicked) : qty " << q->at(i)->qty;
            break;
        }
    }

}

void OrderItemData::on_btnMinus_clicked()
{
    if(ui->txtQty->text().toDouble() == 1.0)
    {
        ui->txtQty->stepDown();

        QVector<orderData*>* q = &GlobalData::CartItem;

        for (int i = 0; i < q->count(); ++i)
        {
           if(q->at(i)->item->id == item->id)
           {
               qDebug() << "OrderItemData (on_btnMinus_clicked) : count befor " << q->count();
               q->remove(i);
               qDebug() << "OrderItemData (on_btnMinus_clicked) : count after " << q->count();

               ui->txtNote->clear();
               ui->txtNote->hide();
               break;
           }
        }
        return;
    }
    if(ui->txtQty->text().toDouble() == 0.0)
    {
        return;
    }

    ui->txtQty->stepDown();

    QVector<orderData*>* q = &GlobalData::CartItem;

    for (int i = 0; i < q->count(); ++i)
    {
       if(q->at(i)->item->id == item->id)
       {
           q->at(i)->qty = q->at(i)->qty-1;
           qDebug() << "OrderItemData (on_btnMinus_clicked) : qty " << q->at(i)->qty;
           break;
       }
    }
}

void OrderItemData::on_txtNote_textChanged(const QString &arg1)
{
    QVector<orderData*>* q = &GlobalData::CartItem;

    for (int i = 0; i < q->count(); ++i)
    {
       if(q->at(i)->item->id == item->id)
       {
           q->at(i)->note = arg1;
           qDebug() << "OrderItemData (on_txtNote_textChanged) : qty " << q->at(i)->note;
           break;
       }
    }
}
