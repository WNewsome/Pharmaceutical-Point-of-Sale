#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "managementscreen.h"
#include "settingsscreen.h"

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
    patientScreen=new PatientScreen();
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 150px; width: 100px; }");

    ui->tabWidget->addTab(new Managementscreen(), QString("Management").arg(ui->tabWidget->count() +1));
    ui->tabWidget->addTab(new Settingsscreen(), QString("Settings").arg(ui->tabWidget->count() +1));
    ui->tabWidget->addTab(patientScreen,QString("Patient Screen").arg(ui->tabWidget->count()+1));
    connect(ui->actionCheckout,SIGNAL(triggered()), this, SLOT(on_checout_action()));
    connect(ui->actionClear_cart,SIGNAL(triggered()), patientScreen, SLOT(on_clear_cart_action()));
      
    // Set search drug dropdown to invisible
    ui->items_dropdown->setVisible(false);
    currentAccount->getInstance();
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
    ui->total->setText("$ "+QString::number(currentAccount->get_total()));
}

void MainWindow::on_checout_action(){
    Checkout* checkout=new Checkout(this);
    checkout->setWindowFlag(Qt::SubWindow);
    connect(checkout,SIGNAL(clearCart()),patientScreen,SLOT(on_accept_checkout()));
    checkout->show();
}

