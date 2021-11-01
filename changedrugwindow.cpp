#include "changedrugwindow.h"
#include "ui_changedrugwindow.h"

changedrugwindow::changedrugwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::changedrugwindow)
{
    ui->setupUi(this);
}

changedrugwindow::~changedrugwindow()
{
    delete ui;
}

void changedrugwindow::changename(QString name){

    drugname = name;
    ui->drugname->setText(drugname);
}

void changedrugwindow::on_confirm_clicked()
{
    //check if valid numbers
    //APIchange price???
    //API->add_inventory(drug,amount)

    this->close();
}

