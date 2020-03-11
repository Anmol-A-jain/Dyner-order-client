#include <QDebug>
#include <QKeyEvent>
#include "dynerandroid.h"
#include "ui_dynerandroid.h"
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "widget/tableList/tablelist.h"
#include "widget/Cart/cart.h"
#include "widget/CloseWindow/closewindow.h"

DynerAndroid::DynerAndroid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynerAndroid)
{
    ui->setupUi(this);

    tbl = 0;
    logWindow = newWindow(widgetWindow::serverConnectionWindow);
    childFrame = logWindow;
    ui->windowContainer->addWidget(childFrame);

    ui->btnHome->hide();
    ui->pushButton->hide();
}

DynerAndroid::~DynerAndroid()
{
    delete ui;
}

QWidget* DynerAndroid::newWindow(int option,int tblNo)
{
    switch (option)
    {
        case serverConnectionWindow :
        {
            ui->btnHome->hide();
            ui->pushButton->hide();
            logWindow = new serverConnection(this);
            return logWindow;
            break;
        }
        case cartWindow:
        {
            ui->btnHome->show();
            ui->pushButton->show();
            if(tblNo != 0)
            {
                cart = new Cart(tblNo,this);
                return cart;
            }
            break;
        }

        case tableListWindow :
        {
            ui->btnHome->show();
            ui->pushButton->show();
            if(tbl != 0)
            {
                tableButtons = new tableList(tbl,this);
                return tableButtons;
            }
            break;
        }
        case closeWindowWidget :
        {
            ui->btnHome->hide();
            ui->pushButton->hide();
            return new CloseWindow(this);
            break;
        }
    }
    return childFrame;
}

void DynerAndroid::dinningTableList(int tbl)
{
    this->tbl = tbl;
    delete childFrame;
    //childFrame->deleteLater();
    tableButtons = newWindow(widgetWindow::tableListWindow);
    childFrame = tableButtons;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::cartWidgetWindow(int tblNo)
{
    delete childFrame;
    //childFrame->deleteLater();
    cart = newWindow(widgetWindow::cartWindow,tblNo);
    childFrame = cart;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::logInWidget()
{
    delete childFrame;
    //childFrame->deleteLater();
    logWindow = newWindow(widgetWindow::serverConnectionWindow);
    childFrame = logWindow ;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::closeWidget()
{
    delete childFrame;
    //childFrame->deleteLater();
    closeWindow = newWindow(widgetWindow::closeWindowWidget);
    childFrame = closeWindow ;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::setTitle(QString title)
{
    ui->widgetTitle->setText(title);
}

void DynerAndroid::on_btnHome_clicked()
{
    if(childFrame != tableButtons)
    {
        this->dinningTableList(tbl);
    }
}

// overriding back button functioning
void DynerAndroid::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Back )
    {
        qDebug() << "DynerAndroid (keyPressEvent) : back_Button pressed";
        if(childFrame == cart)
        {
            this->dinningTableList(this->tbl);
            return;
        }
        return;
    }
    event->accept();
}
