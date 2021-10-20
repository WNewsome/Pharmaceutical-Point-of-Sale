#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

void MainWindow::searchDrug(QNetworkReply *reply){
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

void MainWindow::on_drugeditsearch_clicked()
{
    //looks up name
    // Connect to web API
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    // Add name of drug as a parameter
    QString searchdrug = ui->searchdrugname->text();
    // Once a response is received it will call searchDrug()
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::searchDrug);
    const QUrl url = QUrl(web_API+"?name="+searchdrug);
    QNetworkRequest request(url);
    man->get(request);
    //brings up screen to update drug
    updateDrug->changename(searchdrug);
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


