#include "settingsscreen.h"
#include "ui_settingsscreen.h"

Settingsscreen::Settingsscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settingsscreen){
    ui->setupUi(this);
    API = DataStorage::getInstance();
    loadSettings();
}

Settingsscreen::~Settingsscreen(){
    delete ui;
}

void Settingsscreen::loadSettings(){
    // Ask data storage class for current settings
    address_t thisStore = API->get_store_address();
    ui->Company_name_label->setText(API->get_store_name());
    ui->storeStreet->setText(QString::fromStdString(thisStore.street_number));
    ui->storeCity->setText(QString::fromStdString(thisStore.city));
    ui->storeState->setText(QString::fromStdString(thisStore.state));
    ui->storeZIP->setText(QString::fromStdString(thisStore.zip_code));
    toggle_enable_settings(false);
}

void Settingsscreen::on_EdditSettings_clicked(){
    if(ui->Company_name_label->isEnabled()){
        toggle_enable_settings(false);
        // Save current info in dataStorage class
        address_t newAddress;
        newAddress.street_number = ui->storeStreet->text().toStdString();
        newAddress.city = ui->storeCity->text().toStdString();
        newAddress.state = ui->storeState->text().toStdString();
        newAddress.zip_code = ui->storeZIP->text().toStdString();
        std::string newName = ui->Company_name_label->text().toStdString();
        if(API->save_local_address(newAddress, newName)){
            loadSettings();
        }
        ui->EdditSettings->setText("Edit Info");
    } else {
        toggle_enable_settings(true);
        ui->EdditSettings->setText("Save Info");
    }
}

void Settingsscreen::toggle_enable_settings(bool enabled){
    ui->Company_name_label->setEnabled(enabled);
    ui->storeStreet->setEnabled(enabled);
    ui->storeCity->setEnabled(enabled);
    ui->storeState->setEnabled(enabled);
    ui->storeZIP->setEnabled(enabled);
    ui->Company_name_label->setEnabled(enabled);
}
