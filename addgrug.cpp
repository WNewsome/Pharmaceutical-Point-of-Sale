#include "addgrug.h"
#include "ui_addgrug.h"

addgrug::addgrug(drug_t drug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addgrug)
{
    ui->setupUi(this);
    this->drug = drug;
    API = DataStorage::getInstance();
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
    this->drug.picture_url = "https://www.google.com/imgres?imgurl=https%3A%2F%2Fwww.drugs.com%2Fimages%2Fpills%2Ffio%2FSHR01050%2Fvyvanse.JPG&imgrefurl=https%3A%2F%2Fwww.drugs.com%2Fimprints%2Fnrp104-50-mg-9792.html&tbnid=KTN9mp_BQGiKAM&vet=10CAsQxiAoAWoXChMIiJKN3cP28wIVAAAAAB0AAAAAEAc..i&docid=P5cr3v69gpFpZM&w=288&h=216&itg=1&q=vyvanse&ved=0CAsQxiAoAWoXChMIiJKN3cP28wIVAAAAAB0AAAAAEAc";

    API->create_new_drug(drug,this->drug.amount);

    this->close();
}

