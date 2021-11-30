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
    series = new QPieSeries();
    createchart();

    connect(series->slices().at(1), SIGNAL(pressed()), this, SLOT(sliceclicked(1)));

}

Reports::~Reports()
{
    delete ui;
}

void Reports::sliceclicked(int num){
    QPieSlice *slice = series->slices().at(num);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

}

void Reports::createchart(){

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

        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();

        slice = series->slices().at(1);
        slice->setLabelVisible();

        slice = series->slices().at(2);
        slice->setLabelVisible();

        slice = series->slices().at(3);
        slice->setLabelVisible();

        slice = series->slices().at(4);
        slice->setLabelVisible();

        QPieSlice *slice2 = seriesprofit->slices().at(0);
        slice2->setLabelVisible();

        slice2 = seriesprofit->slices().at(1);
        slice2->setLabelVisible();

        slice2 = seriesprofit->slices().at(2);
        slice2->setLabelVisible();

        slice2 = seriesprofit->slices().at(3);
        slice2->setLabelVisible();

        slice2 = seriesprofit->slices().at(4);
        slice2->setLabelVisible();

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


        QBarSet *set0 = new QBarSet(topdrugList.at(0).brand);
        QBarSet *set1 = new QBarSet(topdrugList.at(1).brand);
        QBarSet *set2 = new QBarSet(topdrugList.at(2).brand);
        QBarSet *set3 = new QBarSet(topdrugList.at(3).brand);
        QBarSet *set4 = new QBarSet(topdrugList.at(4).brand);

        *set0 << topdrugList.at(0).amount;
        *set1 << topdrugList.at(1).amount;
        *set2 << topdrugList.at(2).amount;
        *set3 << topdrugList.at(3).amount;
        *set4 << topdrugList.at(4).amount;

        QBarSeries *barseries = new QBarSeries();
        barseries->append(set0);
        barseries->append(set1);
        barseries->append(set2);
        barseries->append(set3);
        barseries->append(set4);

        QChart *barchart = new QChart();
        barchart->addSeries(barseries);
        barchart->setTitle("Top 10 drugs in October 2021");
        barchart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "Drugs";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        barchart->addAxis(axisX, Qt::AlignBottom);
        barseries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,200);
        barchart->addAxis(axisY, Qt::AlignLeft);
        barseries->attachAxis(axisY);

        ui->top10->setChart(barchart);
}
