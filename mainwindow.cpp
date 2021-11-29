#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "settingsscreen.h"

DataStorage* DataStorage::instance;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    patientScreen=new PatientScreen(this);
    saleScreen = new SaleScreen(this);
    managementScreen = new Managementscreen(this);

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 150px; width: 100px; }");
    ui->tabWidget->addTab(saleScreen,QString("Sale").arg(ui->tabWidget->count()+1));
    ui->tabWidget->addTab(patientScreen,QString("Patient").arg(ui->tabWidget->count()+1));
    ui->tabWidget->addTab(managementScreen, QString("Management").arg(ui->tabWidget->count()+1));

    connect(ui->actionCheckout,SIGNAL(triggered()), this, SLOT(on_checout_action()));
    connect(ui->actionClear_cart,SIGNAL(triggered()), patientScreen, SLOT(on_clear_cart_action()));


    connect(ui->actionClear_cart,SIGNAL(triggered()), patientScreen, SLOT(on_clear_cart_action()));  

    ui->tabWidget->setCurrentIndex(0);

    // Set search drug dropdown to invisible
    currentAccount->getInstance();
    // Init API
    API = DataStorage::getInstance();

    // -------------------
    // Data Storage Tests:
    // -------------------
    // TODO: remove these tests
    /*
    // Search for one drug matching word "Tyle*"
    drug_t drug = API->search_one_drug("tyle");
    if(drug.valid){
        qDebug() << "Drug Name: "+ drug.name +" Price: "+QString::number(drug.price);
    }

    // Show results of searching for "Asp*"
    std::vector<drug_t> drugs = API->search_drugs("A");

    for(size_t i = 0; i < drugs.size(); i++){
         qDebug() << "Drug Name: "+ drugs[i].name+" Quantity: "+QString::number(drugs[i].amount);
    }
    // Search for one patient by first name
    patient_t patient = API->search_one_patient("James");
    if(patient.valid){
        qDebug() << QString::fromStdString( patient.first_name + " " + patient.last_name);
        qDebug() << QString::fromStdString(patient.address.street_number+", "+patient.address.city+ ", "+ patient.address.state);
    }
    */
    // Create a new drug and 32 units in inventory

  //  drug_t new_drug;
   // new_drug.name = "this is a new drug";

 /*   drug_t new_drug;
    new_drug.name = "Atorvastatin";

    new_drug.brand = "Lipitor";
    new_drug.cost = 3;
    new_drug.price = 40.05;
    new_drug.control_status = "N/a";
    new_drug.picture_url = "";
    new_drug.UPC = "305913775190";
    new_drug.DEA = "";
    new_drug.GPI = "39400010100310";
    new_drug.NDC = "0378451393";

    API->create_new_drug(new_drug, 50);

    new_drug.name = "Levothyroxine";

    new_drug.brand = "Levothroid";
    new_drug.cost = 5;
    new_drug.price = 15.42;
    new_drug.control_status = "N/a";
    new_drug.picture_url = "";
    new_drug.UPC = "305271345011";
    new_drug.DEA = "";
    new_drug.GPI = "9664508400";
    new_drug.NDC = "7133516371";

    API->create_new_drug(new_drug, 30);

    new_drug.name = "Lisinopril";

    new_drug.brand = "Prinivil";
    new_drug.cost = 3;
    new_drug.price = 15;
    new_drug.control_status = "N/a";
    new_drug.picture_url = "";
    new_drug.UPC = "368180519010";
    new_drug.DEA = "";
    new_drug.GPI = "3610003000";
    new_drug.NDC = "68180051901";

    API->create_new_drug(new_drug, 20);

    new_drug.name = "Metformin";

    new_drug.brand = "Fortamet";
    new_drug.cost = 0.5;
    new_drug.price = 7;
    new_drug.control_status = "N/a";
    new_drug.picture_url = "";
    new_drug.UPC = "461555160005";
    new_drug.DEA = "";
    new_drug.GPI = "2725005000";
    new_drug.NDC = "62037057110";

    API->create_new_drug(new_drug, 30);

    new_drug.name = "Dextroamphetamine";

    new_drug.brand = "Adderall";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "II";
    new_drug.picture_url = "";
    new_drug.UPC = "354092381012";
    new_drug.DEA = "1100";
    new_drug.GPI = "123456777";
    new_drug.NDC = "5409238301";

    API->create_new_drug(new_drug, 10);

    new_drug.name = "Aspirin123";

    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    API->create_new_drug(new_drug, 10);

    new_drug.name = "Aspirin123";

    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    API->create_new_drug(new_drug, 10);

    new_drug.name = "Aspirin123";

    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    API->create_new_drug(new_drug, 10);

    new_drug.name = "Aspirin123";

    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    API->create_new_drug(new_drug, 10);

    new_drug.name = "Aspirin123";

    new_drug.brand = "This is its brand";
    new_drug.cost = 8;
    new_drug.price = 12;
    new_drug.control_status = "AWEF";
    new_drug.picture_url = "";
    new_drug.UPC = "12345";
    new_drug.DEA = "123444";
    new_drug.GPI = "123456777";
    new_drug.NDC = "12jj";

    API->create_new_drug(new_drug, 10);*/
  /*  drug_t to_update = API->search_one_drug("Aspirin123");
    to_update.name = "UPDATEDNAMETEST";
    to_update.brand = "UPDATED_BRAND";
    //API->update_drug(to_update);
    // Test create a new patient into the DB
    patient_t new_patient;
    new_patient.first_name = "Willy";
    new_patient.last_name = "Wonka";
    new_patient.middle_name = "john";
    new_patient.address.street_number = "111 Pensilvania Ave.";
    new_patient.address.city = "Washington D.C.";
    new_patient.address.state = "D.C.";
    new_patient.address.zip_code = "23333";
    new_patient.phone = "5404441122";
    new_patient.SSN = "123654789";
    new_patient.DOB.day = 12;
    new_patient.DOB.month = 11;

    new_patient.DOB.year = 1997;*/

    //API->create_new_patient(new_patient);
   // patient = API->search_one_patient("Berth");
   // patient.first_name = "Berthoooo";
  //  API->update_patient(patient);

   /* new_patient.DOB.year = 1997;
    API->create_new_patient(new_patient);
    patient = API->search_one_patient("Berth");
    patient.first_name = "Berthoooo";
    API->update_patient(patient);
    drug_t searchID = API->search_drug_by_id(41);
    if(searchID.valid)
        qDebug() << searchID.name;

    patient_t patient = API->search_one_patient("Alex");
    patient.first_name = "Alex2TEST";
    API->update_patient(patient);
    API->create_new_patient(patient);
    // Regiter a transaction


    drug_t drug = API->search_drug_by_id(49);
    API->register_a_transaction(drug, 1);
    // How to access the report functions
    QDate nov21;
    nov21.setDate(2021,11,1); // Dont really care about day
    API->get_monthly_report(nov21);
    API->get_top_drugs(nov21);

    */
    if(!API->creat_store_table()){
       qDebug()<<"unable to creat table";
       close();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checout_action(){
    Checkout* checkout=new Checkout(this);
    checkout->setWindowFlag(Qt::SubWindow);
    connect(checkout,SIGNAL(clearCart()),patientScreen,SLOT(on_accept_checkout()));
    connect(checkout,SIGNAL(clearCart()),saleScreen,SLOT(on_clear()));
    checkout->show();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    qDebug()<<event->size();
    QMainWindow::resizeEvent(event);
    QSize size=event->size();
    size.setHeight(size.height()-15);
    size.setWidth(size.width()-8);
    patientScreen->resize(size);
    saleScreen->resize(size);
    managementScreen->resize(size);
    size.setHeight(size.height()+5);
    size.setWidth(size.width()+5);
    ui->tabWidget->resize(size);
}

