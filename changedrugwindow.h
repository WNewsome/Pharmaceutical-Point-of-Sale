#ifndef CHANGEDRUGWINDOW_H
#define CHANGEDRUGWINDOW_H

#include <QMainWindow>

namespace Ui {
class changedrugwindow;
}

class changedrugwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit changedrugwindow(QWidget *parent = nullptr);
    ~changedrugwindow();
    void changename(QString name);

private slots:
    void on_pushButton_clicked();

private:
    Ui::changedrugwindow *ui;
    QString drugname;
};

#endif // CHANGEDRUGWINDOW_H
