#include "mainwindow.h"

#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(Imagetest);
    QFile file(":/images.dat");
    MainWindow w;
    w.show();

    return a.exec();
}
