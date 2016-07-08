#ifndef DROPABLEAREA_H
#define DROPABLEAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <ctime>
#include "cardpanel.h"

class DropableArea : public QWidget {
public:
    DropableArea(CardPanel*);
    virtual void checkDropRelease();        //wykonyanie dropu
    void setViewAsStack(bool);

protected:
    CardPanel *parent;

    QPoint randPosition(const QPoint&);     //zwraca tego samego QPointa z lekkim przsunięciem
    bool asStack = false;                   //czy ma być wrażenie stosu (wykorzystuje randPosition())

    virtual bool acceptDrop();              //zwraca czy można wykonać drop
    virtual void inArea();                  //działania zaraz po wykonaniu dropu

};

#endif // DROPABLEAREA_H
