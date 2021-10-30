#include "patientscreen.h"
#include "ui_patientscreen.h"
CheckoutAccount* CheckoutAccount::instance;
PatientScreen::PatientScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patientScreen)
{
    slotcount=0;
    ui->setupUi(this);
    connect(ui->search_button_2, SIGNAL(clicked()), this, SLOT(on_search_button_p_clicked()));
    connect(ui->clear_button, SIGNAL(clicked()), this, SLOT(on_clear_p_clicked()));
    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(on_new_p_clicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_search_table_p_clicked(int,int)));
    connect(ui->checkout_button,SIGNAL(clicked()), this, SLOT(on_checkout_p_clicked()));
    API = DataStorage::getInstance();
    currentAccount = CheckoutAccount::getInstance();
}

PatientScreen::~PatientScreen()
{
    delete ui;
}

void  PatientScreen::on_search_button_p_clicked(){
    ui->tableWidget->setRowCount(1);
    patientList.clear();
    std::string search_buffer=ui->search_lineEdit_2->text().toStdString();
    if(search_buffer.find(' ')!=-1){
        std::vector<std::pair<int,std::string>> searchList;
        int pos=search_buffer.find(' ');
        while (pos>-1) {
            std::string token=search_buffer.substr(0,pos);
            search_buffer=search_buffer.substr(pos+1);
            std::string filed=token.substr(0,token.find(':'));
            if(filed=="name")
                searchList.push_back(std::pair<int,std::string>(0,token.substr(token.find(':')+1)));
            else if(filed=="id")
                searchList.push_back(std::pair<int,std::string>(1,token.substr(token.find(':')+1)));
            else if(filed=="ssn"){
                secuared=true;
                searchList.push_back(std::pair<int,std::string>(2,token.substr(token.find(':')+1)));
            }
            else if(filed=="phone")
                searchList.push_back(std::pair<int,std::string>(3,token.substr(token.find(':')+1)));
            pos=search_buffer.find(' ');
        }
        patientList=std::vector<patient_t>();
    }
    else{
        patientList=API->search_patients(search_buffer);
    }
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setRowCount(patientList.size()+1);
    for(size_t i=0;i<patientList.size();i++){
        patient_t patient=patientList[i];
        std::string SSN = patient.SSN;
        if(!secuared){
            SSN[0]='*';
            SSN[1]='*';
            SSN[2]='*';
            SSN[3]='*';
            SSN[4]='*';
        }
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
    }
}

void PatientScreen::on_search_table_p_clicked(int row,int colum){
    if(row==0){
        return;
    }
    Dialog *dialog=new Dialog(patientList[row-1],this);
    dialog->setWindowFlag(Qt::SubWindow);
    dialog->show();
    connect(dialog,SIGNAL(correct_ssn(patient_t)),this,SLOT(on_correct_ssn(patient_t)));
}

void PatientScreen::on_correct_ssn(patient_t patient){
    ui->prescriptionTable->setEnabled(true);
    ui->checkout_button->setEnabled(true);
    ui->update_pButton->setEnabled(true);
    curPatient=patient;
    std::vector<prescription_t> prescriptionList = patient.prescription;
    ui->nameEdit->setText(QString::fromStdString(patient.first_name+" "+patient.last_name));
    ui->phoneEdit->setText(QString::fromStdString(patient.phone));
    ui->ssnEdit->setText(QString::fromStdString(patient.SSN));
    ui->addressEdit->setPlainText(QString::fromStdString(patient.address.toString()));
    ui->prescriptionTable->setRowCount(prescriptionList.size());
    for(size_t i=0;i<prescriptionList.size();i++){
        prescription_t prescription = prescriptionList[i];
        QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(prescription.name));
        QTableWidgetItem *UPC = new QTableWidgetItem(QString::fromStdString(prescription.UPC));
        QTableWidgetItem *amount = new QTableWidgetItem(QString::fromStdString(std::to_string(prescription.amount)));
        QTableWidgetItem *next;
        if(prescription.getValid()){
            next=new QTableWidgetItem(QString::fromStdString("N/A"));
            num->setBackground(Qt::green);
            name->setBackground(Qt::green);
            UPC->setBackground(Qt::green);
            amount->setBackground(Qt::green);
            next->setBackground(Qt::green);
        }
        else{
            time_t nextTime=prescription.last_time+60*60*24*prescription.period;
            next=new QTableWidgetItem(QString::fromStdString(ctime(&nextTime)));
            num->setBackground(Qt::red);
            name->setBackground(Qt::red);
            UPC->setBackground(Qt::red);
            amount->setBackground(Qt::red);
            next->setBackground(Qt::red);
        }
        ui->prescriptionTable->setItem(i,0,num);
        ui->prescriptionTable->setItem(i,1,name);
        ui->prescriptionTable->setItem(i,2,UPC);
        ui->prescriptionTable->setItem(i,3,amount);
        ui->prescriptionTable->setItem(i,4,next);
    }
}

