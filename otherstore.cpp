#include "otherstore.h"
#include "ui_otherstore.h"

OtherStore::OtherStore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtherStore)
{
    ui->setupUi(this);
    API = DataStorage::getInstance();
    ui->treeWidget->setColumnCount(0);
}

OtherStore::OtherStore(std::vector<drug_t> &drugList, QWidget *parent):
    QDialog(parent),
    ui(new Ui::OtherStore){
    ui->setupUi(this);
    API = DataStorage::getInstance();
    this->drugList=drugList;
    QString drugs="";
    for(drug_t drug:this->drugList){
        drugs+=drug.name+" ";
        QTreeWidgetItem* item0=new QTreeWidgetItem();
        item0->setText(0,drug.name);
        ui->treeWidget->addTopLevelItem(item0);
        auto stores=API->get_near_by_store();
        for (auto store :stores ) {
            auto res=API->search_drugs_remotelly(std::get<0>(store),drug.name.toStdString());
            if(res.size()>0){
                if(res[0].amount>drug.amount){
                QString str=std::get<2>(store)+"\n"+QString::fromStdString(std::get<1>(store).toString());
                QStringList list(str);
                QTreeWidgetItem* item1=new QTreeWidgetItem();
                item1->setText(0,str);
                item0->addChild(item1);
                }
            }
        }

    }
    ui->label->setText(drugs+"are not avilable in this store,\n do you still want to continue to checkout?");
}

OtherStore::~OtherStore()
{
    delete ui;
}
