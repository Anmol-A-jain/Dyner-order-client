#ifndef TABLELIST_H
#define TABLELIST_H

#include <QWidget>

namespace Ui {
class tableList;
}

class tableList : public QWidget
{
    Q_OBJECT

public:
    explicit tableList(int tbl,QWidget *parent = nullptr);
    ~tableList();
    void setButton();

private:
    Ui::tableList *ui;
    QWidget* myParent;
    int tbl;
    int column;
    int row;
};

#endif // TABLELIST_H
