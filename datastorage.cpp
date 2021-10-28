#include "datastorage.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

DataStorage::DataStorage(){
    manager = new QNetworkAccessManager(this);
}

DataStorage* DataStorage::getInstance(){
    if(NULL == instance)
        instance = new DataStorage();
    return instance;
}

patient_t DataStorage::search_one_patient(std::string name){

    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/search_patient.php?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Convert to JSON
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();

    patient_t patient;


    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj     = value.toObject();
        patient.first_name  = obj["first_name"].toString().toStdString();
        patient.middle_name = obj["middle_name"].toString().toStdString();
        patient.last_name   = obj["last_name"].toString().toStdString();
        patient.DOB         = { (uint8_t)obj["month"].toString().toInt(),
                                (uint8_t)obj["day"].toString().toInt(),
                                (uint16_t)obj["year"].toString().toInt()};
        patient.address     = {obj["street"].toString().toStdString(), obj["city"].toString().toStdString(), obj["state"].toString().toStdString(), obj["zip_code"].toString().toStdString()};
        patient.SSN         = obj["ssn"].toString().toStdString();
        patient.phone       = obj["phone"].toString().toStdString();
        patient.valid       = true;
        //TODO: need real prescription return
        patient.prescription.push_back({"Aspirin","31284313231",2,10,(time(0)-3600*24*15)});
        patient.prescription.push_back({"bad Aspirin","31284313333",6,5,time(0)});
        // Return first result only
        return patient;
    }
}

drug_t DataStorage::search_one_drug(std::string name){
    // Search one drug by name

    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/search.php?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Convert to JSON
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();

    drug_t drug;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        drug.name = obj["name"].toString();
        drug.brand = obj["brand"].toString();
        drug.cost = obj["cost"].toString().toDouble();
        drug.price = obj["price"].toString().toDouble();
        drug.control_status = obj["control_status"].toString();
        drug.picture_url = obj["picture_url"].toString();
        drug.UPC = obj["UPC"].toString().toStdString();
        drug.DEA = obj["DEA"].toString().toStdString();
        drug.GPI = obj["GPI"].toString().toStdString();
        drug.NDC = obj["NDC"].toString().toStdString();
        drug.valid = true;
        //TODO: need real amount return;
        drug.amount=5;
        // Return first result only
        return drug;
    }

    return drug;
}

std::vector<patient_t> DataStorage::search_patients(std::string name){
    std::vector<patient_t> result;
    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/search_patient.php?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Convert to JSON
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        patient_t patient;
        QJsonObject obj     = value.toObject();
        patient.first_name  = obj["first_name"].toString().toStdString();
        patient.middle_name = obj["middle_name"].toString().toStdString();
        patient.last_name   = obj["last_name"].toString().toStdString();
        patient.DOB         = { (uint8_t)obj["month"].toString().toInt(),
                                (uint8_t)obj["day"].toString().toInt(),
                                (uint16_t)obj["year"].toString().toInt()};
        patient.address     = {obj["street"].toString().toStdString(), obj["city"].toString().toStdString(), obj["state"].toString().toStdString(), obj["zip_code"].toString().toStdString()};
        patient.SSN         = obj["ssn"].toString().toStdString();
        patient.phone       = obj["phone"].toString().toStdString();
        patient.valid       = true;
        //TODO: need real prescription return
        patient.prescription.push_back({"Aspirin","31284313231",2,10,(time(0)-3600*24*15)});
        patient.prescription.push_back({"bad Aspirin","31284313333",6,5,time(0)});
        // Return first result only
        result.push_back(patient);
    }
    return result;
}

std::vector<drug_t> DataStorage::search_drugs(std::string name){
    // Search drugs by name

    std::vector<drug_t> result;
    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/search.php?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Convert to JSON
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["results"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        drug_t drug;
        QJsonObject obj = value.toObject();
        drug.name = obj["name"].toString();
        drug.brand = obj["brand"].toString();
        drug.cost = obj["cost"].toString().toDouble();
        drug.price = obj["price"].toString().toDouble();
        drug.control_status = obj["control_status"].toString();
        drug.picture_url = obj["picture_url"].toString();
        drug.UPC = obj["UPC"].toString().toStdString();
        drug.DEA = obj["DEA"].toString().toStdString();
        drug.GPI = obj["GPI"].toString().toStdString();
        drug.NDC = obj["NDC"].toString().toStdString();
        drug.valid = true;
        //TODO: need for real amount return
        drug.amount=5;
        // Add result to vector
        result.push_back(drug);
    }

    return result;
}

bool DataStorage::create_new_drug(drug_t drug){
    // TODO: save new drug in DB
    // return true if successfully saved in DB
    return true;
}

bool DataStorage::create_new_patient(patient_t patient){
    // TODO: save new patient in DB
    // return true if successfully saved in DB
    qDebug() << "new patient name" ;
    qDebug()<<patient.first_name.c_str();
    return true;
}

bool DataStorage::add_inventory(drug_t drug, uint16_t n){
    // TODO: add n of drug to current inventory
    return true;
}

bool DataStorage::patient_new_address(patient_t patient, address_t new_address){
    // TODO: update the address of patient to be new_address
    return true;
}
std::string address_t::toString(){
    return street_number+"\n"+city+","+state+","+zip_code;
}

bool prescription_t::getValid(){
    std::time_t x=time(0);
    int diff=std::difftime(x,last_time)/(3600*24);
    return diff>period;
}