void PatientScreen::on_clear_p_clicked(){
    ui->tableWidget->setRowCount(1);
    ui->search_lineEdit_2->clear();
    ui->nameEdit->clear();
    ui->phoneEdit->clear();
    ui->ssnEdit->clear();
    ui->addressEdit->clear();
    ui->prescriptionTable->setRowCount(0);
}

void PatientScreen::on_new_p_clicked(){
    patient_t newPatient;
    newPatient.first_name=ui->nameEdit->text().toStdString();
    newPatient.phone=ui->phoneEdit->text().toStdString();
    newPatient.SSN=ui->ssnEdit->text().toStdString();
    API->create_new_patient(newPatient);
}

void PatientScreen::on_checkout_p_clicked(){
    if(slotcount)
        return;
    slotcount++;
    qDebug()<<"enter";
    if(curPatient.prescription.size()>0){
        for(size_t i=0;i<curPatient.prescription.size();i++){
            if(curPatient.prescription[i].getValid()&&(!curPatient.prescription[i].inCart)){
                qDebug()<<"add";
                drug_t drug=API->search_one_drug(curPatient.prescription[i].name);
                drug.amount=curPatient.prescription[i].amount;
                currentAccount->add_item(drug);
                curPatient.prescription[i].inCart=true;
            }
        }
    }
    qDebug()<<"leave";
    slotcount--;
}

void PatientScreen::on_accept_checkout(){
    if(curPatient.prescription.size()>0){
        for(size_t i=0;i<curPatient.prescription.size();i++){
            if(curPatient.prescription[i].getValid()&&(curPatient.prescription[i].inCart)){
                curPatient.prescription[i].last_time=time(0);
                prescription_t prescription = curPatient.prescription[i];
                QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
                QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(prescription.name));
                QTableWidgetItem *UPC = new QTableWidgetItem(QString::fromStdString(prescription.UPC));
                QTableWidgetItem *amount = new QTableWidgetItem(QString::fromStdString(std::to_string(prescription.amount)));
                QTableWidgetItem *next;
                if(prescription.getValid()){
                    next=new QTableWidgetItem(QString::fromStdString("N/A"));
                    num->setBackground(Qt::green);
                    name->setBackground(Qt::green);
                    UPC->setBackground(Qt::green);
                    amount->setBackground(Qt::green);
                    next->setBackground(Qt::green);
                }
                else{
                    time_t nextTime=prescription.last_time+60*60*24*prescription.period;
                    next=new QTableWidgetItem(QString::fromStdString(ctime(&nextTime)));
                    num->setBackground(Qt::red);
                    name->setBackground(Qt::red);
                    UPC->setBackground(Qt::red);
                    amount->setBackground(Qt::red);
                    next->setBackground(Qt::red);
                }
                ui->prescriptionTable->setItem(i,0,num);
                ui->prescriptionTable->setItem(i,1,name);
                ui->prescriptionTable->setItem(i,2,UPC);
                ui->prescriptionTable->setItem(i,3,amount);
                ui->prescriptionTable->setItem(i,4,next);
            }
        }
    }
}

void PatientScreen::on_clear_cart_action(){
    currentAccount->clear();
    if(curPatient.prescription.size()>0)
        for(size_t i=0;i<curPatient.prescription.size();i++){
           curPatient.prescription[i].inCart=false;
        }
}
