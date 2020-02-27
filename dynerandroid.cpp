#include "dynerandroid.h"
#include "ui_dynerandroid.h"
#include "widget/serverConnection/serverconnection.h"
#include <QDebug>
#include "data/allaction.h"

DynerAndroid::DynerAndroid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynerAndroid)
{
    ui->setupUi(this);

    childFrame = new serverConnection(this);
    ui->windowContainer->addWidget(childFrame);
}

DynerAndroid::~DynerAndroid()
{
    delete ui;
}

void DynerAndroid::hideConnectionWdget()
{
    serverSocket::serverClient->write(QString::number(ALLAction::getTotaltableNo).toUtf8());
    childFrame->hide();
}
