#include "reports.h"
#include "ui_reports.h"

//sales report struct
//montly repot
//profit report

//get top drugs
//QDate argument

Reports::Reports(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reports)
{
    ui->setupUi(this);
    //get_monthly_report
    createchart();
}

Reports::~Reports()
{
    delete ui;
}

void Reports::createchart(){

    //![1]
        QPieSeries *series = new QPieSeries();
        series->append("Jane", 1);
        series->append("Joe", 2);
        series->append("Andy", 3);
        series->append("Barbara", 4);
        series->append("Axel", 5);
    //![1]

    //![2]
        QPieSlice *slice = series->slices().at(1);
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);
    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple piechart example");
        chart->legend()->hide();
    //![3]

    //![4]
        ui->sales->setChart(chart);
}
