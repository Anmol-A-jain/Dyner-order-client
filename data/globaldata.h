#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

// creating a structure to store menu data in it
struct menuData
{
    QString id,name,category;
    double price;
};

class GlobalData
{
public:
    GlobalData();

    //shadow effect function
    static void setShadow(QWidget* widget);

    //menu data Functions
    static void setMendsduItem(QString id,QString name,QString category,double price);
    //vector to store menu in dynamic array
    static QVector<menuData*> menuDataList;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
