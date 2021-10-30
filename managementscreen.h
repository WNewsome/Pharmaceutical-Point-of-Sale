#ifndef MANAGEMENTSCREEN_H
#define MANAGEMENTSCREEN_H

#include <QWidget>
#include "changedrugwindow.h"

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
    void on_changedruginfoclick_clicked();

    void on_addnewdrugclicked_clicked();

private:
    Ui::Managementscreen *ui;
    changedrugwindow *updateDrug;
};

#endif // MANAGEMENTSCREEN_H
