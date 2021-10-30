#ifndef PATIENTSCREEN_H
#define PATIENTSCREEN_H

#include <QWidget>
#include "datastorage.h"
#include "dialog.h"
#include "checkout.h"

namespace Ui {
class patientScreen;
}

class PatientScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PatientScreen(QWidget *parent = nullptr);
    ~PatientScreen();

private:
    Ui::patientScreen *ui;
    DataStorage *API;
    bool secuared;
    std::vector<patient_t> patientList;
    patient_t curPatient;
    CheckoutAccount* currentAccount;
    int slotcount;
private slots:
    void on_search_button_p_clicked();                            // Main search button in patient tab
    void on_search_table_p_clicked(int,int);
    void on_correct_ssn(patient_t);
    void on_clear_p_clicked();
    void on_new_p_clicked();
    void on_checkout_p_clicked();
    void on_accept_checkout();
    void on_clear_cart_action();
};

#endif // PATIENTSCREEN_H