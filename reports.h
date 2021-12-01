#ifndef REPORTS_H
#define REPORTS_H

// reports.h	Jessica Orefice		VT	ECE4574 FA21	Nov 20, 2021
// This class allows the user to see the generated reports

#include <QWidget>
#include "datastorage.h"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Reports;
}

class Reports : public QWidget
{
    Q_OBJECT

public:
    explicit Reports(QWidget *parent = nullptr);
    ~Reports();
    void createchart();

private:
    Ui::Reports *ui;
    DataStorage *API;
    sales_report newSalesReport;
    std::vector<drug_t> topdrugList;
    QDate date;
    QPieSeries *series;
};

#endif // REPORTS_H
