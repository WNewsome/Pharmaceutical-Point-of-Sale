#include "checkout.h"
#include "ui_checkout.h"


Checkout::Checkout(QWidget *parent ): QMainWindow(parent),
    ui(new Ui::Checkout){
    ui->setupUi(this);
    CheckoutAccount* account=CheckoutAccount::getInstance();
    std::vector<drug_t> drugList=account->drugList;
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
    ui->listWidget->addItem(QString::fromStdString("Subtotal:\t$"+std::to_string(account->get_total())));
    ui->listWidget->addItem(QString::fromStdString("Tax:\t$"+std::to_string(account->get_total()*0.15)));
    ui->listWidget->addItem(QString::fromStdString("Total:\t$"+std::to_string(account->get_total()*1.15)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(on_accept()));
    total=account->get_total()*1.15;
    ui->textEdit->setAlignment(Qt::AlignRight);
    ui->label_4->setStyleSheet("QLabel { background-color : white; color : red; }");
    ui->label_4->setText("-1.00");
    buffer="";
}

Checkout::~Checkout()
{
    delete ui;
}
void Checkout::keyPressEvent(QKeyEvent *e){
    if(!(e->key()==Qt::Key_Backspace)&&!(e->key()==Qt::Key_Return)){
        bool isint;
        e->text().toInt(&isint);
        if(isint){
            buffer+=e->text();
            QString temp=buffer;
            while(temp.length()<3){
                temp="0"+temp;
            }
            temp.insert(temp.length()-2,'.');
            ui->textEdit->clear();
            ui->textEdit->setText(temp);
            if((temp.toDouble()-total)>-0.01){
                ui->label_4->setStyleSheet("QLabel { background-color : white; color : black; }");
                ui->label_4->setText(QString::fromStdString(std::to_string(temp.toDouble()-total)));
            }
        }
    }
}

void Checkout::on_accept(){
    if((ui->textEdit->toPlainText().toDouble()-total)>-0.01){
        this->close();
        clearCart();
        this->setParent(nullptr);
    }
}
