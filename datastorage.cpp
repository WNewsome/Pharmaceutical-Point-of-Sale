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
        patient.id          = (uint8_t)obj["id"].toString().toInt();

        // Prescription
        QString str= obj["prescription"].toString();
        QJsonDocument doc=QJsonDocument::fromJson(str.toUtf8());
        QJsonObject obj2 = doc.object();
        QJsonArray arr= obj2["prescription"].toArray();
        foreach (const QJsonValue & value, arr) {
            // Go over every prescription and add it to the patient
            QJsonObject obj2     = value.toObject();
            std::string med_name = obj2["name"].toString().toStdString();
            std::string med_UPC = obj2["UPC"].toString().toStdString();
            int med_amount = obj2["amount"].toString().toInt();
            int med_period = obj2["period"].toString().toInt();
            patient.prescription.push_back({med_name,med_UPC,med_amount,med_period,(time(0)-3600*24*15)});
        }
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
        drug.amount = obj["quantity"].toString().toInt();
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
        patient.id          = (uint8_t)obj["id"].toString().toInt();
        // Prescription
        //QString str= "{\"firstname\":\"James\",\"middlename\":\"\",\"lastname\":\"Smith\",\"prescription\":[{\"name\":\"ssasprin\"},{\"name\":\"sbad asprin\"}]}";
        QString str = obj["prescription"].toString();
        qDebug() << "here";
        qDebug() << str;
        QJsonDocument doc=QJsonDocument::fromJson(str.toUtf8());
        QJsonObject obj2 = doc.object();
        QJsonArray arr= obj2["prescription"].toArray();
        foreach (const QJsonValue & value, arr) {
            // Go over every prescription and add it to the patient
            QJsonObject obj2     = value.toObject();
            std::string med_name = obj2["name"].toString().toStdString();
            std::string med_UPC = obj2["UPC"].toString().toStdString();
            int med_amount = obj2["amount"].toString().toInt();
            int med_period = obj2["period"].toString().toInt();
            patient.prescription.push_back({med_name,med_UPC,med_amount,med_period,(time(0)-3600*24*15)});
        }
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

        drug.amount = obj["quantity"].toString().toInt();
        drug.UPC = obj["UPC"].toString().toStdString();
        drug.DEA = obj["DEA"].toString().toStdString();
        drug.GPI = obj["GPI"].toString().toStdString();
        drug.NDC = obj["NDC"].toString().toStdString();
        drug.valid = true;
        drug.amount = obj["quantity"].toString().toInt();
        // Add result to vector
        result.push_back(drug);
    }

    return result;
}

bool DataStorage::create_new_drug(drug_t drug, int quantity){
    // Save new drug in DB
    // TODO: return true if successfully saved in DB
    const QUrl url = QUrl(host_API+"/create_new_drug.php?name="+drug.name+"&brand="+drug.brand
                          +"&cost="+QString::number(drug.cost)
                          +"&price="+QString::number(drug.price)
                          +"&control_status="+drug.control_status
                          +"&picture_url="+drug.picture_url
                          +"&quantity="+QString::number(quantity)
                          +"&UPC="+QString::fromStdString(drug.UPC)
                          +"&DEA="+QString::fromStdString(drug.DEA)
                          +"&GPI="+QString::fromStdString(drug.GPI)
                          +"&NDC="+QString::fromStdString(drug.NDC));
    qDebug() << url;
    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return true;
}

bool DataStorage::create_new_patient(patient_t patient){
    // TODO: return true if successfully saved in DB
    const QUrl url = QUrl(host_API+QString::fromStdString("/create_new_patient.php?first_name="+patient.first_name
                          +"&middle_name="+patient.middle_name
                          +"&last_name="+patient.last_name
                          +"&street_number="+patient.address.street_number
                          +"&city="+patient.address.city
                          +"&state="+patient.address.state
                          +"&zip_code="+patient.address.zip_code
                          +"&phone="+patient.phone
                          +"&SSN="+patient.SSN)
                          +"&month="+QString::number(patient.DOB.month)
                          +"&day="+QString::number(patient.DOB.day)
                          +"&year="+QString::number(patient.DOB.year));
    qDebug() << url;
    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return true;
}

bool DataStorage::add_inventory(drug_t drug, uint16_t n){
    // TODO: add n of drug to current inventory
    return true;
}

bool DataStorage::update_patient(patient_t patient){
    // TODO: return true if successfully saved in DB
    const QUrl url = QUrl(host_API+QString::fromStdString("/update_patient.php?first_name="+patient.first_name
                          +"&middle_name="+patient.middle_name
                          +"&last_name="+patient.last_name
                          +"&street_number="+patient.address.street_number
                          +"&city="+patient.address.city
                          +"&state="+patient.address.state
                          +"&zip_code="+patient.address.zip_code
                          +"&phone="+patient.phone
                          +"&SSN="+patient.SSN)
                          +"&month="+QString::number(patient.DOB.month)
                          +"&day="+QString::number(patient.DOB.day)
                          +"&year="+QString::number(patient.DOB.year)
                          +"&id="+QString::number(patient.id));
    qDebug() << url;
    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return true;
}
std::string address_t::toString(){
    return street_number+"\n"+city+","+state+","+zip_code;
}

bool prescription_t::getValid(){
    // Validate that we can prescribe the drug to the patient
    int diff=last_time.daysTo(QDate::currentDate());

    return diff>=period;
}

