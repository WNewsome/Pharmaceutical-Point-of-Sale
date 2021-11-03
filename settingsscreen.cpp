#include "settingsscreen.h"
#include "ui_settingsscreen.h"

Settingsscreen::Settingsscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settingsscreen)
{
    ui->setupUi(this);
}

Settingsscreen::~Settingsscreen()
{
    delete ui;
}
