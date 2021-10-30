#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "managementscreen.h"

DataStorage* DataStorage::instance;

void MainWindow::searchDrug(QNetworkReply *reply){
    // TODO: I will remove this function to use datastorage class instead!
    // Reply from server received
    // Convert all values to JSON format
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();
    int i = 0;
    // Set dropdown list to visible and delete any older items
    ui->items_dropdown->setVisible(true);
    ui->items_dropdown->clear();
    // Display every json object
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString price = obj["price"].toString();
        QString cost = price;
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setData(1, cost.toDouble());
        newItem->setText(name+" $"+price);
        ui->items_dropdown->insertItem(i, newItem);
        i++;
        // Adapt the height of the list menu according to number of items found
        ui->items_dropdown->setFixedHeight(33*i);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 150px; width: 100px; }");
    ui->tabWidget->addTab(new Managementscreen(), QString("Management").arg(ui->tabWidget->count() +1));
    connect(ui->search_button_2, SIGNAL(clicked()), this, SLOT(on_search_button_p_clicked()));
    connect(ui->clear_button, SIGNAL(clicked()), this, SLOT(on_clear_p_clicked()));
    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(on_new_p_clicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_search_table_p_clicked(int,int)));
    connect(ui->checkout_button,SIGNAL(clicked()), this, SLOT(on_checkout_p_clicked()));
    // Set search drug dropdown to invisible
    ui->items_dropdown->setVisible(false);

    // Init API
    API = DataStorage::getInstance();

    // TODO: remove these tests
    // Search for one drug matching word "Tyle*"
    drug_t drug = API->search_one_drug("tyle");
    if(drug.valid){
        qDebug() << "Drug Name: "+ drug.name +" Price: "+QString::number(drug.price);
    }

    // Show results of searching for "Asp*"
    std::vector<drug_t> drugs = API->search_drugs("Asp");

    for(size_t i = 0; i < drugs.size(); i++){
         qDebug() << "Drug Name: "+ drugs[i].name+" Quantity: "+QString::number(drugs[i].amount);
    }
    // Search for one patient by first name
    patient_t patient = API->search_one_patient("James");
    if(patient.valid){
        qDebug() << QString::fromStdString( patient.first_name + " " + patient.last_name);
        qDebug() << QString::fromStdString(patient.address.street_number+", "+patient.address.city+ ", "+ patient.address.state);
    }
    // Create a new drug and 32 units in inventory
    drug_t new_drug;
    new_drug.name = "this is a new drug";
    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "the_url";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    //API->create_new_drug(new_drug, 10);

    // Test create a new patient into the DB
    patient_t new_patient;
    new_patient.first_name = "Willy";
    new_patient.last_name = "Wonka";
    new_patient.middle_name = "john";
    new_patient.address.street_number = "111 Pensilvania Ave.";
    new_patient.address.city = "Washington D.C.";
    new_patient.address.state = "D.C.";
    new_patient.address.zip_code = "23333";
    new_patient.phone = "5404441122";
    new_patient.SSN = "123654789";
    new_patient.DOB.day = 12;
    new_patient.DOB.month = 11;
    new_patient.DOB.year = 1997;

    //API->create_new_patient(new_patient);
    patient = API->search_one_patient("Berth");
    patient.first_name = "Berthoooo";
    API->update_patient(patient);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_search_button_clicked()
{
    // Search requested
    // Connect to web API
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    // Add name of drug as a parameter
    QString word_to_search = ui->search_lineEdit->text();
    // Once a response is received it will call searchDrug()
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::searchDrug);
    const QUrl url = QUrl(web_API+"?name="+word_to_search);
    QNetworkRequest request(url);
    man->get(request);
}

void MainWindow::on_items_dropdown_itemClicked(QListWidgetItem *item)
{
    // An item was selected from the dropdown search result list
    // Hide dropdown list
    ui->items_dropdown->setVisible(false);
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(item->text());
    ui->items_list->insertItem(0, newItem);
    // Add item to current account to update shopping list
    //currentAccount.add_item( item->data(1).toDouble());
    // Delete items in dropdown lists (We dont need them anymore)
    ui->items_dropdown->clear();
    // Update current total
    ui->total->setText("$ "+QString::number(currentAccount.get_total()));
}

