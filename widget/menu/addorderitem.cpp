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

    GlobalData::setShadow(ui->btnsubmit,QColor(52, 149, 254),0,10);
    GlobalData::setShadow(ui->btnSearch);
}

AddOrderItem::~AddOrderItem()
{
    delete ui;
}

void AddOrderItem::loadData()
{

    this->deleteVecterData();
    QVector<menuData*> q = GlobalData::menuDataList;

    for( int i = 0 ; q.count() > i ;++i )
    {
        qDebug() << "AddOrderItem.cpp (loadData) : id " << q[i]->id; //q->value("id").toString();
        OrderItemData *item = new OrderItemData(q[i],0,"",myParent);
        itemlist.push_back(item);
        ui->displayAddOrder->addWidget(item);
    }
}

void AddOrderItem::deleteVecterData()
{
    for (int i = 0; i < itemlist.count(); ++i)
    {
        itemlist[i]->deleteLater();
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

    for (int i = 0; i < q.count(); ++i)
    {

        int result = ui->categoryList->findText(q[i]->category);

        if(result != -1) continue;

        qDebug() << "AdminWidget.cpp (loadComboBoxData) : combo box :" << q[i]->category; //q->value("category").toString();
        //ui->categoryList->addItem(q->value("category").toString());
        ui->categoryList->addItem(q[i]->category);
    }
}

bool AddOrderItem::isContains(QString text, QString subText)
{
    return text.indexOf(subText, 0, Qt::CaseInsensitive) != -1;
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

    QString searchText = ui->SearchTextBox->text();

    enum menu{all,id,name,category,price};

    if(!ui->SearchTextBox->text().isEmpty() || !ui->categoryList->isHidden() )
    {

        switch (ui->menuColumn->currentIndex())
        {
            case all:
            {
                QString itemId,itemName,itemCategory,itemPrice;
                for (int i = 0; i < itemlist.count(); ++i)
                {
                    itemId = itemlist.at(i)->getId();
                    itemName = itemlist.at(i)->getName();
                    itemCategory = itemlist.at(i)->getCategory();
                    itemPrice = itemlist.at(i)->getPrice();

                    if(isContains(itemId,searchText) || isContains(itemName,searchText) || isContains(itemCategory,searchText) || isContains(itemPrice,searchText) )
                    {
                        itemlist.at(i)->show();
                    }
                    else
                    {
                        itemlist.at(i)->hide();
                    }
                }
                break;
            }
            case id:
            {
                QString itemId,itemName,itemCategory,itemPrice;
                for (int i = 0; i < itemlist.count(); ++i)
                {
                    itemId = itemlist.at(i)->getId();
                    itemName = itemlist.at(i)->getName();
                    itemCategory = itemlist.at(i)->getCategory();
                    itemPrice = itemlist.at(i)->getPrice();

                    if(isContains(itemId,searchText))
                    {
                        itemlist.at(i)->show();
                    }
                    else
                    {
                        itemlist.at(i)->hide();
                    }
                }
                break;
            }
            case name:
            {
                QString itemId,itemName,itemCategory,itemPrice;
                for (int i = 0; i < itemlist.count(); ++i)
                {
                    itemId = itemlist.at(i)->getId();
                    itemName = itemlist.at(i)->getName();
                    itemCategory = itemlist.at(i)->getCategory();
                    itemPrice = itemlist.at(i)->getPrice();

                    if(isContains(itemName,searchText))
                    {
                        itemlist.at(i)->show();
                    }
                    else
                    {
                        itemlist.at(i)->hide();
                    }
                }

                break;
            }
            case category:
            {
                QString itemId,itemName,itemCategory,itemPrice;
                for (int i = 0; i < itemlist.count(); ++i)
                {
                    itemId = itemlist.at(i)->getId();
                    itemName = itemlist.at(i)->getName();
                    itemCategory = itemlist.at(i)->getCategory();
                    itemPrice = itemlist.at(i)->getPrice();

                    if(isContains(itemCategory,ui->categoryList->currentText()))
                    {
                        itemlist.at(i)->show();
                    }
                    else
                    {
                        itemlist.at(i)->hide();
                    }
                }
                break;
            }
            case price:
            {
                QString itemId,itemName,itemCategory,itemPrice;
                for (int i = 0; i < itemlist.count(); ++i)
                {
                    itemId = itemlist.at(i)->getId();
                    itemName = itemlist.at(i)->getName();
                    itemCategory = itemlist.at(i)->getCategory();
                    itemPrice = itemlist.at(i)->getPrice();

                    if(isContains(itemPrice,searchText))
                    {
                        itemlist.at(i)->show();
                    }
                    else
                    {
                        itemlist.at(i)->hide();
                    }
                }

                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < itemlist.count(); ++i)
        {
            itemlist.at(i)->show();
        }
    }
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
