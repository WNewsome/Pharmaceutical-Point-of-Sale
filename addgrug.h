#ifndef ADDGRUG_H
#define ADDGRUG_H

#include <QMainWindow>

namespace Ui {
class addgrug;
}

class addgrug : public QMainWindow
{
    Q_OBJECT

public:
    explicit addgrug(QWidget *parent = nullptr);
    ~addgrug();

private:
    Ui::addgrug *ui;
};

#endif // ADDGRUG_H
