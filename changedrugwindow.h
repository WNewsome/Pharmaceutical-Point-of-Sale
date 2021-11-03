#ifndef CHANGEDRUGWINDOW_H
#define CHANGEDRUGWINDOW_H

#include <QMainWindow>
#include "datastorage.h"

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
    void on_confirm_clicked();

private:
    Ui::changedrugwindow *ui;
    QString drugname;
    DataStorage *API;
};

#endif // CHANGEDRUGWINDOW_H
