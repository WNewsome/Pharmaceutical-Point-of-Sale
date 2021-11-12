#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QMainWindow>
#include "datastorage.h"
#include <QKeyEvent>
#include <QString>
class CheckoutAccount{
public:
    std::vector<drug_t> drugList;
    std::vector<int> amountList;
    // This class keeps track of the main sales screen state
    CheckoutAccount(){
        // Constructor sets everything to 0
        total = 0;
        drugList = std::vector<drug_t>();
    }

    static CheckoutAccount* getInstance(){
        if(NULL==instance){
            instance = new CheckoutAccount();
        }
        return instance;
    }

    void clear(){
        total = 0;
        drugList.clear();
    }

    bool add_item(drug_t drug,int amount){
        // Just update total for now
        if(drug.amount<amount){
            qDebug()<<"out of stock";
            return false;
        }
        total += drug.price*amount;
        drugList.push_back(drug);
        amountList.push_back(amount);
        return true;
    }

    double get_total(){
        return total;
    }

private:
    double total;
    static CheckoutAccount* instance;
};
namespace Ui {
class Checkout;
}

class Checkout : public QMainWindow
{
    Q_OBJECT

public:
    explicit Checkout(QWidget *parent = nullptr);
    ~Checkout();

    void keyPressEvent(QKeyEvent *e);

private:
    Ui::Checkout *ui;
    double total;
    QString buffer;
    CheckoutAccount* account;
    DataStorage* API;
private slots:
    void on_accept();
signals:
    void clearCart();
};

#endif // CHECKOUT_H
