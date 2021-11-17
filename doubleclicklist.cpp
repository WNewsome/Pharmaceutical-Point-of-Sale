#include "doubleclicklist.h"

DoubleClickList::DoubleClickList(QWidget *parent):QListWidget(parent),m_single_clicked_timer(new QTimer(this)),m_bDoubleClicked(false)
{
    m_single_clicked_timer->setSingleShot(true);
    connect(m_single_clicked_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
}

void DoubleClickList::mousePressEvent(QMouseEvent* event){
    if(count()<=0){
        return;
    }
    if(!m_bDoubleClicked){
        m_bDoubleClicked=true;
        m_single_clicked_timer->start(200);
        QListWidget::mousePressEvent(event);
    }
}

void DoubleClickList::mouseDoubleClickEvent(QMouseEvent* event){
    if(count()<=0){
        return;
    }
    m_single_clicked_timer->stop();
    m_bDoubleClicked = false;
    emit itemDoubleClicked(this->currentItem());
}

void DoubleClickList::on_timeout(){
    if(count()<=0){
        return;
    }
    m_bDoubleClicked = false;
    emit itemClicked(this->currentItem());
}
