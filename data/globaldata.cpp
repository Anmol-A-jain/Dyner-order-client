#include "globaldata.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QVector<menuData*> GlobalData::menuDataList;
QVector<orderData*> GlobalData::CartItem;

GlobalData::GlobalData()
{
    this->tagname.insert(data::clientName,"waiterName");
    this->attribute.insert(data::clientName,"Name");
}

QString GlobalData::getTagName(int tagname)
{
    return this->tagname[tagname];
}

QString GlobalData::getattribute(int tagname)
{
    return this->attribute[tagname];
}

void GlobalData::setShadow(QWidget *widget,QColor color,qreal real,qreal radius  )
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(real);
    effect->setBlurRadius(radius);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}


void GlobalData::setMenuItem(QString id, QString name, QString category, double price)
{
    menuData* item = new menuData ;

    item->id = id;
    item->name = name;
    item->category = category;
    item->price = price;

    menuDataList.push_back(item);
}

void GlobalData::setItemQty(menuData* item, double qty)
{
    orderData* order = new orderData;

    order->item = item;
    order->qty = qty;

    CartItem.push_back(order);
}

void GlobalData::deleteCartVectordata()
{
    for (int i = 0; i < CartItem.count(); ++i)
    {
        delete CartItem.at(i);
    }
    CartItem.clear();
    qDebug() << "GlobalData (deleteCartVectordata) : cart data has been deleted";
}
