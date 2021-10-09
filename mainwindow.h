#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CheckoutAccount{
public:
    // This class keeps track of the main sales screen state
    CheckoutAccount(){
        // Constructor sets everything to 0
        total = 0;
        n_items = 0;
    }

    void add_item(double price){
        // Just update total for now
        total += price;
    }

    double get_total(){
        return total;
    }

private:
    double total;
    int n_items;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CheckoutAccount currentAccount;

private:
    // Main User Interface
    Ui::MainWindow *ui;
    // Web API used to obtain drug, patients, and inventory data
    QString web_API = "https://wnewsome.com/POS/search.php";

private slots:
    void searchDrug(QNetworkReply*);                            // Function that calls the API to obtain data
    void on_search_button_clicked();                            // Main search button in sales tab
    void on_items_dropdown_itemClicked(QListWidgetItem *item);  // Select an item from search results
};

#endif // MAINWINDOW_H
