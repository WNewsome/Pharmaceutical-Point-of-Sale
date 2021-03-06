#include "managementscreen.h"
#include "ui_managementscreen.h"

// managmentscreen.cpp	Jessica Orefice		VT	ECE4574 FA21	Nov 12, 2021
// This class allows the user to interact with the management screen tab. This allows them to edit/search/add drugs
// as well as generate reports and edit settings.

Managementscreen::Managementscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Managementscreen)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
    addDrug = new addgrug();
    settings = new Settingsscreen();
    reports = new Reports();
    connect(ui->changedruginfoclick, SIGNAL(clicked()), this, SLOT(changedruginfoclicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_tableWidget_cellClicked(int,int)));

    ui->changedruginfoclick->setEnabled(true);
    ui->addnewdrugclicked->setEnabled(false);
    ui->storesearch->setEnabled(false);
    ui->editdrug_2->setEnabled(false);
    ui->editimage->setEnabled(false);
    ui->scrollArea_2->setEnabled(false);
    ui->Message->setVisible(false);
}

Managementscreen::~Managementscreen()
{
    delete ui;
}

//search for a particular drug in the database
void Managementscreen::changedruginfoclicked()
{
    ui->scrollArea_2->setEnabled(false);
    ui->Message->setVisible(false);
    ui->tableWidget->setRowCount(1);
    ui->addnewdrugclicked->setEnabled(true);
    ui->editdrug_2->setEnabled(false);
    ui->editimage->setEnabled(false);
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
   ui->tableWidget->setEnabled(true);
   ui->tableWidget->setRowCount(drugList.size()+1);
    for(int i=0;i<drugList.size();i++){
        drug_t drug = drugList[i];
        QTableWidgetItem *num = new QTableWidgetItem(QString::fromStdString(std::to_string(i+1)));
        QTableWidgetItem *name = new QTableWidgetItem(drug.name);
        QTableWidgetItem *brand = new QTableWidgetItem(drug.brand);
        QTableWidgetItem *inventory = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.amount)));
        QTableWidgetItem *price = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.price)));
        ui->tableWidget->setItem(i+1,0,num);
        ui->tableWidget->setItem(i+1,1,name);
        ui->tableWidget->setItem(i+1,2,brand);
        ui->tableWidget->setItem(i+1,3,inventory);
        ui->tableWidget->setItem(i+1,4,price);
    }

}

//edit the cells on the table
void Managementscreen::on_tableWidget_cellClicked(int row, int column){
    ui->Message->setVisible(false);
    if (row != 0){
        curDrug = drugList[row-1];
        ui->storesearch->setEnabled(true);
        ui->editdrug_2->setEnabled(true);
        ui->editimage->setEnabled(true);
        ui->scrollArea_2->setEnabled(true);
        ui->drugnames->setText(curDrug.name);
        ui->DEAs->setText(QString::fromStdString(curDrug.DEA));
        ui->GPIs->setText(QString::fromStdString(curDrug.GPI));
        ui->NDCs->setText(QString::fromStdString(curDrug.NDC));
        ui->UPCs->setText(QString::fromStdString(curDrug.UPC));
        ui->brands->setText(curDrug.brand);
        ui->controls->setText(curDrug.control_status);
        ui->cost->setText(QString::number(curDrug.cost));

        imageObject = new QImage();
        imageObject->load(curDrug.picture_url);

        image = QPixmap::fromImage(*imageObject);

        drugimage = new QGraphicsScene(this);
        drugimage->addPixmap(image);
        drugimage->setSceneRect(image.rect());
        ui->Image->setScene(drugimage);

        ui->quantity->setText(QString::number(curDrug.amount));
        ui->prices->setText(QString::number(curDrug.price));
    }
}

//opens the add a new drug screen
void Managementscreen::on_addnewdrugclicked_clicked()
{
    addDrug->show();
}

//syncs drug edits with the database
void Managementscreen::on_editdrug_2_clicked()
{
    //checks if all required lines are filled in
    if ((ui->drugnames->text() != "") && (ui->brands->text() != "")&& (ui->cost->text() != "") && (ui->prices->text() != "")
            && (ui->UPCs->text() != "") && (ui->quantity->text() != "") && (ui->GPIs->text() != "")
            && (ui->NDCs->text() != "")){
        curDrug.name = ui->drugnames->text();
        curDrug.brand = ui->brands->text();
        curDrug.cost = ui->cost->text().toInt();
        curDrug.price = ui->prices->text().toInt();
        curDrug.UPC = ui->UPCs->text().toStdString();
        curDrug.DEA = ui->DEAs->text().toStdString();
        curDrug.GPI = ui->GPIs->text().toStdString();
        curDrug.NDC = ui->NDCs->text().toStdString();
        curDrug.amount = ui->quantity->text().toInt();
        curDrug.control_status = ui->controls->text();
        API->update_drug(curDrug);
        changedruginfoclicked();
        ui->Message->setStyleSheet("QLabel { color : green; }");
        ui->Message->setText("Drug Updated!");
        ui->Message->setVisible(true);
    }

    //in they are not an error is displayed above the edits
    else{
        ui->Message->setStyleSheet("QLabel { color : red; }");
        ui->Message->setText("ERROR: FIELDS CANNOT BE LEFT EMPTY");
        ui->Message->setVisible(true);
    }

}

//updates the image corresponding to the drug
void Managementscreen::on_editimage_clicked()
{
    //opens file manager to choose drug
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "assets/", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    imageObject = new QImage();
    imageObject->load(imagePath);
    QFileInfo im(imagePath);

    //moves the image to the assets folder
    QFile::rename(imagePath, "assets/" + im.completeBaseName() + "." + im.completeSuffix()); //move file??

    //displays the image on the graphics screen
    image = QPixmap::fromImage(*imageObject);

    drugimage = new QGraphicsScene(this);
    drugimage->addPixmap(image);
    drugimage->setSceneRect(image.rect());
    ui->Image->setScene(drugimage);
    curDrug.picture_url = "assets/" + im.baseName() + "." + im.completeSuffix();
    API->update_drug(curDrug);
    ui->Message->setStyleSheet("QLabel { color : green; }");
    ui->Message->setText("Image Updated!");
    ui->Message->setVisible(true);
} 

//opens the reports screen
void Managementscreen::on_generatereports_clicked()
{
    reports->show();
}

//opens the settings screen
void Managementscreen::on_updatesettigns_clicked()
{
    settings->show();
}
