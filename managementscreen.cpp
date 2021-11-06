#include "managementscreen.h"
#include "ui_managementscreen.h"

//TODO: Drug url

Managementscreen::Managementscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Managementscreen)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
    updateDrug = new changedrugwindow(this);
    addDrug = new addgrug(this);
    connect(ui->changedruginfoclick, SIGNAL(clicked()), this, SLOT(on_changedruginfoclick_clicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_tableWidget_cellClicked(int,int)));
}

Managementscreen::~Managementscreen()
{
    delete ui;
}

void Managementscreen::on_changedruginfoclick_clicked()
{
    ui->tableWidget->setRowCount(1);
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
        drug_t drug = drugList[row-1];
        ui->addnewdrugclicked->setEnabled(true);
        ui->storesearch->setEnabled(true);
        ui->drugnames->setText(drug.name);
        ui->DEA_5->setText(QString::fromStdString(drug.DEA));
        ui->GPI_5->setText(QString::fromStdString(drug.GPI));
        ui->NPCs->setText(QString::fromStdString(drug.NDC));
        ui->UPCs->setText(QString::fromStdString(drug.UPC));
        ui->brands->setText(drug.brand);
        ui->controls->setText(drug.control_status);
        ui->Cost_5->setText(QString::number(drug.cost));

        imageObject = new QImage();
        imageObject->load(drug.picture_url);

        image = QPixmap::fromImage(*imageObject);

        scene = new QGraphicsScene(this);
        scene->addPixmap(image);
        scene->setSceneRect(image.rect());
        ui->Image->setScene(scene);

        ui->quantity->setText(QString::number(drug.amount));
        ui->prices->setText(QString::number(drug.price));
    }
}



void Managementscreen::on_addnewdrugclicked_clicked()
{
    //if no, move on to creation
    addDrug->newDrugname(ui->editdrug->text());
    addDrug->show();
}


