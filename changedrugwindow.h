#ifndef CHANGEDRUGWINDOW_H
#define CHANGEDRUGWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeDrugWindow;
}

class ChangeDrugWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeDrugWindow(QWidget *parent = nullptr);
    ~ChangeDrugWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangeDrugWindow *ui;
};

#endif // CHANGEDRUGWINDOW_H
