#include "addorderitem.h"
#include "ui_addorderitem.h"
#include "data/globaldata.h"
#include <QDebug>
#include <QScrollBar>
#include <QScroller>
#include "dynerandroid.h"

AddOrderItem::AddOrderItem(int tblNo,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOrderItem)
{
    ui->setupUi(this);
    myParent = parent;

    this->tblNo = tblNo;

    QScrollArea *scrollArea = ui->scrollArea;
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:10px;}");
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);

    QString title = "Menu List : table " + QString::number(tblNo);
    static_cast<DynerAndroid*>(myParent)->setTitle(title);

    ui->categoryList->hide();
    this->loadData();
}

AddOrderItem::~AddOrderItem()
{
    delete ui;
}

void AddOrderItem::loadData()
{

    this->deleteVecterData();
    /*databaseCon d;
    QString cmd = "select * from mstTblMenu order by id" ;
    QSqlQuery* q = d.execute(cmd);
    */
    QVector<menuData*> q = GlobalData::menuDataList;

    for( int i = 0 ; q.count() > i ;++i )
    {

        QString id = q[i]->id; //q->value("id").toString();
        QString itemName = q[i]->name; //q->value("itemName").toString();
        QString category = q[i]->category; //q->value("category").toString();
        QString price = QString::number(q[i]->price); //q->value("Price").toString();

        qDebug() << "AddOrderItem.cpp (loadData) : id " << q[i]->id; //q->value("id").toString();
        OrderItemData *item = new OrderItemData(id,itemName,category,price,myParent);
        itemlist.push_back(item);
        ui->displayAddOrder->addWidget(item);

    }
}

void AddOrderItem::deleteVecterData()
{
    for (int i = 0; i < itemlist.count(); ++i)
    {
        delete itemlist[i];
    }
    itemlist.clear();
}

void AddOrderItem::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    ui->categoryList->setSizePolicy(ui->SearchTextBox->sizePolicy());
}

void AddOrderItem::updateCategorylist()
{
    ui->categoryList->clear();

    /*databaseCon d;
    QString cmd = "SELECT category FROM tblCategoryList ORDER BY category" ;
    QSqlQuery* q = d.execute(cmd);
    */

    QVector<menuData*> q = GlobalData::menuDataList;
    for (int i = 0; i < q.count(); ++i) {

        qDebug() << "AdminWidget.cpp (loadComboBoxData) : combo box :" << q[i]->category; //q->value("category").toString();
        //ui->categoryList->addItem(q->value("category").toString());
        ui->categoryList->addItem(q[i]->category);
    }
}

void AddOrderItem::on_menuColumn_currentIndexChanged(int index)
{
    if(index == 3 )
    {
        ui->categoryList->show();
        ui->SearchTextBox->hide();
        this->updateCategorylist();
    }
    else
    {
        ui->categoryList->hide();
        ui->SearchTextBox->show();
    }
}

void AddOrderItem::on_btnSearch_clicked()
{
    /*
    QString columnName;
    QString cmd;
    QString searchText = ui->SearchTextBox->text();
    bool isPrice = false, isName = false, isCategory = false, isAll = false;

    if(!ui->SearchTextBox->text().isEmpty() || !ui->categoryList->isHidden() )
    {
        if(ui->menuColumn->currentText() == ui->menuColumn->itemText(0))
        {
            isAll = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(1))
        {
            columnName = "id";
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(2))
        {
            columnName = "itemName";
            isName = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(3))
        {
            columnName = "category";
            isCategory = true;
        }
        else if(ui->menuColumn->currentText() == ui->menuColumn->itemText(4))
        {
            columnName = "Price";
            isPrice = true;
        }

        if(isPrice)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" = "+ searchText +" ORDER BY id" ;
        }
        else if(isName)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" LIKE '%"+ searchText +"%' ORDER BY id" ;
        }
        else if(isAll)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE id = '"+searchText+"' OR itemName LIKE '%"+ searchText +"%' OR category LIKE '%"+ searchText +"%' OR Price = '"+ searchText +"' ORDER BY id" ;
        }
        else if(isCategory)
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" = '"+ ui->categoryList->currentText() +"' ORDER BY id" ;
        }
        else
        {
            cmd = "SELECT * FROM mstTblMenu WHERE "+ columnName +" LIKE '%"+ ui->SearchTextBox->text() +"%' ORDER BY id" ;
        }
    }
    else
    {
        cmd = "SELECT * FROM mstTblMenu ORDER BY id";
    }

    this->deleteVecterData();
    databaseCon d;
    qDebug() << "AddOrderItem.cpp (on_btnSearch_clicked) : constr " << cmd ;
    QSqlQuery* q = d.execute(cmd);

    while( q->next() )
    {
        qDebug() << "AddOrderItem.cpp (on_btnSearch_clicked) : id " << q->value("id").toString() ;
        OrderItemData *item = new OrderItemData(q->value("id").toString(),q->value("itemName").toString(),q->value("category").toString(),q->value("Price").toString(),myParent);
        itemlist.push_back(item);
        ui->displayAddOrder->addWidget(item);
    }
    delete q;
    */
}

void AddOrderItem::on_SearchTextBox_returnPressed()
{

    qDebug() << "AddOrderItem.cpp (on_SearchTextBox_returnPressed) : current text " << ui->SearchTextBox->text() ;
    emit on_btnSearch_clicked();
}

void AddOrderItem::on_SearchTextBox_textChanged(const QString &arg1)
{
    qDebug() << "AddOrderItem.cpp (on_SearchTextBox_textChanged) : argument " << arg1 ;
    emit on_btnSearch_clicked();
}

void AddOrderItem::on_categoryList_currentIndexChanged(int index)
{
    qDebug() << "AddOrderItem.cpp (on_categoryList_currentIndexChanged) : argument " << index ;
    emit on_btnSearch_clicked();
}


void AddOrderItem::on_btnsubmit_clicked()
{
    static_cast<DynerAndroid*>(myParent)->cartWidgetWindow(this->tblNo);
}
