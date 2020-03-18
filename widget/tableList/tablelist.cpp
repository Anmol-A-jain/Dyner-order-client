#include "tablelist.h"
#include "ui_tablelist.h"
#include "TableCustomButtons/tablecustombuttons.h"
#include <QPushButton>
#include <QtMath>
#include <QDebug>
#include <QLayout>
#include <QScroller>
#include <QScrollBar>
#include <QAbstractItemView>
#include "data/globaldata.h"
#include "dynerandroid.h"

tableList::tableList(int tbl,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableList)
{
    ui->setupUi(this);
    myParent = parent;
    this->tbl = tbl;
    this->column = 2;
    QScrollArea *scrollArea = ui->scrollArea;
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:10px;}");
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);
    setButton();

    GlobalData::setShadow(this);
    QString title = "Table List";
    static_cast<DynerAndroid*>(myParent)->setTitle(title);

    QVector<orderData*>* q = &GlobalData::CartItem;

    q->clear();
}

tableList::~tableList()
{
    delete ui;
}

void tableList::setButton()
{

    row = tbl/column;
    row = (tbl%column > 0) ? (row + 1) : row ;

    QGridLayout* layout = ui->btnList;

    qDebug() << "tableList (setButton) : row%column " << (double) (row%column) ;
    qDebug() << "tableList (setButton) : row " << row ;
    qDebug() << "tableList (setButton) : table " << tbl ;

    for (int i = 0,count = 1; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            if(count <= tbl)
            {
                TableCustomButtons* btn = new TableCustomButtons(count,"Table " + QString::number(count),myParent);
                qDebug() << "tableList (setButton) : btn name " << btn->getText() ;
                count++;
                layout->addWidget(btn,i,j);
            }
        }
    }
}
