#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "changedrugwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString web_API = "https://wnewsome.com/POS/search.php";
    changedrugwindow *updateDrug;

private slots:
    void downloadFinished(QNetworkReply*);
    void on_search_button_clicked();
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
