#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <string>
#include <vector>
#include <qdebug.h>

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
    std::string name;
    std::string brand;
    double      cost;
    double      price;
    std::string control_status;
    std::string picture_url;
    // Codes
    std::string UPC;    // 12 numeric digits
    std::string DEA;    // 2 letters, 6 numbers, and 1 check digit
    std::string GPI;    // 14-character hierarchical classification
    std::string NDC;    // 10-digit or 11-digit, 3-segment number
};

struct prescription_t{
    std::string name;
    std::string UPC;//or any unique id
    int         amount;
    int         period;//in weeks or days
    date_t      last_time;
};

struct patient_t{
    // Patient data type
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    address_t   address;
    std::string phone;
    std::string SSN;
    date_t      DOB;
    //vector<prescription_t> prescription
};

class DataStorage
{
public:
    DataStorage();
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

};

#endif // DATASTORAGE_H
