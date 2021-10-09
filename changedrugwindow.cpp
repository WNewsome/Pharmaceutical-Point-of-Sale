#include "changedrugwindow.h"
#include "ui_changedrugwindow.h"

changedrugwindow::changedrugwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::changedrugwindow)
{
    ui->setupUi(this);
}

changedrugwindow::~changedrugwindow()
{
    delete ui;
}

void changedrugwindow::on_pushButton_clicked()
{
    //when clicked, the system is updated and the window closes
}
