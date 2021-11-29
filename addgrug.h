#ifndef ADDGRUG_H
#define ADDGRUG_H

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

    DataStorage *API;
    drug_t newDrug;
};

#endif // ADDGRUG_H
