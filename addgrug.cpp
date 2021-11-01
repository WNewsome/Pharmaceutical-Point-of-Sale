#include "addgrug.h"
#include "ui_addgrug.h"

addgrug::addgrug(drug_t drug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addgrug)
{
    ui->setupUi(this);
    this->drug = drug;
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(on_confirm_clicked()));
}

addgrug::~addgrug()
{
    delete ui;
}

void addgrug::newDrugname(QString drugname){
    drug.name = drugname;
    ui->drugname->setText(drug.name);
}

void addgrug::on_confirm_clicked()
{
    //check if everything is filled in and display error??

    //put drug stuff from lines in
    this->drug.DEA = this->ui->DEA->text().toStdString();
    this->drug.GPI = this->ui->gpi->text().toStdString();
    this->drug.NDC = this->ui->NDC->text().toStdString();
    this->drug.UPC = this->ui->upc->text().toStdString();
    this->drug.amount = this->ui->invintory->text().toInt();
    this->drug.brand = this->ui->brandname->text();
    this->drug.control_status = this->ui->control->text();
    this->drug.cost = this->ui->Cost->text().toInt();
    this->drug.price = this->ui->Price->text().toInt();
   // this->drug.picture_url = this->ui->DEA->text().toStdString();

    API->create_new_drug(drug,this->drug.amount);

    this->close();
}
