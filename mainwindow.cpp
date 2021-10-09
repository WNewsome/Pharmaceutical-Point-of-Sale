#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

static CheckoutAccount currentAccount;

void MainWindow::downloadFinished(QNetworkReply *reply){

    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();
    int i = 0;
    ui->items_dropdown->setVisible(true);
    ui->items_dropdown->clear();
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
        ui->items_dropdown->setFixedHeight(33*i);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->items_dropdown->setVisible(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_search_button_clicked()
{
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    QString word_to_search = ui->search_lineEdit->text();
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
    const QUrl url = QUrl(web_API+"?name="+word_to_search);
    QNetworkRequest request(url);
    //qDebug() << url.toString();
    man->get(request);
}

void MainWindow::on_items_dropdown_itemClicked(QListWidgetItem *item)
{
    ui->items_dropdown->setVisible(false);
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(item->text());
    ui->items_list->insertItem(0, newItem);
    total += item->data(1).toDouble();
    qDebug() << total;
    ui->items_dropdown->clear();
    ui->total->setText("$ "+QString::number(total));
}

