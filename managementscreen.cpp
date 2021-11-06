#include "managementscreen.h"
#include "ui_managementscreen.h"



Managementscreen::Managementscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Managementscreen)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
    addDrug = new addgrug(this);
    connect(ui->changedruginfoclick, SIGNAL(clicked()), this, SLOT(on_changedruginfoclick_clicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_tableWidget_cellClicked(int,int)));

    ui->addnewdrugclicked->setEnabled(false);
    ui->storesearch->setEnabled(false);
    ui->editdrug_2->setEnabled(false);
    ui->editimage->setEnabled(false);
    ui->scrollArea_2->setEnabled(false);
}

Managementscreen::~Managementscreen()
{
    delete ui;
}

void Managementscreen::on_changedruginfoclick_clicked()
{
    ui->tableWidget->setRowCount(1);
    ui->addnewdrugclicked->setEnabled(true);
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
        QTableWidgetItem *inventory = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.amount)));
        QTableWidgetItem *cost = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.cost)));
        QTableWidgetItem *price = new QTableWidgetItem(QString::fromStdString(std::to_string(drug.price)));
        ui->tableWidget->setItem(i+1,0,num);
        ui->tableWidget->setItem(i+1,1,name);
        ui->tableWidget->setItem(i+1,2,inventory);
        ui->tableWidget->setItem(i+1,3,cost);
        ui->tableWidget->setItem(i+1,4,price);
    }

}

void Managementscreen::on_tableWidget_cellClicked(int row,int column){
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



void Managementscreen::on_addnewdrugclicked_clicked()
{
    //if no, move on to creation
    addDrug->newDrugname(ui->editdrug->text());
    addDrug->show();
}



void Managementscreen::on_editdrug_2_clicked()
{
    curDrug.brand = ui->brands->text();
    curDrug.cost = ui->cost->text().toInt();
    curDrug.price = ui->prices->text().toInt();
    curDrug.UPC = ui->UPCs->text().toStdString();
    curDrug.DEA = ui->DEAs->text().toStdString();
    curDrug.GPI = ui->GPIs->text().toStdString();
    curDrug.NDC = ui->NDCs->text().toStdString();
    curDrug.amount = ui->quantity->text().toInt();
    curDrug.control_status = ui->controls->text();

}


void Managementscreen::on_editimage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    imageObject = new QImage();
    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);

    drugimage = new QGraphicsScene(this);
    drugimage->addPixmap(image);
    drugimage->setSceneRect(image.rect());
    ui->Image->setScene(drugimage);
    curDrug.picture_url = imagePath;
}

