#ifndef ADDGRUG_H
#define ADDGRUG_H

// addgrug.h	Jessica Orefice		VT	ECE4574 FA21	Nov 12, 2021
// This class allows the user to interact with the GUI and add a drug to the datbase

#include <QMainWindow>
#include "datastorage.h"
#include <QGraphicsScene>

namespace Ui {
class addgrug;
}

class addgrug : public QMainWindow
{
    Q_OBJECT

public:
    explicit addgrug(QWidget *parent = nullptr);
    ~addgrug();

private:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_confirm_clicked();
    void on_openimage_clicked();

private:
    Ui::addgrug *ui;
    QPixmap image;
    QImage* imageObject;
    QGraphicsScene* drugimage;

    DataStorage *API; //datastorage
    drug_t newDrug;   //
};

#endif // ADDGRUG_H
