#ifndef REPORTS_H
#define REPORTS_H

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
    sales_report newSalesReport;
};

#endif // REPORTS_H
