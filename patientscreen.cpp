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
    connect(ui->nameEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit(QString)));
    connect(ui->phoneEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit(QString)));
    connect(ui->addressEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit(QString)));
    connect(ui->ssnEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit(QString)));
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(on_date(QDate)));
    connect(ui->update_pButton, SIGNAL(clicked()), this, SLOT(on_update_p_clicked()));
    connect(ui->addNewButton_2,SIGNAL(clicked()), this, SLOT(on_add_p_clicked()));
    connect(ui->prescriptionTable,SIGNAL(cellClicked(int,int)),this,SLOT(on_table_p_clicked(int,int)));
    API = DataStorage::getInstance();
    currentAccount = CheckoutAccount::getInstance();
    updateFlag=false;
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
    updateFlag=true;
    QDate dob;
    curPatient=patient;
    std::vector<prescription_t> prescriptionList = patient.prescription;
    ui->nameEdit->setText(QString::fromStdString((patient.middle_name.size()==0)?patient.first_name+" "+patient.last_name:patient.first_name+" "+patient.middle_name+" "+patient.last_name));
    ui->phoneEdit->setText(QString::fromStdString(patient.phone));
    ui->ssnEdit->setText(QString::fromStdString(patient.SSN));
    ui->addressEdit->setPlainText(QString::fromStdString(patient.address.toString()));
    ui->prescriptionTable->setRowCount(prescriptionList.size());
    ui->idEdit->setText(QString::number(patient.id));
    dob.setDate(patient.DOB.year,patient.DOB.month,patient.DOB.day);
    ui->dateEdit->setDate(dob);
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
            next=new QTableWidgetItem(prescription.last_time.addDays(prescription.period).toString());
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
    ui->update_pButton->setEnabled(false);
    ui->addNewButton_2->setEnabled(true);
}

void PatientScreen::on_clear_p_clicked(){
    ui->tableWidget->setRowCount(1);
    ui->search_lineEdit_2->clear();
    ui->nameEdit->clear();
    ui->phoneEdit->clear();
    ui->ssnEdit->clear();
    ui->addressEdit->clear();
    ui->prescriptionTable->setRowCount(0);
    curPatient=patient_t();
    updateFlag=false;
    ui->update_pButton->setEnabled(false);
    ui->addNewButton->setEnabled(false);
    ui->addNewButton_2->setEnabled(false);
    ui->dateEdit->setDate(QDate());
}

void PatientScreen::on_new_p_clicked(){
    patient_t newPatient;
    std::string name;
    std::string address;
    name=ui->nameEdit->text().toStdString();
    int pos=name.find(' ');
    newPatient.first_name=name.substr(0,pos);
    name=name.substr(pos+1);
    pos=name.find(' ');
    if(pos==-1){
        newPatient.last_name=name.substr(0,pos);
    }
    else{
        newPatient.middle_name=name.substr(0,pos);
        name=name.substr(pos+1);
        pos=name.find(' ');
        newPatient.last_name=name.substr(0,pos);
    }
    newPatient.phone=ui->phoneEdit->text().toStdString();
    newPatient.SSN=ui->ssnEdit->text().toStdString();
    address=ui->addressEdit->toPlainText().toStdString();
    pos=address.find('\n');
    newPatient.address.street_number=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    newPatient.address.city=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    newPatient.address.state=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    newPatient.address.zip_code=address.substr(0,pos);
    newPatient.DOB.day=ui->dateEdit->date().day();
    newPatient.DOB.month=ui->dateEdit->date().month();
    newPatient.DOB.year=ui->dateEdit->date().year();
    API->create_new_patient(newPatient);
    ui->addNewButton->setEnabled(false);
}

void PatientScreen::on_checkout_p_clicked(){
    if(slotcount)
        return;
    slotcount++;
    if(curPatient.prescription.size()>0){
        for(size_t i=0;i<curPatient.prescription.size();i++){
            if(curPatient.prescription[i].getValid()&&(!curPatient.prescription[i].inCart)){
                drug_t drug=API->search_one_drug(curPatient.prescription[i].name);
                curPatient.prescription[i].inCart=currentAccount->add_item(drug,curPatient.prescription[i].amount);
            }
        }
    }
    slotcount--;
}

void PatientScreen::on_accept_checkout(){
    if(curPatient.prescription.size()>0){
        for(size_t i=0;i<curPatient.prescription.size();i++){
            if(curPatient.prescription[i].getValid()&&(curPatient.prescription[i].inCart)){
                curPatient.prescription[i].last_time=QDate::currentDate();
                prescription_t prescription = curPatient.prescription[i];
                QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
                QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(prescription.name));
                QTableWidgetItem *UPC = new QTableWidgetItem(QString::fromStdString(prescription.UPC));
                QTableWidgetItem *amount = new QTableWidgetItem(QString::fromStdString(std::to_string(prescription.amount)));
                QTableWidgetItem *next;
                next=new QTableWidgetItem(prescription.last_time.addDays(prescription.period).toString());
                num->setBackground(Qt::red);
                name->setBackground(Qt::red);
                UPC->setBackground(Qt::red);
                amount->setBackground(Qt::red);
                next->setBackground(Qt::red);
                ui->prescriptionTable->setItem(i,0,num);
                ui->prescriptionTable->setItem(i,1,name);
                ui->prescriptionTable->setItem(i,2,UPC);
                ui->prescriptionTable->setItem(i,3,amount);
                ui->prescriptionTable->setItem(i,4,next);
            }
        }
        API->update_patient(curPatient);
    }
}

