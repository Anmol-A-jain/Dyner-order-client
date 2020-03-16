#ifndef TABLECUSTOMBUTTONS_H
#define TABLECUSTOMBUTTONS_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class TableCustomButtons;
}

class TableCustomButtons : public QWidget
{
    Q_OBJECT

public:
    explicit TableCustomButtons(int tbl,QString name,QWidget *parent = nullptr);
    ~TableCustomButtons();
    QString getText();

private slots:
    void on_btnTable_clicked();

private:
    Ui::TableCustomButtons *ui;
    QWidget* myParent;
    int tbl;
};

#endif // TABLECUSTOMBUTTONS_H
