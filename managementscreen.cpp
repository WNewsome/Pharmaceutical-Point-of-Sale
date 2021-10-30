#include "managementscreen.h"
#include "ui_managementscreen.h"

Managementscreen::Managementscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Managementscreen)
{
    ui->setupUi(this);
    updateDrug = new changedrugwindow(this);
}

Managementscreen::~Managementscreen()
{
    delete ui;
}

void Managementscreen::on_changedruginfoclick_clicked()
{
    updateDrug->changename(ui->editdrug->text());
    updateDrug->show();
}


void Managementscreen::on_addnewdrugclicked_clicked()
{

}

