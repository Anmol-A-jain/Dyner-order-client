#include "closewindow.h"
#include "ui_closewindow.h"
#include <QApplication>

CloseWindow::CloseWindow(QLabel *lblTitle,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloseWindow)
{
    ui->setupUi(this);

    QString title = "Disconnected";
    lblTitle->setText(title);
}

CloseWindow::~CloseWindow()
{
    delete ui;
}

void CloseWindow::on_btnQuit_clicked()
{
    qApp->quit();
}
