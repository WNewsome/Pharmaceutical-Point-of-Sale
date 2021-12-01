#include "addgrug.h"
#include "ui_addgrug.h"
#include <QFileDialog>

// addgrug.cpp	Jessica Orefice		VT	ECE4574 FA21	Nov 12, 2021
// This class allows the user to interact with the GUI and add a drug to the datbase


addgrug::addgrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addgrug)
{
    ui->setupUi(this);
    ui->Error->setVisible(false);
    API = DataStorage::getInstance();
    drugimage = new QGraphicsScene(this);
}

addgrug::~addgrug()
{
    delete ui;
}

//if the window closes, this function clears all the values
void addgrug::closeEvent(QCloseEvent *event){

    newDrug.picture_url  = "";
    ui->drugname->clear();
    ui->brandname->clear();
    ui->Cost->clear();
    ui->Price->clear();
    ui->upc->clear();
    ui->DEA->clear();
    ui->gpi->clear();
    ui->NDC->clear();
    ui->invintory->clear();
    ui->control->clear();
    drugimage->clear();
    ui->Image->viewport()->update();
    QMainWindow::closeEvent(event);
}

void addgrug::on_confirm_clicked()
{
    //check if everything is filled in
    if ((ui->drugname->text() != "") && (ui->brandname->text() != "") && (ui->Cost->text() != "") && (ui->Price->text() != "")
            && (ui->upc->text() != "") && (ui->invintory->text() != "") && (ui->gpi->text() != "")
            && (ui->NDC->text() != "")){
        newDrug.name = ui->drugname->text();
        newDrug.brand = ui->brandname->text();
        newDrug.cost = ui->Cost->text().toInt();
        newDrug.price = ui->Price->text().toInt();
        newDrug.UPC = ui->upc->text().toStdString();
        newDrug.DEA = ui->DEA->text().toStdString();
        newDrug.GPI = ui->gpi->text().toStdString();
        newDrug.NDC = ui->NDC->text().toStdString();
        newDrug.amount = ui->invintory->text().toInt();
        newDrug.control_status = ui->control->text();
        int quaintity = newDrug.amount;

        //adds drug to the database
        API->create_new_drug(newDrug,quaintity);

        ui->drugname->clear();
        ui->brandname->clear();
        ui->Cost->clear();
        ui->Price->clear();
        ui->upc->clear();
        ui->DEA->clear();
        ui->gpi->clear();
        ui->NDC->clear();
        ui->invintory->clear();
        ui->control->clear();
        drugimage->clear();
        ui->Image->viewport()->update();

        this->close();
    }

    //if all required fieldas are not filled in an error shows up
    else{
        ui->frame->setStyleSheet("QFrame { border: 5px solid red } ");
        ui->Error->setStyleSheet("QLabel { color : red; }");
        ui->Error->setVisible(true);
    }
}

//allows the user to add an image
void addgrug::on_openimage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    imageObject = new QImage();
    imageObject->load(imagePath);
    QFileInfo im(imagePath);

    QFile::rename(imagePath, "assets/" + im.completeBaseName() + "." + im.completeSuffix()); //moves file to assets

    image = QPixmap::fromImage(*imageObject);

    drugimage->addPixmap(image);
    drugimage->setSceneRect(image.rect());
    ui->Image->setScene(drugimage);
    newDrug.picture_url = "assets/" + im.baseName() + "." + im.completeSuffix();
}

