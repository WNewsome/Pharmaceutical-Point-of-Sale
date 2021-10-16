#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

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
    updateDrug = new changedrugwindow(this);
    // Set search drug dropdown to invisible
    ui->items_dropdown->setVisible(false);
    // Init API
    API = new DataStorage();

    // TODO: remove these tests
    // Search for one drug matching word "Tyle*"
    drug_t drug = API->search_one_drug("tyle");
    if(drug.valid){
        qDebug() << "Drug Name: "+ drug.name +" Price: "+QString::number(drug.price);
    }

    // Show results of searching for "Asp*"
    std::vector<drug_t> drugs = API->search_drugs("Asp");

    for(size_t i = 0; i < drugs.size(); i++){
         qDebug() << "Drug Name: "+ drugs[i].name+" Price: "+QString::number(drugs[i].price);
    }
    // Search for one patient by first name
    patient_t patient = API->search_one_patient("James");
    if(patient.valid){
        qDebug() << patient.first_name + " " + patient.last_name;
        qDebug() << patient.address.street_number+", "+patient.address.city+ ", "+ patient.address.state;
    }

    // Add all patients in DB to patients list in patients tab
    std::vector<patient_t> patients = API->search_patients("");
    for(size_t i = 0; i < patients.size(); i++){
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(   patients[i].first_name+" "+
                            patients[i].last_name+" - "+
                            patients[i].address.street_number+", "+
                            patients[i].address.city+ ", "+
                            patients[i].address.state + " - "+
                            patients[i].phone);
        ui->patientsListView->insertItem((int)i, newItem);
    }
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

void MainWindow::on_pushButton_5_clicked()
{
    //looks up name
    //brings up screen to update drug
    updateDrug->show();
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
    currentAccount.add_item( item->data(1).toDouble());
    // Delete items in dropdown lists (We dont need them anymore)
    ui->items_dropdown->clear();
    // Update current total
    ui->total->setText("$ "+QString::number(currentAccount.get_total()));
}
