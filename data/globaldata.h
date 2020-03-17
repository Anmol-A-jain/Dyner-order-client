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

struct orderData
{
    menuData* item;
    double qty;
};

class GlobalData
{
public:
    GlobalData();

    //shadow effect function
    static void setShadow(QWidget* widget);

    //menu data Functions
    static void setMenuItem(QString id,QString name,QString category,double price);
    static void setItemQty(menuData* item,double qty);

    //delete vector
    static void deleteCartVectordata();

    //vector to store menu in dynamic array
    static QVector<menuData*> menuDataList;
    static QVector<orderData*> CartItem;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;

};

#endif // GLOBALDATA_H
