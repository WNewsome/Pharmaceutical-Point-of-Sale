#include "newprescription.h"
#include "ui_newprescription.h"

NewPrescription::NewPrescription(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewPrescription)
{
    ui->setupUi(this);
    API=DataStorage::getInstance();
    currentAccount=CheckoutAccount::getInstance();
    ui->label_id->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit_change(QString)));
    connect(ui->items_dropdown,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(on_clicked_dropdown(QListWidgetItem *)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(on_accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(on_reject()));
}

NewPrescription::~NewPrescription()
{
    delete ui;
}

void NewPrescription::on_accept(){
    if(drug.valid){
        if(ui->checkBox->isChecked()){
            drug.amount=ui->spinBox->value();
            currentAccount->add_item(drug);
            emit accept({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),QDate::currentDate(),true});
            this->close();
        }
        else{
            emit accept({drug.name.toStdString(),drug.UPC,ui->spinBox->value(),ui->spinBox_2->value(),QDate(2010,1,1),false});
            this->close();
        }
    }
}

void NewPrescription::on_reject(){
    this->close();
    this->setParent(nullptr);
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
