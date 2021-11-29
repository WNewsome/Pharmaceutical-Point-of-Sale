#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include "datastorage.h"

namespace Ui {
class Settingsscreen;
}

class Settingsscreen : public QWidget
{
    Q_OBJECT

public:
    explicit Settingsscreen(QWidget *parent = nullptr);
    ~Settingsscreen();
    void loadSettings();
signals:
    void changed();
private slots:
    void on_EdditSettings_clicked();
    void toggle_enable_settings(bool enabled);
    void toggle_enable_nearby(bool enabled);
    void on_Edditnearby_clicked();

private:
    Ui::Settingsscreen *ui;
    DataStorage *API;
};

#endif // SETTINGSSCREEN_H
