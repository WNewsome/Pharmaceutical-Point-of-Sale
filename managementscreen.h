#ifndef MANAGEMENTSCREEN_H
#define MANAGEMENTSCREEN_H

#include <QWidget>
#include "datastorage.h"
#include "changedrugwindow.h"
#include "addgrug.h"

namespace Ui {
class Managementscreen;
}

class Managementscreen : public QWidget
{
    Q_OBJECT

public:
    explicit Managementscreen(QWidget *parent = nullptr);
    ~Managementscreen();
    void searchdrugs();

private slots:
    void on_changedruginfoclick_clicked();

    void on_addnewdrugclicked_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::Managementscreen *ui;
    DataStorage *API;
    changedrugwindow *updateDrug;
    addgrug* addDrug;
    drug_t newDrug;
    std::vector<drug_t> drugList;
    bool secured;
    drug_t curDrug;
};

#endif // MANAGEMENTSCREEN_H
