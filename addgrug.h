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
    drug_t drug;
public:
    explicit addgrug(drug_t drug, QWidget *parent = nullptr);
    ~addgrug();
    void newDrugname(QString drugname);

private slots:
    void on_confirm_clicked();

private:
    Ui::addgrug *ui;
    DataStorage *API;
};

#endif // ADDGRUG_H
