#include "datastorage.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>

DataStorage::DataStorage(){
    // Read and load store settings
    load_local_info();
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
            prescription_t prescription;
            prescription.name = obj2["name"].toString().toStdString();
            prescription.UPC = obj2["UPC"].toString().toStdString();
            prescription.amount = obj2["amount"].toString().toInt();
            prescription.period = obj2["period"].toString().toInt();
            prescription.last_time = QDate::fromString(obj2["last_time"].toString(), "ddMMyyyy");
            patient.prescription.push_back(prescription);
        }
        // Return first result only
        return patient;
    }

    // No patient found
    qDebug() << "ERROR: No patient found";
    return patient;
}

drug_t DataStorage::search_one_drug(std::string name){
    // Search one drug by name

    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/new_search_drugs.php?name="+word_to_search+"&storeid="+QString::number(get_store_id()));

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
        drug.id = obj["id"].toString().toInt();
        // Return first result only
        return drug;
    }

    // No drug found
    qDebug() << "ERROR: No drug found";
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
        QString str = obj["prescription"].toString();
        QJsonDocument doc=QJsonDocument::fromJson(str.toUtf8());
        QJsonObject obj2 = doc.object();
        QJsonArray arr= obj2["prescription"].toArray();
        foreach (const QJsonValue & value, arr) {
            // Go over every prescription and add it to the patient
            QJsonObject obj2     = value.toObject();
            prescription_t prescription;
            prescription.name = obj2["name"].toString().toStdString();
            prescription.UPC = obj2["UPC"].toString().toStdString();
            prescription.amount = obj2["amount"].toString().toInt();
            prescription.period = obj2["period"].toString().toInt();
            prescription.last_time = QDate::fromString(obj2["last_time"].toString(), "ddMMyyyy");

            patient.prescription.push_back(prescription);
        }
        // Return first result only
        result.push_back(patient);
    }

    if(0 == result.size())
        qDebug() << "ERROR: No patients found";

    return result;
}

std::vector<drug_t> DataStorage::search_drugs(std::string name){
    // Search drugs by name for local store only
    return search_drugs_remotelly(get_store_id(), name);
}
std::vector<drug_t> DataStorage::search_drugs_in_all(std::string name){
    std::vector<drug_t> result;
    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/new_search_drugs.php?name="+word_to_search);

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
        drug.id = obj["id"].toString().toInt();
        // Add result to vector
        result.push_back(drug);
    }

    if(0 == result.size())
        qDebug() << "ERROR: No drugs found at database";

    return result;
}
std::vector<drug_t> DataStorage::search_drugs_remotelly(int storeID, std::string name){
    // Search drugs by name in store with id storeID

    std::vector<drug_t> result;
    QString word_to_search = QString::fromStdString(name);
    const QUrl url = QUrl(host_API+"/new_search_drugs.php?name="+word_to_search+"&storeid="+QString::number(storeID));

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
        drug.id = obj["id"].toString().toInt();
        // Add result to vector
        result.push_back(drug);
    }

    if(0 == result.size())
        qDebug() << "ERROR: No drugs found at store with id "+QString::number(storeID);

    return result;
}

drug_t DataStorage::search_drug_by_id(int id){
    drug_t drug;
    const QUrl url = QUrl(host_API+"/new_search_drug_by_id.php?id="+QString::number(id)+"&storeid="+QString::number(get_store_id()));

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
        drug.id = obj["id"].toString().toInt();
        // Return first result only
        return drug;
    }

    // No drug found
    qDebug() << "ERROR: No drug found " + QString::number(id);

    return drug;
}

bool DataStorage::create_new_drug(drug_t drug, int quantity){
    // Save new drug in DB
    const QUrl url = QUrl(host_API+"/new_create_new_drug.php?name="+drug.name+"&brand="+drug.brand
                          +"&cost="+QString::number(drug.cost)
                          +"&price="+QString::number(drug.price)
                          +"&control_status="+drug.control_status
                          +"&picture_url="+drug.picture_url
                          +"&quantity="+QString::number(quantity)
                          +"&UPC="+QString::fromStdString(drug.UPC)
                          +"&DEA="+QString::fromStdString(drug.DEA)
                          +"&GPI="+QString::fromStdString(drug.GPI)
                          +"&NDC="+QString::fromStdString(drug.NDC)
                          +"&storeid="+QString::number(get_store_id()));

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString strReply = (QString)reply->readAll();

    if(strReply == "200 Ok"){
        return true;
    }
    qDebug() << "ERROR: "+strReply;
    return false;
}

