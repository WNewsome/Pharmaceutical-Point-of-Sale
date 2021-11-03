#ifndef ADDGRUG_H
#define ADDGRUG_H

#include <QMainWindow>
#include "datastorage.h"

namespace Ui {
class addgrug;
}

class addgrug : public QMainWindow
{
    Q_OBJECT
public:
    explicit addgrug(QWidget *parent = nullptr);
    ~addgrug();
    void newDrugname(QString drugname);

private slots:
    void on_confirm_clicked();

private:
    Ui::addgrug *ui;
    DataStorage *API;
    drug_t newDrug;
};

#endif // ADDGRUG_H
