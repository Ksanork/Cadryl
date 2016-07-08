#ifndef CARDSLOTINC_H
#define CARDSLOTINC_H

#include "cardslot.h"

class CardSlotInc : public CardSlot {
public:
    CardSlotInc(int value, CardPanel*);
    virtual bool isPossible(CardSlot*);

protected:
    virtual bool acceptDrop();
    virtual void inArea();

private:
    typedef CardSlot cd;
    int value;
};

#endif // CARDSLOTINC_H
