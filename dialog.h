#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "datastorage.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    patient_t patient;
public:
    explicit Dialog(QWidget *parent = nullptr);
    explicit Dialog(patient_t patient,QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
public slots:
    void on_clicked_ok();
signals:
    void correct_ssn(patient_t);
};

#endif // DIALOG_H
