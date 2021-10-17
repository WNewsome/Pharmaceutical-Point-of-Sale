#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <string>
#include <vector>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QMainWindow>

struct address_t{
    // Address data type
    QString street_number;
    QString city;
    QString state;
    QString zip_code;
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
    QString UPC;    // 12 numeric digits
    QString DEA;    // 2 letters, 6 numbers, and 1 check digit
    QString GPI;    // 14-character hierarchical classification
    QString NDC;    // 10-digit or 11-digit, 3-segment number

    bool valid = false;
};

struct patient_t{
    // Patient data type
    QString     first_name;
    QString     middle_name;
    QString     last_name;
    address_t   address;
    QString     phone;
    QString     SSN;
    date_t      DOB;

    bool valid = false;
};

class DataStorage : public QObject
{
protected:
    DataStorage();
public:
    static DataStorage* getInstance();
    // TODO: will add more as required

    // Search functions:
    patient_t search_one_patient(std::string name); // returns the first patient found by name
    drug_t search_one_drug(std::string name);       // returns the first drug found by name
    std::vector<patient_t> search_patients(std::string name); // returns a vector of patients of the resulting search by name
    std::vector<drug_t> search_drugs(std::string name); // returns a vector of drugs of the resulting search by name

    // Create functions:
    bool create_new_drug(drug_t drug);
    bool create_new_patient(patient_t patient);

    // Update functions:
    bool add_inventory(drug_t drug, uint16_t n); // Add 'n' of 'drug' to DB (add more to current inventory)
    bool patient_new_address(patient_t patient, address_t new_address); // Update the address of an existing patient

private:
    static DataStorage* instance;
    QString host_API = "https://wnewsome.com/POS";
    QNetworkAccessManager *manager;
};

#endif // DATASTORAGE_H
