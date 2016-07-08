#include "deck.h"
#include "mainslot.h"

Deck::Deck(){}

Deck::Deck(CardViewer *_cd) : cd(_cd) {
    std::srand(std::time(NULL));   
    shuffle();
}

Deck::~Deck() {
    delete []cards;
}

void Deck::shuffle() {
    int i = 0;
    for(int j = 0; j < 4; j++) {            //kolory
        for(int l = 1; l < 14; l++)         //warości
              cards[i++] = new Card(cd, j, l);
    }
    std::random_shuffle(cards, cards+52);
}

void Deck::operator>>(MainSlot *cs) {
    /*for(int i = 0; i < 52; i++)
        cs->cards[i] = cards[i];*/
    cs->addCards(cards);
}
