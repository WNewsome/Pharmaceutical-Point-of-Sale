#include "datastorage.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

DataStorage::DataStorage()
{
    manager = new QNetworkAccessManager(this);
}

patient_t DataStorage::search_one_patient(std::string name){
    // TODO: Returning a fake result for now
    patient_t patient;
    patient.first_name  = "Jim";
    patient.last_name   = "Halpert";
    patient.DOB         = {10, 1, 1978};
    patient.address     = {"1725 Slough Avenue", "Scranton", "PA", "18540"};
    patient.SSN         = "123456890";
    patient.phone       = "1234567890";

    return patient;
}

drug_t DataStorage::search_one_drug(std::string name){
    // Search one drug by name
    // TODO:
    //  What to return when a drug is not found?
    //  Price/Cost convertion not working

    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we receive a response
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
        drug.cost = obj["cost"].toDouble();
        drug.price = obj["price"].toDouble();
        drug.control_status = obj["control_status"].toString();
        drug.picture_url = obj["picture_url"].toString();
        drug.UPC = obj["UPC"].toString();
        drug.DEA = obj["DEA"].toString();
        drug.GPI = obj["GPI"].toString();
        drug.NDC = obj["NDC"].toString();
        // Return first result only
        return drug;
    }
}

std::vector<patient_t> DataStorage::search_patients(std::string name){
    // TODO: returns 2 fake results for now
    std::vector<patient_t> result;
    result.push_back(search_one_patient(""));
    result.push_back(search_one_patient(""));
    return result;
}

std::vector<drug_t> DataStorage::search_drugs(std::string name){
    // Search drugs by name
    // TODO:
    //  What to return when a drug is not found?
    //  Price/Cost convertion not working

    std::vector<drug_t> result;
    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"?name="+word_to_search);

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we receive a response
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
        drug.cost = obj["cost"].toDouble();
        drug.price = obj["price"].toDouble();
        drug.control_status = obj["control_status"].toString();
        drug.picture_url = obj["picture_url"].toString();
        drug.UPC = obj["UPC"].toString();
        drug.DEA = obj["DEA"].toString();
        drug.GPI = obj["GPI"].toString();
        drug.NDC = obj["NDC"].toString();
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

