#include "dynerandroid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DynerAndroid w;
    w.showFullScreen();
    return a.exec();
}
