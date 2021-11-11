#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <string>
#include <vector>
#include <QNetworkAccessManager>
#include <qdebug.h>
#include <time.h>
#include <QDate>

struct address_t{
    // Address data type
    std::string street_number;
    std::string city;
    std::string state;
    std::string zip_code;
    std::string toString();

};

struct date_t{
    // Date data type
    uint8_t     month;
    uint8_t     day;
    uint16_t    year;
};

struct drug_t {
    // Drug data type
    QString name;
    QString brand;
    double  cost;
    double  price;
    QString control_status;
    QString picture_url;
    // Codes

    std::string UPC;    // 12 numeric digits
    std::string DEA;    // 2 letters, 6 numbers, and 1 check digit
    std::string GPI;    // 14-character hierarchical classification
    std::string NDC;    // 10-digit or 11-digit, 3-segment number
    int amount;
    bool valid = false;
    int id;             // Unique id from DB
};

struct prescription_t{
    std::string name;       // Drug name
    std::string UPC;        //or any unique id
    int         amount;
    int         period;     //in weeks or days
    QDate       last_time;
    bool        inCart ;
    bool getValid();
};

struct patient_t{
    // Patient data type
    std::string     first_name;
    std::string     middle_name;
    std::string     last_name;
    address_t   address;
    std::string     phone;
    std::string     SSN;
    date_t      DOB;
    std::vector<prescription_t> prescription;   //
    int id;                                     // Unique patient id from DB
    bool valid = false;
};

struct sales_report{
    double cost = 0;
    double profit = 0;  // profit = price - cost
};

class DataStorage : public QObject
{
protected:
    DataStorage();
public:
    static DataStorage* getInstance();
    // TODO: will add more as required

    // Search functions:
    patient_t search_one_patient(std::string name);             // returns the first patient found by name
    drug_t search_one_drug(std::string name);                   // returns the first drug found by name
    std::vector<patient_t> search_patients(std::string name);   // returns a vector of patients of the resulting search by name
    std::vector<drug_t> search_drugs(std::string name);         // returns a vector of drugs of the resulting search by name
    drug_t search_drug_by_id(int id);                           // returns a drug by id

    // Create functions:
    bool create_new_drug(drug_t drug, int quantity);
    bool create_new_patient(patient_t patient);

    // Update functions:
    bool add_inventory(drug_t drug, uint16_t n);                // Add 'n' of 'drug' to DB (add more to current inventory)
    bool update_patient(patient_t patient);                     // Update an existing patient
    bool update_drug(drug_t drug);                              // Update an existing drug

    // Store specific methods:
    QString get_store_name();
    QString get_store_address();
    int get_store_id();
    void register_a_transaction(drug_t drug, int quantity);
    sales_report get_monthly_report(QDate);
    std::vector<drug_t> get_top_drugs(QDate monthYear);

    // TODO:
    //  1: sprint 3 method on return sales, profits, etc by date and store
private:
    static DataStorage* instance;
    QString host_API = "https://wnewsome.com/POS";
    QNetworkAccessManager *manager;
    // Specific to store
    QString store_name;
    QString store_address;
    int store_id;
};

#endif // DATASTORAGE_H
