#include "tablecustombuttons.h"
#include "ui_tablecustombuttons.h"
#include "dynerandroid.h"
#include "data/globaldata.h"

TableCustomButtons::TableCustomButtons(int tbl,QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableCustomButtons)
{
    ui->setupUi(this);
    myParent = parent;
    ui->btnTable->setText(name);
    this->tbl = tbl;

    GlobalData::setShadow(this,QColor(240,230,140));
}

TableCustomButtons::~TableCustomButtons()
{
    delete ui;
}

QString TableCustomButtons::getText()
{
    return ui->btnTable->text();
}

void TableCustomButtons::on_btnTable_clicked()
{
    //static_cast<DynerAndroid*>(myParent)->cartWidgetWindow(tbl);
    static_cast<DynerAndroid*>(myParent)->menuWidget(this->tbl);
}
