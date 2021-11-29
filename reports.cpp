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

        QBarSet *set0 = new QBarSet(topdrugList.at(0).brand);
       /* QBarSet *set1 = new QBarSet(topdrugList.at(1).brand);
        QBarSet *set2 = new QBarSet(topdrugList.at(2).brand);
        QBarSet *set3 = new QBarSet(topdrugList.at(3).brand);
        QBarSet *set4 = new QBarSet(topdrugList.at(4).brand);
        QBarSet *set5 = new QBarSet(topdrugList.at(5).brand);
        QBarSet *set6 = new QBarSet(topdrugList.at(6).brand);
        QBarSet *set7 = new QBarSet(topdrugList.at(7).brand);
        QBarSet *set8 = new QBarSet(topdrugList.at(8).brand);*/
      //  QBarSet *set9 = new QBarSet(topdrugList.at(9).brand);

    //    *set0 << topdrugList.at(0).amount;
/*        *set1 << topdrugList.at(1).amount;
           *set2 << 3 << 5 << 8 << 13 << 8 << 5;
           *set3 << 5 << 6 << 7 << 3 << 4 << 5;
           *set4 << 9 << 7 << 5 << 3 << 1 << 2;*/

     //   QBarSeries *barseries = new QBarSeries();
      //  barseries->append(set0);
      //  barseries->append(set1);
      //  barseries->append(set2);
       // barseries->append(set3);
       // barseries->append(set4);

      /*  QChart *barchart = new QChart();
        barchart->addSeries(series);
        barchart->setTitle("Simple barchart example");
        barchart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "1"; //<< "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10";
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,15);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);*/

     //   ui->top10->setChart(barchart);
}
