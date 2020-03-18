#ifndef ORDERITEMDATA_H
#define ORDERITEMDATA_H

#include <QWidget>
#include "data/globaldata.h"


namespace Ui {
class OrderItemData;
}

class OrderItemData : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItemData(menuData* item,double qty = 0,QWidget *parent = nullptr);
    ~OrderItemData();

    QString getId();
    QString getName();
    QString getCategory();
    QString getPrice();

private slots:

    void on_btnPlus_clicked();

    void on_btnMinus_clicked();

private:
    Ui::OrderItemData *ui;
    QWidget *myparent;
    menuData *item;
};

#endif // ORDERITEMDATA_H
