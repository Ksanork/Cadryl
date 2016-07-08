#ifndef MAINSLOT_H
#define MAINSLOT_H

#include <QLabel>
#include <QMouseEvent>
#include <ctime>
#include "cardviewer.h"
#include "cardpanel.h"
#include "cardslot.h"
#include "strokelabel.h"

class MainSlot : public QLabel {
public:
    MainSlot(CardPanel*, CardViewer*, CardSlot*);
    void setSlotY(CardSlot*);
    void show();
    void clean();
    bool isEmpty();

    Card* getCard();
    void addCards(Card* [52]);              //dodanie kart (z Deck)

private:
    Card *cards[52];
    int current = 51;

    CardViewer *cd;
    CardSlot *slotY;
    StrokeLabel *amount;

    QPoint randPosition();

    void enterEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // MAINSLOT_H
