#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>

namespace Ui {
class Settingsscreen;
}

class Settingsscreen : public QWidget
{
    Q_OBJECT

public:
    explicit Settingsscreen(QWidget *parent = nullptr);
    ~Settingsscreen();

private:
    Ui::Settingsscreen *ui;
};

#endif // SETTINGSSCREEN_H
