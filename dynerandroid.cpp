#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QtAndroidExtras>
#include "dynerandroid.h"
#include "ui_dynerandroid.h"
#include "widget/serverConnection/serverconnection.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include "widget/tableList/tablelist.h"
#include "widget/Cart/cart.h"
#include "widget/menu/addorderitem.h"
#include "widget/CloseWindow/closewindow.h"
#include "widget/login/loginwidget.h"

DynerAndroid::DynerAndroid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynerAndroid)
{
    ui->setupUi(this);

    tbl = 0;
    serverConnectionWidget = newWindow(widgetWindow::serverConnectionWindow);
    childFrame = serverConnectionWidget;
    ui->windowContainer->addWidget(childFrame);

    ui->btnHome->hide();
    ui->lblCurrentId->hide();

    GlobalData::deleteCartVectordata();

    this->isExiting = false;
}

DynerAndroid::~DynerAndroid()
{
    delete ui;
}

QWidget* DynerAndroid::newWindow(int option,int tblNo)
{
    switch (option)
    {
        case loginWindowWidget:
        {
            ui->btnHome->hide();
            ui->lblCurrentId->hide();
            loginWindow = new LogInWidget(this);
            return loginWindow;
            break;
        }
        case serverConnectionWindow :
        {
            ui->btnHome->hide();
            ui->lblCurrentId->hide();
            serverConnectionWidget = new serverConnection(this);
            return serverConnectionWidget;
            break;
        }
        case cartWindow:
        {
            ui->btnHome->show();
            ui->lblCurrentId->show();
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
            ui->lblCurrentId->show();
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
            ui->lblCurrentId->hide();
            return new CloseWindow(ui->widgetTitle);
            break;
        }
        case menuListWidget :
        {
            ui->btnHome->show();
            ui->lblCurrentId->show();
            this->currentTbl = tblNo;
            return new AddOrderItem(tblNo,this);
            break;
        }
    }
    return childFrame;
}

void DynerAndroid::dinningTableList(int tbl)
{
    if(tbl != 0)
    {
        this->tbl = tbl;
    }
    tableButtons = newWindow(tableListWindow);
    setWidget(tableButtons);
}

void DynerAndroid::cartWidgetWindow(int tblNo)
{
    cart = newWindow(cartWindow,tblNo);
    setWidget(cart);
}

void DynerAndroid::sreverConnectionWidget()
{
    serverConnectionWidget = newWindow(serverConnectionWindow);
    setWidget(serverConnectionWidget);
}

void DynerAndroid::menuWidget(int tblNo)
{
    menuList = newWindow(menuListWidget,tblNo);
    setWidget(menuList);
}

void DynerAndroid::loginWidget()
{
    loginWindow = newWindow(loginWindowWidget);
    setWidget(loginWindow);
}

void DynerAndroid::closeWidget()
{
    QMessageBox::StandardButton reply = QMessageBox::critical(this,"Diconnected","Server has been disconnected,\n App will exit",QMessageBox::Ok);
    if(reply == QMessageBox::Ok)
        qApp->exit(0);

    /*
    //delete childFrame;
    QWidget* temp = childFrame;
    //childFrame->deleteLater();
    closeWindow = newWindow(widgetWindow::closeWindowWidget);
    childFrame = closeWindow ;
    ui->windowContainer->addWidget(childFrame);
    delete temp;
    */
}

void DynerAndroid::setWidget(QWidget *child)
{
    QWidget* temp = childFrame;
    temp->hide();
    //childFrame->deleteLater();
    childFrame = child ;
    ui->windowContainer->addWidget(childFrame);
    temp->hide();
}

void DynerAndroid::setTitle(QString title)
{
    ui->widgetTitle->setText(title);
}

void DynerAndroid::setCurrentId(QString id)
{
    ui->lblCurrentId->setText("Id: " + id);
}

void DynerAndroid::ChangeBoolvalue(bool value)
{
    isExiting = value;
}

void DynerAndroid::callCartObject(QString name,QString mblNo)
{
    if(cart == childFrame)
    {
        static_cast<Cart*>(cart)->customerData(name,mblNo);
    }
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
    qDebug() << "DynerAndroid (keyPressEvent) : pressed" << event->key();

    if(event->key() == Qt::Key_Back )
    {
        qDebug() << "DynerAndroid (keyPressEvent) : back_Button pressed";
        if(childFrame == menuList)
        {
            this->dinningTableList(this->tbl);
            return;
        }
        if(childFrame == cart)
        {
            this->menuWidget(this->currentTbl);
            return;
        }
        if(childFrame == tableButtons || childFrame == serverConnectionWidget || childFrame == loginWindow)
        {
            if(isExiting)
            {
                qDebug() << "DynerAndroid (keyPressEvent) : isExiting" << isExiting;
                qApp->exit(0);
            }
            QString message = "Press again to Exit";
            int duration =2000;
            QtAndroid::runOnAndroidThread([message, duration ] {
                QAndroidJniObject javaString = QAndroidJniObject::fromString(message);
                QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                                    "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                                    QtAndroid::androidActivity().object(),
                                                                                    javaString.object(),
                                                                                    jint(duration));
                toast.callMethod<void>("show");
            });
            ChangeBoolvalue(true);

            class ExitThread : public QThread
            {

                public:
                    DynerAndroid* myParent;
                    void run()
                    {
                        sleep(2);
                        myParent->ChangeBoolvalue(false);
                    }
                    ExitThread(DynerAndroid *parent)
                    {
                        myParent = parent;
                    }
            };
            (new ExitThread(this))->start();
        }
        return;
    }

    event->accept();
}

QWidget *DynerAndroid::getLoginWidget()
{
    if(childFrame == loginWindow)
    {
        return loginWindow;
    }
    return nullptr;
}
