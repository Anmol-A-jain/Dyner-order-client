#include "dynerandroid.h"
#include "ui_dynerandroid.h"
#include "widget/serverConnection/serverconnection.h"
#include <QDebug>
#include "data/allaction.h"
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
            return new serverConnection(this);
            break;
        }
        case cartWindow:
        {
            ui->btnHome->show();
            if(tblNo != 0) return new Cart(tblNo,this);
            break;
        }

        case tableListWindow :
        {
            ui->btnHome->show();
            if(tbl != 0) return new tableList(tbl,this);
            break;
        }
        case closeWindowWidget :
        {
            ui->btnHome->hide();
            return new CloseWindow();
            break;
        }
    }
    return childFrame;
}

void DynerAndroid::dinningTableList(int tbl)
{
    this->tbl = tbl;
    childFrame->deleteLater();
    tableButtons = newWindow(widgetWindow::tableListWindow);
    childFrame = tableButtons;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::cartWidgetWindow(int tblNo)
{
    childFrame->deleteLater();
    cart = newWindow(widgetWindow::cartWindow,tblNo);
    childFrame = cart;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::logInWidget()
{
    childFrame->deleteLater();
    logWindow = newWindow(widgetWindow::serverConnectionWindow);
    childFrame = logWindow ;
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::closeWidget()
{
    childFrame->deleteLater();
    childFrame = newWindow(widgetWindow::closeWindowWidget);
    ui->windowContainer->addWidget(childFrame);
}

void DynerAndroid::on_btnHome_clicked()
{
    if(childFrame != tableButtons)
    {
        this->dinningTableList(tbl);
    }
}
