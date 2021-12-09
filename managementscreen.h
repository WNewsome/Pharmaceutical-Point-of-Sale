#ifndef MANAGEMENTSCREEN_H
#define MANAGEMENTSCREEN_H

// managmentscreen.h	Jessica Orefice		VT	ECE4574 FA21	Nov 12, 2021
// This class allows the user to interact with the management screen tab. This allows them to edit/search/add drugs
// as well as generate reports and edit settings.

#include <QWidget>
#include <QFileDialog>
#include "datastorage.h"
#include "addgrug.h"
#include "settingsscreen.h"
#include "reports.h"

namespace Ui {
class Managementscreen;
}

class Managementscreen : public QWidget
{
    Q_OBJECT

public:
    explicit Managementscreen(QWidget *parent = nullptr);
    ~Managementscreen();

private slots:
    void changedruginfoclicked();

    void on_addnewdrugclicked_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_editdrug_2_clicked();

    void on_editimage_clicked();

    void on_generatereports_clicked();

    void on_updatesettigns_clicked();

private:
    Ui::Managementscreen *ui;
    DataStorage *API;
    addgrug* addDrug;
    drug_t newDrug;
    std::vector<drug_t> drugList;
    bool secured;
    drug_t curDrug;
    QPixmap image;
    QImage* imageObject;
    QGraphicsScene* drugimage;
    Settingsscreen* settings;
    Reports* reports;
};

#endif // MANAGEMENTSCREEN_H
