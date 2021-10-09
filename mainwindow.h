#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double total = 0;

private:
    Ui::MainWindow *ui;
    QString web_API = "https://wnewsome.com/POS/search.php";

private slots:
    void downloadFinished(QNetworkReply*);
    void on_search_button_clicked();
    void on_items_dropdown_itemClicked(QListWidgetItem *item);
};

class CheckoutAccount{
public:
    CheckoutAccount(){
        total = 0;
        n_items = 0;
    }

    void add_item(double price){
        total += price;
    }

    double get_total(){
        return total;
    }

private:
    double total;
    int n_items;
};

#endif // MAINWINDOW_H
