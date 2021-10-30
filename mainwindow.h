#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QTabWidget>
#include "datastorage.h"
#include "changedrugwindow.h"
#include "patientscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CheckoutAccount* currentAccount;

private:
    // Main User Interface
    Ui::MainWindow *ui;
    // Web API used to obtain drug, patients, and inventory data
    QString web_API = "https://wnewsome.com/POS/search.php";
    DataStorage *API;
    PatientScreen* patientScreen;

private slots:
    void searchDrug(QNetworkReply*);                            // Function that calls the API to obtain data
    void on_search_button_clicked();                            // Main search button in sales tab
    void on_items_dropdown_itemClicked(QListWidgetItem *item);  // Select an item from search results
    void on_checout_action();
};

#endif // MAINWINDOW_H
