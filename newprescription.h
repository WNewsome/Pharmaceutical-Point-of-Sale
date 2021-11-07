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
    ~NewPrescription();

private:
    Ui::NewPrescription *ui;
    DataStorage* API;
    CheckoutAccount* currentAccount;
    prescription_t prescriotion;
    drug_t drug;
signals:
    void accept(prescription_t);
private slots:
    void on_accept();
    void on_reject();
    void on_edit_change(QString);
    void on_clicked_dropdown(QListWidgetItem *);
};

#endif // NEWPRESCRIPTION_H