void  MainWindow::on_search_button_p_clicked(){
    ui->tableWidget->setRowCount(1);
    patientList.clear();
    std::string search_buffer=ui->search_lineEdit_2->text().toStdString();
    if(search_buffer.find(' ')!=-1){
        std::vector<std::pair<int,std::string>> searchList;
        int pos=search_buffer.find(' ');
        while (pos>-1) {
            std::string token=search_buffer.substr(0,pos);
            search_buffer=search_buffer.substr(pos+1);
            std::string filed=token.substr(0,token.find(':'));
            if(filed=="name")
                searchList.push_back(std::pair<int,std::string>(0,token.substr(token.find(':')+1)));
            else if(filed=="id")
                searchList.push_back(std::pair<int,std::string>(1,token.substr(token.find(':')+1)));
            else if(filed=="ssn"){
                secuared=true;
                searchList.push_back(std::pair<int,std::string>(2,token.substr(token.find(':')+1)));
            }
            else if(filed=="phone")
                searchList.push_back(std::pair<int,std::string>(3,token.substr(token.find(':')+1)));
            pos=search_buffer.find(' ');
        }
        patientList=std::vector<patient_t>();
    }
    else{
        patientList=API->search_patients(search_buffer);
    }
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setRowCount(patientList.size()+1);
    for(size_t i=0;i<patientList.size();i++){
        patient_t patient=patientList[i];
        std::string SSN = patient.SSN;
        if(!secuared){
            SSN[0]='*';
            SSN[1]='*';
            SSN[2]='*';
            SSN[3]='*';
            SSN[4]='*';
        }
        QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(patient.first_name));
        QTableWidgetItem *id = new QTableWidgetItem(QString::fromStdString(std::to_string(patient.DOB.year)+'/'+std::to_string(patient.DOB.month)+'/'+std::to_string(patient.DOB.day)));
        QTableWidgetItem *ssn = new QTableWidgetItem(QString::fromStdString(SSN));
        QTableWidgetItem *phone = new QTableWidgetItem(QString::fromStdString(patient.phone));
        ui->tableWidget->setItem(i+1,0,num);
        ui->tableWidget->setItem(i+1,1,name);
        ui->tableWidget->setItem(i+1,2,id);
        ui->tableWidget->setItem(i+1,3,ssn);
        ui->tableWidget->setItem(i+1,4,phone);
    }
}

void MainWindow::on_search_table_p_clicked(int row,int colum){
    if(row==0){
        return;
    }
    Dialog *dialog=new Dialog(patientList[row-1],this);
    dialog->setWindowFlag(Qt::SubWindow);
    dialog->show();
    connect(dialog,SIGNAL(correct_ssn(patient_t)),this,SLOT(on_correct_ssn(patient_t)));
}

void MainWindow::on_correct_ssn(patient_t patient){
    ui->prescriptionTable->setEnabled(true);
    ui->checkout_button->setEnabled(true);
    ui->update_pButton->setEnabled(true);
    curPatient=patient;
    std::vector<prescription_t> prescriptionList = patient.prescription;
    ui->nameEdit->setText(QString::fromStdString(patient.first_name+" "+patient.last_name));
    ui->phoneEdit->setText(QString::fromStdString(patient.phone));
    ui->ssnEdit->setText(QString::fromStdString(patient.SSN));
    ui->addressEdit->setPlainText(QString::fromStdString(patient.address.toString()));
    ui->prescriptionTable->setRowCount(prescriptionList.size());
    for(size_t i=0;i<prescriptionList.size();i++){
        prescription_t prescription = prescriptionList[i];
        QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(prescription.name));
        QTableWidgetItem *UPC = new QTableWidgetItem(QString::fromStdString(prescription.UPC));
        QTableWidgetItem *amount = new QTableWidgetItem(QString::fromStdString(std::to_string(prescription.amount)));
        QTableWidgetItem *next;
        if(prescription.getValid()){
            next=new QTableWidgetItem(QString::fromStdString("N/A"));
            num->setBackground(Qt::green);
            name->setBackground(Qt::green);
            UPC->setBackground(Qt::green);
            amount->setBackground(Qt::green);
            next->setBackground(Qt::green);
        }
        else{
            time_t nextTime=prescription.last_time+60*60*24*prescription.period;
            next=new QTableWidgetItem(QString::fromStdString(ctime(&nextTime)));
            num->setBackground(Qt::red);
            name->setBackground(Qt::red);
            UPC->setBackground(Qt::red);
            amount->setBackground(Qt::red);
            next->setBackground(Qt::red);
        }
        ui->prescriptionTable->setItem(i,0,num);
        ui->prescriptionTable->setItem(i,1,name);
        ui->prescriptionTable->setItem(i,2,UPC);
        ui->prescriptionTable->setItem(i,3,amount);
        ui->prescriptionTable->setItem(i,4,next);
    }
}

void MainWindow::on_clear_p_clicked(){
    ui->tableWidget->setRowCount(1);
    ui->search_lineEdit_2->clear();
    ui->nameEdit->clear();
    ui->phoneEdit->clear();
    ui->ssnEdit->clear();
    ui->addressEdit->clear();
    ui->prescriptionTable->setRowCount(0);
}

void MainWindow::on_new_p_clicked(){
    patient_t newPatient;
    newPatient.first_name=ui->nameEdit->text().toStdString();
    newPatient.phone=ui->phoneEdit->text().toStdString();
    newPatient.SSN=ui->ssnEdit->text().toStdString();
    API->create_new_patient(newPatient);
}

void MainWindow::on_checkout_p_clicked(){
    if(curPatient.prescription.size()>0){
        for (prescription_t prescription : curPatient.prescription) {
            if(prescription.getValid()){
                drug_t drug=API->search_one_drug(prescription.name);
                drug.amount=prescription.amount;
                currentAccount.add_item(drug);
            }
        }
        Checkout* checkout=new Checkout(currentAccount,this);
        checkout->setWindowFlag(Qt::SubWindow);
        checkout->show();
    }
}
