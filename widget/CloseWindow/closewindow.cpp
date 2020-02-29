#include "closewindow.h"
#include "ui_closewindow.h"
#include <QApplication>
#include <QProcess>

CloseWindow::CloseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloseWindow)
{
    ui->setupUi(this);
}

CloseWindow::~CloseWindow()
{
    delete ui;
}

void CloseWindow::on_btnQuit_clicked()
{
    qApp->quit();
}
