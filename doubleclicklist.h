#ifndef DOUBLECLICKLIST_H
#define DOUBLECLICKLIST_H

#include <QListWidget>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>

class DoubleClickList : public QListWidget
{
    Q_OBJECT
public:
    DoubleClickList(QWidget *parent=Q_NULLPTR);
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
signals:
    void itemClicked(QListWidgetItem *);
    void itemDoubleClicked(QListWidgetItem *);
private:
     bool       m_bDoubleClicked;
     QTimer*    m_single_clicked_timer;
private slots:
     void on_timeout();
};

#endif // DOUBLECLICKLIST_H
