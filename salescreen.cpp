#include "salescreen.h"
#include "ui_salescreen.h"

SaleScreen::SaleScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleScreen)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
    currentAccount = CheckoutAccount::getInstance();
    curDrug = drug_t();
    ui->drug_name->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->drug_code->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->drug_stock->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    drugimage = new QGraphicsScene(ui->graphicsView);
    connect(ui->search_lineEdit,SIGNAL(textEdited(QString)),this,SLOT(on_edit_change(QString)));
    connect(ui->items_dropdown,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(on_clicked_dropdown(QListWidgetItem *)));
    connect(ui->items_dropdown,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(on_double_clicked_dropdown(QListWidgetItem *)));
    connect(ui->search_button,SIGNAL(clicked()), this, SLOT(on_search_button_d_clicked()));
    connect(ui->cartButton,SIGNAL(clicked()), this, SLOT(on_checkout()));
    connect(ui->clearButton,SIGNAL(clicked()), this, SLOT(on_clear()));
    connect(ui->items_list,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(on_clicked_list(QListWidgetItem *)));
    connect(ui->items_list,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(on_double_clicked_list(QListWidgetItem *)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_combo_changed(int)));
    ui->label_3->setText(API->get_store_name());
    ui->label_4->setText(QString::fromStdString(API->get_store_address().toString()));
}

SaleScreen::~SaleScreen()
{
    delete ui;
}

void SaleScreen::on_search_button_d_clicked(){
    drug_list=API->search_drugs(ui->search_lineEdit->text().toStdString());
    ui->items_list->clear();
    for (size_t i=0;i<drug_list.size() ;i++ ) {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(drug_list[i].name);
        ui->items_list->insertItem(i,newItem);
    }
    ui->items_list->setEnabled(true);
}

void SaleScreen::on_edit_change(QString buffer){
    if(buffer.size()==0){
        return;
    }
    ui->items_dropdown->clear();
    std::string name=buffer.toStdString();
    std::vector<drug_t> drug_list_drop = API->search_drugs(name);
    for (size_t i=0;i<drug_list_drop.size() ;i++ ) {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(drug_list_drop[i].name);
        ui->items_dropdown->insertItem(i,newItem);
    }
    if(!ui->items_dropdown->isVisible()){
        ui->items_dropdown->setVisible(true);
        ui->items_dropdown->setEnabled(true);
    }
}

void SaleScreen::on_clicked_dropdown(QListWidgetItem * item){
    ui->search_lineEdit->setText(item->text());
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
}

void SaleScreen::on_double_clicked_dropdown(QListWidgetItem * item){
    drugimage->clear();
    curDrug = API->search_one_drug(item->text().toStdString());
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(curDrug.name);
    ui->items_list->insertItem(0,newItem);
    drug_list.push_back(curDrug);
    ui->drug_name->setText(curDrug.name);
    ui->drug_code->setText(QString::fromStdString(curDrug.UPC));
    ui->drug_stock->setText(QString::number(curDrug.amount));
    QDir dir;
    QString path=dir.relativeFilePath("../Pharmaceutical-Point-of-Sale/asset/Lexapro.jpg");
    imageObject = new QImage();
    imageObject->load(path);
    image = QPixmap::fromImage(*imageObject);
    drugimage->addPixmap(image);
    drugimage->setSceneRect(image.rect());
    ui->graphicsView->setScene(drugimage);
    ui->spinBox->setValue(1);
}

void SaleScreen::on_clicked_list(QListWidgetItem *item){
    drugimage->clear();
    curDrug = drug_list[ui->items_list->currentRow()];
    ui->drug_name->setText(curDrug.name);
    ui->drug_code->setText(QString::fromStdString(curDrug.UPC));
    ui->drug_stock->setText(QString::number(curDrug.amount));
    QDir dir;
    QString path=dir.relativeFilePath("../Pharmaceutical-Point-of-Sale/asset/Lexapro.jpg");
    imageObject = new QImage();
    imageObject->load(path);
    image = QPixmap::fromImage(*imageObject);
    drugimage->addPixmap(image);
    drugimage->setSceneRect(image.rect());
    ui->graphicsView->setScene(drugimage);
    ui->spinBox->setValue(1);
}

void SaleScreen::on_double_clicked_list(QListWidgetItem *item){
    curDrug = drug_list[ui->items_list->currentRow()];
    drug_t drug=curDrug;
    currentAccount->add_item(drug,1);
}

void SaleScreen::on_checkout(){
    drug_t drug=curDrug;
    currentAccount->add_item(drug,ui->spinBox->value());
}

void SaleScreen::on_clear(){
    drugimage->clear();
    curDrug=drug_t();
    drug_list.clear();
    ui->search_lineEdit->clear();
    ui->items_dropdown->clear();
    ui->items_list->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->spinBox->setValue(1);
    ui->drug_code->setText("");
    ui->drug_name->setText("");
    ui->drug_stock->setText("");
    ui->items_dropdown->setVisible(false);
    ui->items_dropdown->setEnabled(false);
}

void SaleScreen::on_combo_changed(int index){
    if(curDrug.valid)
    switch (index) {
    case 0:ui->drug_code->setText(QString::fromStdString(curDrug.UPC));break;
    case 1:ui->drug_code->setText(QString::fromStdString(curDrug.DEA));break;
    case 2:ui->drug_code->setText(QString::fromStdString(curDrug.GPI));break;
    case 3:ui->drug_code->setText(QString::fromStdString(curDrug.NDC));break;
    }
}
