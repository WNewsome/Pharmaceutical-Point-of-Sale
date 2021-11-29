#ifndef OTHERSTORE_H
#define OTHERSTORE_H

#include <QDialog>
#include "datastorage.h"

namespace Ui {
class OtherStore;
}

class OtherStore : public QDialog
{
    Q_OBJECT

public:
    explicit OtherStore(QWidget *parent = nullptr);
    OtherStore(std::vector<drug_t> &, QWidget *parent = nullptr);
    ~OtherStore();

private:
    Ui::OtherStore *ui;
    std::vector<drug_t> drugList;
    DataStorage *API;
};

#endif // OTHERSTORE_H
