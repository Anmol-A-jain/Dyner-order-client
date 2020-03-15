#ifndef CLOSEWINDOW_H
#define CLOSEWINDOW_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CloseWindow;
}

class CloseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CloseWindow(QLabel *lblTitle,QWidget *parent = nullptr);
    ~CloseWindow();

private slots:

    void on_btnQuit_clicked();

private:
    Ui::CloseWindow *ui;
};

#endif // CLOSEWINDOW_H
