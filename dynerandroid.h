#ifndef DYNERANDROID_H
#define DYNERANDROID_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DynerAndroid; }
QT_END_NAMESPACE

class DynerAndroid : public QMainWindow
{
    Q_OBJECT

public:
    DynerAndroid(QWidget *parent = nullptr);
    ~DynerAndroid();
    void hideConnectionWdget();
    void showConnectionWdget();
    void loadTable(int tbl);
    void loadTable();
    void loadCart(int tbl);

private slots:
    void on_btnHome_clicked();

private:
    Ui::DynerAndroid *ui;
    QWidget* childFrame;
    QWidget* logWindow;
    QWidget* tableButtons;
    QWidget* cart;
    int tbl;

};
#endif // DYNERANDROID_H
