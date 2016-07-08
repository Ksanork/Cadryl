#include "cardslotinc.h"
#include "card.h"
#include "mainwindow.h"

CardSlotInc::CardSlotInc(int _v, CardPanel *_cp) : value(_v), CardSlot(_cp) {
    setStyleSheet("border-image: url(:/bg/inc-" + QString::number(_v) + ".png)");
}

bool CardSlotInc::acceptDrop() {
    Card* c = dynamic_cast<Card*>(cd::parent->getDrag());

    if(!cd::cards.isEmpty()) {
        return(c->getType() == cd::lastcard()->getType()  &&
               c->getValue() == (cd::lastcard()->getValue()+2));
    }
    else if(c->getValue() == value) return true;
    else return false;
}

void CardSlotInc::inArea() {
    cd::inArea();

    Card *c = dynamic_cast<Card*>(cd::parent->getDrag());

    c->setDragable(false);
    if(asStack) {
        c->setLastPosition(
                QRect(randPosition(QPoint(x()-(MainWindow::perc_w * 22), y()-(MainWindow::perc_w * 48))), QSize(MainWindow::perc_w * 250, MainWindow::perc_h * 250))
                //QRect(setPosition(QPoint(x(), y())), QSize(250, 250))
        );
    }
    else {
        c->setLastPosition(
                QRect(QPoint(x()-(MainWindow::perc_w * 22), y()-(MainWindow::perc_w * 48)), QSize(MainWindow::perc_w * 250, MainWindow::perc_h * 250))
                //QRect(setPosition(QPoint(x(), y())), QSize(250, 250))
        );
    }


    c->animateRotation();
}


bool CardSlotInc::isPossible(CardSlot *s) {
    if(!this->isEmpty() && !s->isEmpty()) {
        return(s->lastcard()->getType() == lastcard()->getType()  &&
               s->lastcard()->getValue() == (lastcard()->getValue()+2));
    }
    else if(!s->isEmpty()){
        return (s->lastcard()->getValue() == value);
    }
    else return false;
}
