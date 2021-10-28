#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QMainWindow>
#include "datastorage.h"
#include <QKeyEvent>
#include <QString>
class CheckoutAccount{
public:
    std::vector<drug_t> drugList;
    // This class keeps track of the main sales screen state
    CheckoutAccount(){
        // Constructor sets everything to 0
        total = 0;
        drugList = std::vector<drug_t>();
    }

    void add_item(drug_t drug){
        // Just update total for now
        total += drug.price*drug.amount;
        drugList.push_back(drug);
    }

    double get_total(){
        return total;
    }

private:
    double total;
};
namespace Ui {
class Checkout;
}

class Checkout : public QMainWindow
{
    Q_OBJECT

public:
    explicit Checkout(QWidget *parent = nullptr);
    explicit Checkout(CheckoutAccount,QWidget *parent = nullptr);
    ~Checkout();

    void keyPressEvent(QKeyEvent *e);

private:
    Ui::Checkout *ui;
    double total;
    QString buffer;
private slots:
    void on_accept();
signals:
    void clearCart();
};

#endif // CHECKOUT_H
