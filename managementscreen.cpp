#include "managementscreen.h"
#include "ui_managementscreen.h"

Managementscreen::Managementscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Managementscreen)
{
    ui->setupUi(this);
    updateDrug = new changedrugwindow(this);
}

Managementscreen::~Managementscreen()
{
    delete ui;
}

void Managementscreen::on_changedruginfoclick_clicked()
{
    drugList.clear();
    std::string search_buffer=ui->editdrug->text().toStdString();
    if(search_buffer.find(' ')!=-1){
        std::vector<std::pair<int,std::string>> searchList;
        int pos=search_buffer.find(' ');
        while (pos>-1) {
            std::string token=search_buffer.substr(0,pos);
            search_buffer=search_buffer.substr(pos+1);
            std::string filed=token.substr(0,token.find(':'));
            searchList.push_back(std::pair<int,std::string>(0,token.substr(token.find(':')+1)));
            pos=search_buffer.find(' ');
        }
        drugList = std::vector<drug_t>();
    }
    else{
        drugList = API->search_drugs(search_buffer);
    }

  /*  for(size_t i=0;i<drugList.size();i++){
        drug_t drug = drugList[i];
        QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(patient.first_name));
        QTableWidgetItem *id = new QTableWidgetItem(QString::fromStdString(std::to_string(patient.DOB.year)+'/'+std::to_string(patient.DOB.month)+'/'+std::to_string(patient.DOB.day)));
        QTableWidgetItem *ssn = new QTableWidgetItem(QString::fromStdString(SSN));
        QTableWidgetItem *phone = new QTableWidgetItem(QString::fromStdString(patient.phone));
        ui->tableWidget->setItem(i+1,0,num);
        ui->tableWidget->setItem(i+1,1,name);
        ui->tableWidget->setItem(i+1,2,id);
        ui->tableWidget->setItem(i+1,3,ssn);
        ui->tableWidget->setItem(i+1,4,phone);
    }*/

    //brings up different drugs
    //seperate page to select drug?
    //the final info goes to updatedrug window

    updateDrug->changename(ui->editdrug->text());
    updateDrug->show();
}


void Managementscreen::on_addnewdrugclicked_clicked()
{
    //search for drug first
    std::string search_buffer=ui->editdrug->text().toStdString();
    //ask if they meant ??? drug (antoehr pop up)
    //if no, move on to creation

    drugList = std::vector<drug_t>();

    //ui->quantiyvalue to int

    API->create_new_drug(drugList.at(0),1);
}

