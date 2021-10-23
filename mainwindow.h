#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QTabWidget>
#include "changedrugwindow.h"
#include "datastorage.h"
#include "dialog.h"

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
    DataStorage *API;
    changedrugwindow *updateDrug;
    bool secuared;
    std::vector<patient_t> patientList;

private slots:
    void searchDrug(QNetworkReply*);                            // Function that calls the API to obtain data
    void on_search_button_clicked();                            // Main search button in sales tab
    void on_pushButton_5_clicked();
    void on_items_dropdown_itemClicked(QListWidgetItem *item);  // Select an item from search results
    void on_search_button_p_clicked();                            // Main search button in patient tab
    void on_search_table_p_clicked(int,int);
    void on_correct_ssn(patient_t);
    void on_clear_p_clicked();
    void on_new_p_clicked();
};

#endif // MAINWINDOW_H
