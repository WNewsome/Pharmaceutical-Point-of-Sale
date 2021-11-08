#include "newprescription.h"
#include "ui_newprescription.h"

NewPrescription::NewPrescription(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewPrescription)
{
    ui->setupUi(this);
    updateFlag=false;
    API=DataStorage::getInstance();
    currentAccount=CheckoutAccount::getInstance();
    ui->label_id->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->dateEdit->setVisible(false);
    ui->pushButton->setVisible(false);
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit_change(QString)));
    connect(ui->items_dropdown,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(on_clicked_dropdown(QListWidgetItem *)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(on_accept()));
}

NewPrescription::NewPrescription(prescription_t prescription,int index,QWidget *parent):
QMainWindow(parent),
ui(new Ui::NewPrescription){
    ui->setupUi(this);
    API=DataStorage::getInstance();
    currentAccount=CheckoutAccount::getInstance();
    this->prescriotion=prescription;
    this->index=index;
    drug=API->search_one_drug(prescriotion.name);
    updateFlag=true;
    ui->label_id->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    ui->pushButton->setVisible(true);
    ui->pushButton->setEnabled(true);
    ui->dateEdit->setDate(this->prescriotion.last_time);
    ui->dateEdit->setEnabled(true);
    ui->dateEdit->setVisible(true);
    ui->label_5->setEnabled(true);
    ui->label_5->setVisible(true);
    ui->label_id->setText(QString::fromStdString(drug.UPC));
    ui->spinBox->setValue(this->prescriotion.amount);
    ui->spinBox_2->setValue(this->prescriotion.period);
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->lineEdit->setText(drug.name);
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit_change(QString)));
    connect(ui->items_dropdown,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(on_clicked_dropdown(QListWidgetItem *)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(on_accept()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_delete()));
}

NewPrescription::~NewPrescription()
{
    delete ui;
}

void NewPrescription::on_accept(){
    if(drug.valid){
        if(updateFlag){
            if(ui->checkBox->isChecked()){
                drug.amount=ui->spinBox->value();
                currentAccount->add_item(drug);
                emit changed({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),ui->dateEdit->date(),true},index);
            }
            else{
                emit changed({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),ui->dateEdit->date(),false},index);
            }
        }
        else{
            if(ui->checkBox->isChecked()){
                drug.amount=ui->spinBox->value();
                currentAccount->add_item(drug);
                emit accept({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),QDate(2010,1,1),true});
            }
            else{
                emit accept({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),QDate(2010,1,1),false});
            }
        }
        this->close();
    }
}


void NewPrescription::on_edit_change(QString buffer){
    drug = drug_t();
    if(buffer.size()==0){
        return;
    }
    ui->items_dropdown->clear();
    std::string name=buffer.toStdString();
    std::vector<drug_t> drug_list_drop = API->search_drugs(name);
    for (size_t i=0;i<drug_list_drop.size() ;i++ ) {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(drug_list_drop[i].name);
        ui->items_dropdown->insertItem(i,newItem);
    }
    if(!ui->items_dropdown->isVisible()){
        ui->items_dropdown->setVisible(true);
        ui->items_dropdown->setEnabled(true);
    }
}

void NewPrescription::on_clicked_dropdown(QListWidgetItem *item){
    ui->lineEdit->setText(item->text());
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    drug=API->search_one_drug(item->text().toStdString());
    ui->label_id->setText(QString::fromStdString(drug.UPC));
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
}

void NewPrescription::on_delete(){
    emit to_delete(index);
    this->close();
    this->setParent(nullptr);
}
