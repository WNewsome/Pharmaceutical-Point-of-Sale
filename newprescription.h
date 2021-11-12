#ifndef NEWPRESCRIPTION_H
#define NEWPRESCRIPTION_H

#include <QMainWindow>
#include <datastorage.h>
#include <qlistwidget.h>
#include <checkout.h>
namespace Ui {
class NewPrescription;
}

class NewPrescription : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewPrescription(QWidget *parent = nullptr);
    NewPrescription(prescription_t,int,QWidget *parent = nullptr);
    ~NewPrescription();

private:
    Ui::NewPrescription *ui;
    DataStorage* API;
    CheckoutAccount* currentAccount;
    prescription_t prescriotion;
    drug_t drug;
    bool updateFlag;
    int index;
signals:
    void accept(prescription_t);
    void changed(prescription_t,int);
    void to_delete(int);
private slots:
    void on_accept();
    void on_edit_change(QString);
    void on_clicked_dropdown(QListWidgetItem *);
    void on_delete();
};

#endif // NEWPRESCRIPTION_H
