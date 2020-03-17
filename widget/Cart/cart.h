#ifndef CART_H
#define CART_H

#include <QWidget>
#include <QRegExpValidator>

namespace Ui {
class Cart;
}

class Cart : public QWidget
{
    Q_OBJECT

public:
    explicit Cart(int tbl,QWidget *parent = nullptr);
    ~Cart();
    qint16 getTblNo();
    void loadData();
    void customerData(QString name,QString mblNo);

private slots:
    void on_AddItem_clicked();

private:
    Ui::Cart *ui;
    QWidget* myParent;
    qint16 tbl;
    QRegExpValidator* r1;
    QRegExpValidator* r2;
};

#endif // CART_H
