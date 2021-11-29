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
    API = DataStorage::getInstance();
    date = QDate(2021, 10, 1);
    createchart();
}

Reports::~Reports()
{
    delete ui;
}

void Reports::createchart(){

        QPieSeries *series = new QPieSeries();
        QPieSeries *seriesprofit = new QPieSeries();
        newSalesReport = API->get_monthly_report(QDate(2021, 10, 1));
        topdrugList = API->get_top_drugs(QDate(2021, 10, 1));
        series->append("October 2021", newSalesReport.cost);
        seriesprofit->append("October 2021", newSalesReport.profit);
        newSalesReport = API->get_monthly_report(QDate(2021, 9, 1));
        series->append("September 2021", newSalesReport.cost);
        seriesprofit->append("September 2021", newSalesReport.profit);
        newSalesReport = API->get_monthly_report(QDate(2021, 8, 1));
        series->append("August 2021", newSalesReport.cost);
        seriesprofit->append("August 2021", newSalesReport.profit);
        newSalesReport = API->get_monthly_report(QDate(2021, 7, 1));
        series->append("July 2021", newSalesReport.cost);
        seriesprofit->append("July 2021", newSalesReport.profit);
        newSalesReport = API->get_monthly_report(QDate(2021, 6, 1));
        series->append("June 2021", newSalesReport.cost);
        seriesprofit->append("June 2021", newSalesReport.profit);

        QPieSlice *slice = series->slices().at(1);
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);

        QPieSlice *slice2 = seriesprofit->slices().at(1);
        slice2->setExploded();
        slice2->setLabelVisible();
        slice2->setPen(QPen(Qt::darkGreen, 2));
        slice2->setBrush(Qt::green);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Sales Report - Cost");
        chart->legend()->hide();

        QChart *chartprofit = new QChart();
        chartprofit->addSeries(seriesprofit);
        chartprofit->setTitle("Sales Report - Profit");
        chartprofit->legend()->hide();

        ui->sales->setChart(chart);
        ui->profits->setChart(chartprofit);
}
