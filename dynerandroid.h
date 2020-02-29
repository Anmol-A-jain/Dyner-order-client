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

    QWidget* newWindow(int option,int tblNo = 0);
    void dinningTableList(int tbl);
    void cartWidgetWindow(int tblNo);
    void logInWidget();
    void closeWidget();

private slots:
    void on_btnHome_clicked();

private:
    Ui::DynerAndroid *ui;
    QWidget* childFrame;
    QWidget* logWindow;
    QWidget* tableButtons;
    QWidget* cart;
    int tbl;
    enum widgetWindow{serverConnectionWindow,cartWindow,tableListWindow,closeWindowWidget};

};
#endif // DYNERANDROID_H
