#include "dynerandroid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/img/logo.png"));
    DynerAndroid w;
    w.show();
    return a.exec();
}
