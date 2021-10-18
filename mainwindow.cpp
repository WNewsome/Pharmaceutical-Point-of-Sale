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
    connect(ui->search_button_2, SIGNAL(clicked()), this, SLOT(on_search_button_p_clicked()));
    updateDrug = new changedrugwindow(this);
    // Set search drug dropdown to invisible
    ui->items_dropdown->setVisible(false);
    // TODO: remove this simple test
    drug_t drug = API->search_one_drug("NyQuil");
    qDebug() << QString::fromStdString(drug.name);
    secuared=false;
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

void  MainWindow::on_search_button_p_clicked(){
    std::string search_buffer=ui->search_lineEdit_2->text().toStdString();
    std::vector<patient_t> patientList;
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
    ui->tableWidget->setRowCount(patientList.size());
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
        ui->tableWidget->setItem(i,0,num);
        ui->tableWidget->setItem(i,1,name);
        ui->tableWidget->setItem(i,2,id);
        ui->tableWidget->setItem(i,3,ssn);
        ui->tableWidget->setItem(i,4,phone);
    }
}
