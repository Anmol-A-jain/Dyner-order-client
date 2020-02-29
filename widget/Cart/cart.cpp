#include "cart.h"
#include "ui_cart.h"

Cart::Cart(int tbl,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    this->tbl = tbl;
    myParent = parent;
    ui->label->setText(QString::number(tbl));
}

Cart::~Cart()
{
    delete ui;
}