void PatientScreen::on_clear_cart_action(){
    currentAccount->clear();
    if(curPatient.prescription.size()>0)
        for(size_t i=0;i<curPatient.prescription.size();i++){
           curPatient.prescription[i].inCart=false;
        }
}


void PatientScreen::on_update_p_clicked(){
    std::string name;
    std::string address;
    name=ui->nameEdit->text().toStdString();
    int pos=name.find(' ');
    curPatient.first_name=name.substr(0,pos);
    name=name.substr(pos+1);
    pos=name.find(' ');
    if(pos==-1){
        curPatient.last_name=name.substr(0,pos);
        curPatient.middle_name="";
    }
    else{
        curPatient.middle_name=name.substr(0,pos);
        name=name.substr(pos+1);
        pos=name.find(' ');
        curPatient.last_name=name.substr(0,pos);
    }
    curPatient.phone=ui->phoneEdit->text().toStdString();
    curPatient.SSN=ui->ssnEdit->text().toStdString();
    address=ui->addressEdit->toPlainText().toStdString();
    pos=address.find('\n');
    curPatient.address.street_number=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    curPatient.address.city=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    curPatient.address.state=address.substr(0,pos);
    address=address.substr(pos+1);
    pos=address.find(',');
    curPatient.address.zip_code=address.substr(0,pos);
    curPatient.DOB.day=ui->dateEdit->date().day();
    curPatient.DOB.month=ui->dateEdit->date().month();
    curPatient.DOB.year=ui->dateEdit->date().year();
    API->update_patient(curPatient);
    ui->update_pButton->setEnabled(false);
}

void PatientScreen::on_edit(QString){
    if(updateFlag)
        ui->update_pButton->setEnabled(true);
    else
        ui->addNewButton->setEnabled(true);
    ui->addNewButton_2->setEnabled(true);
}

void PatientScreen::on_date(QDate){
    if(updateFlag)
        ui->update_pButton->setEnabled(true);
    else
        ui->addNewButton->setEnabled(true);

    ui->addNewButton_2->setEnabled(true);
}

void PatientScreen::on_add_p_clicked(){
    NewPrescription* newWindow = new NewPrescription(this);
    connect(newWindow,SIGNAL(accept(prescription_t)),this,SLOT(on_accept_add(prescription_t)));
    newWindow->setWindowFlag(Qt::SubWindow);
    newWindow->show();
}
void PatientScreen::on_accept_add(prescription_t prescription){
    int row=ui->prescriptionTable->rowCount();
    ui->prescriptionTable->setRowCount(row+1);
    curPatient.prescription.push_back(prescription);
    QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(ui->prescriptionTable->rowCount()+1)));
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
        next=new QTableWidgetItem(prescription.last_time.addDays(prescription.period).toString());
        num->setBackground(Qt::red);
        name->setBackground(Qt::red);
        UPC->setBackground(Qt::red);
        amount->setBackground(Qt::red);
        next->setBackground(Qt::red);
    }
    ui->prescriptionTable->setItem(row,0,num);
    ui->prescriptionTable->setItem(row,1,name);
    ui->prescriptionTable->setItem(row,2,UPC);
    ui->prescriptionTable->setItem(row,3,amount);
    ui->prescriptionTable->setItem(row,4,next);
    ui->update_pButton->setEnabled(true);
}


void PatientScreen::on_changed(prescription_t prescription,int index){
    curPatient.prescription[index]=prescription;
    QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(ui->prescriptionTable->rowCount()+1)));
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
        next=new QTableWidgetItem(prescription.last_time.addDays(prescription.period).toString());
        num->setBackground(Qt::red);
        name->setBackground(Qt::red);
        UPC->setBackground(Qt::red);
        amount->setBackground(Qt::red);
        next->setBackground(Qt::red);
    }
    ui->prescriptionTable->setItem(index,0,num);
    ui->prescriptionTable->setItem(index,1,name);
    ui->prescriptionTable->setItem(index,2,UPC);
    ui->prescriptionTable->setItem(index,3,amount);
    ui->prescriptionTable->setItem(index,4,next);
    ui->update_pButton->setEnabled(true);
}
void PatientScreen::on_delete(int index){
    curPatient.prescription.erase(curPatient.prescription.begin()+index);
    ui->prescriptionTable->removeRow(index);
    ui->prescriptionTable->setRowCount(curPatient.prescription.size());
    ui->update_pButton->setEnabled(true);
}

void PatientScreen::on_table_p_clicked(int row,int){
    NewPrescription* newWindow = new NewPrescription(curPatient.prescription[row],row,this);
    connect(newWindow,SIGNAL(changed(prescription_t,int)),this,SLOT(on_changed(prescription_t,int)));
    connect(newWindow,SIGNAL(to_delete(int)),this,SLOT(on_delete(int)));
    newWindow->setWindowFlag(Qt::SubWindow);
    newWindow->show();
}
