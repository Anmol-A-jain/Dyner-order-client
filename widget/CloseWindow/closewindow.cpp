#include "closewindow.h"
#include "ui_closewindow.h"
#include "dynerandroid.h"
#include <QApplication>

CloseWindow::CloseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloseWindow)
{
    ui->setupUi(this);

    QString title = "Disconnected";
    static_cast<DynerAndroid*>(myParent)->setTitle(title);
}

CloseWindow::~CloseWindow()
{
    delete ui;
}

void CloseWindow::on_btnQuit_clicked()
{
    qApp->quit();
}
