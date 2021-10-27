#include "checkout.h"
#include "ui_checkout.h"

Checkout::Checkout(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Checkout)
{
    ui->setupUi(this);
}

Checkout::Checkout(CheckoutAccount accout,QWidget *parent ): QMainWindow(parent),
    ui(new Ui::Checkout){
    ui->setupUi(this);
    std::vector<drug_t> drugList=accout.drugList;
    ui->tableWidget->setRowCount(drugList.size());
    for(size_t i=0;i<drugList.size();i++){
        drug_t drug=drugList[i];
        QTableWidgetItem *price = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.price)));
        QTableWidgetItem *name = new QTableWidgetItem(drug.name);
        QTableWidgetItem *totalPrice = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.price*drug.amount)));
        QTableWidgetItem *amount = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.amount)));
        total+=drug.price*drug.amount;
        ui->tableWidget->setItem(i,0,name);
        ui->tableWidget->setItem(i,1,price);
        ui->tableWidget->setItem(i,2,amount);
        ui->tableWidget->setItem(i,3,totalPrice);
    }
    ui->listWidget->addItem(QString::fromStdString("Subtotal:\t$"+std::to_string(accout.get_total())));
    ui->listWidget->addItem(QString::fromStdString("Tax:\t$"+std::to_string(accout.get_total()*0.15)));
    ui->listWidget->addItem(QString::fromStdString("Total:\t$"+std::to_string(accout.get_total()*1.15)));
    total*=accout.get_total()*1.15;
}

Checkout::~Checkout()
{
    delete ui;
}
