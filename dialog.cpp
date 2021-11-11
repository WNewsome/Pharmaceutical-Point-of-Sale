#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::Dialog(patient_t patient,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->patient=patient;
    connect(ui->OK_button,SIGNAL(clicked()),this,SLOT(on_clicked_ok()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_clicked_ok(){
    std::string input_ssn=ui->lineEdit->text().toStdString();
    if(input_ssn==patient.SSN){
        correct_ssn(patient);
        this->close();
        this->setParent(nullptr);
    }
    else{
        ui->label_incorrect->setEnabled(true);
        ui->label_incorrect->setStyleSheet("QLabel { background-color : white; color : red; }");
        ui->label_incorrect->setText("Incorrect SSN");
    }
}
