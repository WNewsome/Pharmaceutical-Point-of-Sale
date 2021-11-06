#include "addgrug.h"
#include "ui_addgrug.h"
#include <QFileDialog>

addgrug::addgrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addgrug)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
}

addgrug::~addgrug()
{
    delete ui;
}

void addgrug::newDrugname(QString drugname){
    newDrug.name = drugname;
    ui->drugname->setText(newDrug.name);
}

void addgrug::on_confirm_clicked()
{
    //check if everything is filled in and display error??

    //put drug stuff from lines in
    newDrug.brand = ui->brandname->text();
    newDrug.cost = ui->Cost->text().toInt();
    newDrug.price = ui->Price->text().toInt();
    newDrug.UPC = ui->upc->text().toStdString();
    newDrug.DEA = ui->DEA->text().toStdString();
    newDrug.GPI = ui->gpi->text().toStdString();
    newDrug.NDC = ui->NDC->text().toStdString();
    newDrug.amount = ui->invintory->text().toInt();
    newDrug.control_status = ui->control->text();
   // newDrug.picture_url = "the_url";
    int quaintity = newDrug.amount;

    API->create_new_drug(newDrug,quaintity);

    this->close();
}


void addgrug::on_openimage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    imageObject = new QImage();
    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->Image->setScene(scene);
    newDrug.picture_url = imagePath;

}


void addgrug::on_saveimage_clicked()
{

}

