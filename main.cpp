#include "dynerandroid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DynerAndroid w;
    w.show();
    return a.exec();
}
