#ifndef SALESCREEN_H
#define SALESCREEN_H

#include <QWidget>
#include "datastorage.h"
#include "checkout.h"
#include <QListWidget>
#include <QDir>
#include <QGraphicsScene>
#include "otherstore.h"
namespace Ui {
class SaleScreen;
}

class SaleScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SaleScreen(QWidget *parent = nullptr);
    ~SaleScreen();

private:
    Ui::SaleScreen *ui;
    DataStorage *API;
    CheckoutAccount* currentAccount;
    drug_t curDrug;
    std::vector<drug_t> drug_list;
    QPixmap image;
    QImage* imageObject;
    QGraphicsScene* drugimage;
private slots:
    void on_search_button_d_clicked();
    void on_edit_change(QString);
    void on_clicked_dropdown(QListWidgetItem *);
    void on_double_clicked_dropdown(QListWidgetItem *);
    void on_clicked_list(QListWidgetItem *);
    void on_double_clicked_list(QListWidgetItem *);
    void on_checkout();
    void on_clear();
    void on_combo_changed(int);
    void on_setting_changed();
};

#endif // SALESCREEN_H
