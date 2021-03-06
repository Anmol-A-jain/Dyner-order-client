#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LogInWidget;
}

class LogInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();

    void setMsg(QString msg);

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LogInWidget *ui;
    QWidget* myParent;
};

#endif // LOGINWIDGET_H
