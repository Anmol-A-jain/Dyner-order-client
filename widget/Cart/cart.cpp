#include "cart.h"
#include "ui_cart.h"
#include "dynerandroid.h"

Cart::Cart(int tbl,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    this->tbl = tbl;
    myParent = parent;
    QString title = "Table";
    static_cast<DynerAndroid*>(myParent)->setTitle(title +" : "+ QString::number(tbl));
}

Cart::~Cart()
{
    delete ui;
}
