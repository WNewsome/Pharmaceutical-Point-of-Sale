#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QTabWidget>
#include "datastorage.h"
#include "patientscreen.h"
#include "salescreen.h"
#include "managementscreen.h"
#include "settingsscreen.h"


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
    SaleScreen* saleScreen;
    Managementscreen* managementScreen;
    Settingsscreen* settingScreen;
    virtual void resizeEvent(QResizeEvent *event);


private slots:
    //void on_search_button_clicked();                            // Main search button in sales tab
    //void on_items_dropdown_itemClicked(QListWidgetItem *item);  // Select an item from search results
    void on_checout_action();
};

#endif // MAINWINDOW_H
