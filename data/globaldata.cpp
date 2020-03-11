#include "globaldata.h"
#include <QGraphicsDropShadowEffect>

QVector<menuData*> GlobalData::menuDataList;

GlobalData::GlobalData()
{

}

void GlobalData::setShadow(QWidget *widget)
{

    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(1.0);
    effect->setBlurRadius(5.0);
    effect->setColor(QColor(0,0,0));
    widget->setGraphicsEffect(effect);
}

void GlobalData::setMendsduItem(QString id, QString name, QString category, double price)
{
    menuData* item = new menuData ;

    item->id = id;
    item->name = name;
    item->category = category;
    item->price = price;

    GlobalData::menuDataList.push_back(item);
}
