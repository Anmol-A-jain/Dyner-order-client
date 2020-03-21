#include "orderitemdata.h"
#include "ui_orderitemdata.h"
#include <QDebug>
#include <QMessageBox>

OrderItemData::OrderItemData(menuData* item,double qty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItemData)
{
    ui->setupUi(this);
    myparent = parent;
    this->item = item;

    if(qty > 0.0 ) ui->txtQty->setValue(qty);

    QVector<orderData*>* q = &GlobalData::CartItem;

    for (int i = 0; i < q->count(); ++i)
    {
       if(q->at(i)->item->id == item->id)
       {
            ui->txtQty->setValue(q->at(i)->qty);
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
    if(ui->txtQty->text().toDouble() == 0.0)
    {
        ui->txtQty->stepUp();

        GlobalData::setItemQty(item,ui->txtQty->text().toDouble());

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
       }
    }
}
