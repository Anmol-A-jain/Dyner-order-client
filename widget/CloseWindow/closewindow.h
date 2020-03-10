#ifndef CLOSEWINDOW_H
#define CLOSEWINDOW_H

#include <QWidget>

namespace Ui {
class CloseWindow;
}

class CloseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CloseWindow(QWidget *parent = nullptr);
    ~CloseWindow();

private slots:

    void on_btnQuit_clicked();

private:
    Ui::CloseWindow *ui;
    QWidget* myParent;
};

#endif // CLOSEWINDOW_H
