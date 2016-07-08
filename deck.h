#ifndef DECK_H
#define DECK_H

#include <algorithm>
#include <ctime>
#include <algorithm>
#include "card.h"
#include "cardviewer.h"

class CardSlot;
class Card;
class MainSlot;

class Deck {
public:
    Deck();
    Deck(CardViewer*);
    virtual ~Deck();

    void shuffle();
    void operator>>(MainSlot*);

    enum type {
        pik = 0,
        karo = 1,
        kier = 2,
        trefl = 3
    } t;

    enum value {
        as = 1,
        jack = 11,
        queen = 12,
        king = 13
    } v;

private:
    Card *cards[52];
    CardViewer *cd;
};

#endif // DECK_H
