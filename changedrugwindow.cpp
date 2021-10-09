#include "changedrugwindow.h"
#include "ui_changedrugwindow.h"

ChangeDrugWindow::ChangeDrugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeDrugWindow)
{
    ui->setupUi(this);
}

ChangeDrugWindow::~ChangeDrugWindow()
{
    delete ui;
}

void ChangeDrugWindow::on_pushButton_clicked()
{
    //when clicked, the system is updated and the window closes
}

