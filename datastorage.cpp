#include "datastorage.h"

DataStorage::DataStorage()
{

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
    // TODO: simulates a result for now
    drug_t drug;
    drug.name = "NyQuil SEVERE Cough Cold and Flu Nighttime Relief Berry Flavor Liquid";
    drug.brand = "Vicks";
    drug.cost = 8.99;
    drug.price = 13.49;
    drug.control_status = "";
    drug.picture_url = "https://www.cvs.com/bizcontent/merchandising/productimages/large/323900038141.jpg";
    drug.UPC = "323900038158";
    drug.DEA = "AB1234560";
    drug.GPI = "ABCDEFGHIJKLMN";
    drug.NDC = "3700051812";

    return drug;
}

std::vector<patient_t> DataStorage::search_patients(std::string name){
    // TODO: returns 2 fake results for now
    std::vector<patient_t> result;
    result.push_back(search_one_patient(""));
    result.push_back(search_one_patient(""));
    return result;
}

std::vector<drug_t> DataStorage::search_drugs(std::string name){
    // TODO: returns 3 fake results for now
    std::vector<drug_t> result;
    result.push_back(search_one_drug(""));
    result.push_back(search_one_drug(""));
    result.push_back(search_one_drug(""));
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

