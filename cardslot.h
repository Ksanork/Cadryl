#ifndef CARDSLOT_H
#define CARDSLOT_H

#include "dropablearea.h"
#include "cardpanel.h"
#include "mainslot.h"

class Card;

class CardSlot : public DropableArea {
public:
    CardSlot(CardPanel*);
    void operator<<(CardSlot*);
    void operator<<(MainSlot*);
    void operator<<(Deck*);

    void show();
    void clean();
    bool isEmpty();
    virtual bool isPossible(CardSlot*);

    Card* lastcard();

protected:
    QVector<Card*> cards;
    virtual void inArea();
    virtual bool acceptDrop();

private:
    CardPanel* cp;
};

#endif // CARDSLOT_H
