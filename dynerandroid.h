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

private:
    Ui::DynerAndroid *ui;
    QWidget* childFrame;
};
#endif // DYNERANDROID_H
