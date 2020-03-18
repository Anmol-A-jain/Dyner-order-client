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
    void dinningTableList(int tbl = 0);
    void cartWidgetWindow(int tblNo);
    void logInWidget();
    void closeWidget();
    void menuWidget(int tblNo);

    void setWidget(QWidget* child);
    void setTitle(QString title);
    void ChangeBoolvalue(bool value);

    void callCartObject(QString name,QString mblNo);

    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_btnHome_clicked();

private:
    Ui::DynerAndroid *ui;
    QWidget* childFrame;
    QWidget* logWindow;
    QWidget* tableButtons;
    QWidget* cart;
    QWidget* closeWindow;
    QWidget* menuList;
    int tbl;
    int currentTbl;

    bool isExiting;
    enum widgetWindow{serverConnectionWindow,cartWindow,tableListWindow,closeWindowWidget,menuListWidget};

};
#endif // DYNERANDROID_H
