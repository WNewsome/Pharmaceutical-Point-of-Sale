#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

void MainWindow::downloadFinished(QNetworkReply *reply){

    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();
    int i = 0;
    ui->items_list->clear();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString price = obj["price"].toString();
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(name+" $"+price);
        ui->items_list->insertItem(i, newItem);
        i++;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

