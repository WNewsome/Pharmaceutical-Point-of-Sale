#include "addgrug.h"
#include "ui_addgrug.h"

addgrug::addgrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addgrug)
{
    ui->setupUi(this);
}

addgrug::~addgrug()
{
    delete ui;
}
