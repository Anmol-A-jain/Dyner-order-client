#ifndef ADDORDERITEM_H
#define ADDORDERITEM_H

#include "../customWidget/orderitemdata.h"
#include <QVector>
#include <QWidget>

namespace Ui {
class AddOrderItem;
}

class AddOrderItem : public QWidget
{
    Q_OBJECT

public:
    explicit AddOrderItem(QWidget *parent = nullptr);
    ~AddOrderItem();
    void loadData();
    void deleteVecterData();    
    void paintEvent(QPaintEvent *event) override;
    void updateCategorylist();

private slots:
    void on_menuColumn_currentIndexChanged(int index);

    void on_btnSearch_clicked();

    void on_SearchTextBox_returnPressed();

    void on_SearchTextBox_textChanged(const QString &arg1);

    void on_categoryList_currentIndexChanged(int index);

private:
    Ui::AddOrderItem *ui;
    QWidget *myParent;
    QVector<OrderItemData*> itemlist;
};

#endif // ADDORDERITEM_H
