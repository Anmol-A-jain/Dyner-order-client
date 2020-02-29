#ifndef CART_H
#define CART_H

#include <QWidget>

namespace Ui {
class Cart;
}

class Cart : public QWidget
{
    Q_OBJECT

public:
    explicit Cart(int tbl,QWidget *parent = nullptr);
    ~Cart();

private:
    Ui::Cart *ui;
    QWidget* myParent;
    int tbl;
};

#endif // CART_H