bool DataStorage::create_new_patient(patient_t patient){

    std::string prescription = "{\"prescription\":[";
    for(size_t n = 0; n < patient.prescription.size(); n++){
        prescription = prescription+"{\"name\":\""+patient.prescription[n].name+"\",";
        prescription = prescription+"\"UPC\":\""+patient.prescription[n].UPC+"\",";
        prescription = prescription+"\"amount\":\""+std::to_string(patient.prescription[n].amount)+"\",";
        prescription = prescription+"\"last_time\":\""+patient.prescription[n].last_time.toString("ddMMyyyy").toStdString()+"\",";
        prescription = prescription+"\"period\":\""+std::to_string(patient.prescription[n].period)+"\"}";
        if(n < patient.prescription.size()-1)
            prescription += ",";
    }
    prescription += "]}";

    // Store a new patient in the DB and assign a unique ID
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
                          +"&year="+QString::number(patient.DOB.year)
                          +"&prescription="+QString::fromStdString(prescription));

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString strReply = (QString)reply->readAll();

    if(strReply == "200 Ok"){
        return true;
    }
    qDebug() << "ERROR: "+strReply;
    return false;
}

bool DataStorage::add_inventory(drug_t drug, uint16_t n){
    // Add n of drug to current inventory
    drug.amount += n;
    return update_drug(drug);
}

bool DataStorage::update_patient(patient_t patient){
    // Update an existing patinent in the DB by its unique id

    std::string prescription = "{\"prescription\":[";
    for(size_t n = 0; n < patient.prescription.size(); n++){
        prescription = prescription+"{\"name\":\""+patient.prescription[n].name+"\",";
        prescription = prescription+"\"UPC\":\""+patient.prescription[n].UPC+"\",";
        prescription = prescription+"\"amount\":\""+std::to_string(patient.prescription[n].amount)+"\",";
        prescription = prescription+"\"last_time\":\""+patient.prescription[n].last_time.toString("ddMMyyyy").toStdString()+"\",";
        prescription = prescription+"\"period\":\""+std::to_string(patient.prescription[n].period)+"\"}";
        if(n < patient.prescription.size()-1)
            prescription += ",";
    }
    prescription += "]}";

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
                          +"&id="+QString::number(patient.id)
                          +"&prescription="+QString::fromStdString(prescription));

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString strReply = (QString)reply->readAll();

    if(strReply == "200 Ok"){
        return true;
    }
    qDebug() << "ERROR: "+strReply;
    return false;
}

bool DataStorage::update_drug(drug_t drug){
    const QUrl url = QUrl(host_API+"/new_update_drug.php?name="+drug.name+"&brand="+drug.brand
                          +"&storeid="+QString::number(get_store_id())
                          +"&cost="+QString::number(drug.cost)
                          +"&price="+QString::number(drug.price)
                          +"&control_status="+drug.control_status
                          +"&picture_url="+drug.picture_url
                          +"&quantity="+QString::number(drug.amount)
                          +"&UPC="+QString::fromStdString(drug.UPC)
                          +"&DEA="+QString::fromStdString(drug.DEA)
                          +"&GPI="+QString::fromStdString(drug.GPI)
                          +"&NDC="+QString::fromStdString(drug.NDC)
                          +"&id="+QString::number(drug.id));

    // Request url by GET
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QString strReply = (QString)reply->readAll();

    if(strReply == "200 Ok"){
        return true;
    }
    qDebug() << "ERROR: "+strReply;
    return false;
}

QString DataStorage::get_store_name(){
    return store_name;
}

address_t DataStorage::get_store_address(){
    return store_address;
}

std::string address_t::toString(){
    return street_number+"\n"+city+","+state+","+zip_code;
}

bool prescription_t::getValid(){
    // Validate that we can prescribe the drug to the patient
    int diff=last_time.daysTo(QDate::currentDate());

    return diff>=period;
}

int DataStorage::get_store_id(){
    // Returns the store id stored in local file
    return store_id;
}

void DataStorage::register_a_transaction(drug_t drug, int quantity){
    // This method should be called for EVERY item being sold

    // Reduce quantity in inventory
    drug.amount -= quantity;
    update_drug(drug);

    // Store transaction locally
    // Format: store id, drug id, cost, profit, quantity sold
    QString today = QDateTime::currentDateTime().toString("MMMM_yyyy");
    today += ".txt";

    std::string filename(today.toStdString());
    std::ofstream file_out;
    file_out.open(filename, std::ios_base::app);
    file_out << get_store_id() << ",";
    file_out << drug.id << ",";
    file_out << drug.cost << ",";
    file_out << drug.price - drug.cost << ",";
    file_out << quantity;
    file_out << std::endl;
}

std::vector<drug_t> DataStorage::get_top_drugs(QDate monthYear){
    // Returns a vector of all drugs sorted by quantity sold
    // where index 0 is the most sold drug

    std::vector<drug_t> topDrugs;
    // monthYear is the corresponding month in which a report will be calculated
    QLocale locale=QLocale::English;
    QString file = locale.toString(monthYear,"MMMM_yyyy");
    file += ".txt";
    int i = 0;
    //   map<drug ID, quantity>
    std::map<int, int> drugs;
    std::string line, colname;
    std::ifstream myFile(file.toStdString());
    int currentDrugId;

    if(myFile.good()){
        // Read every line string
        while(std::getline(myFile, line, ',')){

            switch(i){
            case 1:
                // Checking drug ID
                currentDrugId = stoi(line);
                //drugs[stoi(line)]++;
                break;
            case 4:
                // TODO: Checking quantity
                drugs[currentDrugId]+=stoi(line);
                break;
            }

            if(i == 4)
                i = 0;
            i++;
        }
    } else {
        qDebug() << "No report available for "+monthYear.toString("MMMM yyyy");
    }
    int max = 0;
    int id = 0;
    size_t drugsSize = drugs.size();
    for(size_t n = 0; n < drugsSize; n++) {
        for(auto const & d: drugs) {
            // O(n^2) | n is the number of different drugs sold
            if(d.second > max){
                max = d.second;
                id = d.first;
            }
        }
        drug_t current = search_drug_by_id(id);
        current.amount = max;
        topDrugs.push_back(current);
        std::map<int,int>::iterator it = drugs.find(id);
        drugs.erase(it);
        max = 0;
    }
    return topDrugs;
}

sales_report DataStorage::get_monthly_report(QDate monthYear){
    // monthYear is the corresponding month in which a report will be calculated
    sales_report report;
    QLocale locale=QLocale::English;
    QString file = locale.toString(monthYear,"MMMM_yyyy");
    file += ".txt";
    int i = 0;
    std::string line, colname;
    std::ifstream myFile(file.toStdString());
    if(myFile.good()){
        // Read every line string
        while(std::getline(myFile, line, ',')){
            if(i == 4)
                i =0;
            switch(i){
            case 2:
                // Checking cost
                report.cost +=  std::stod(line);
                break;
            case 3:
                // Checking profit
                report.profit += std::stod(line);
                break;
            }
            i++;
        }
    } else {
        qDebug() << "No report available for "+monthYear.toString("MMMM yyyy");
    }

    return report;
}

void DataStorage::load_local_info(){
    std::string file = "assets/store_settings.txt";
    std::string line, colname;
    std::ifstream myFile(file);
    int i = 0;
    bool remote=false;
    if(myFile.good()){
        // Read every line string
        int id;
        QString name;
        address_t address;
        while(std::getline(myFile, line)){
            if(!remote){
            switch(i){
            case 0:
                store_name = QString::fromStdString(line);
                break;
            case 1:
                store_address.street_number = line;
                break;
            case 2:
                store_address.city = line;
                break;
            case 3:
                store_address.state = line;
                break;
            case 4:
                store_address.zip_code = line;
                break;
            case 5:
                store_id = std::stoi(line);
                i=-1;
                remote=true;
                break;
            }
            }
            else{
                switch(i){
                case 0:
                    name = QString::fromStdString(line);
                    break;
                case 1:
                    address.street_number = line;
                    break;
                case 2:
                    address.city = line;
                    break;
                case 3:
                    address.state = line;
                    break;
                case 4:
                    address.zip_code = line;
                    break;
                case 5:
                    id = std::stoi(line);
                    i=-1;
                    near_by_store.push_back(std::make_tuple(id,address,name));
                    break;

            }
            }
            i++;

    }
        //creat_store_table();
    } else {
        qDebug() << "Local settings file not available";
    }
}

bool DataStorage::save_local_address(address_t newAddress, std::string companyName ,QString nearby){

    std::string settingsFile("assets/store_settings.txt");
    //std::ifstream myFile(settingsFile);
    //if(myFile.good()){
        std::ofstream file_out;
        file_out.open(settingsFile, std::ofstream::trunc);
        file_out << companyName;
        file_out << std::endl;
        file_out << newAddress.street_number;
        file_out << std::endl;
        file_out << newAddress.city;
        file_out << std::endl;
        file_out << newAddress.state;
        file_out << std::endl;
        file_out << newAddress.zip_code;
        file_out << std::endl;
        file_out << get_store_id();
        file_out << std::endl;
        file_out << nearby.toStdString()<<std::endl;
        file_out.close();
        load_local_info();
        return true;
    //}
    qDebug() << "File store_settings.txt does not exist.";
    return false;
}

bool DataStorage::creat_store_table(){
    const QUrl url = QUrl(host_API+"/create_new_store.php?storeid="+QString::number(store_id));
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    // Wait until we received a response
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QString strReply = (QString)reply->readAll();

    if((strReply == "created") || (strReply == "exist")){
        return true;
    }

    qDebug() << "ERROR: "+strReply;
    return false;
}
std::vector<std::tuple<int,address_t,QString>> DataStorage::get_near_by_store(){
    return near_by_store;
}
