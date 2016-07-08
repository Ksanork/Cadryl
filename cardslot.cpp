#include "cardslot.h"
#include "card.h"

CardSlot::CardSlot(CardPanel *_cp) : cp(_cp), DropableArea(_cp) {
    setStyleSheet("background-color: rgba(255, 255, 255, 0.2)");
}

Card* CardSlot::lastcard() {
    return cards.last();
}

void CardSlot::operator<<(CardSlot *cs)  {
    if(!cards.isEmpty()) {
        this->cards.last()->setDragable(false);
        setViewAsStack(true);
    }
    else setViewAsStack(false);

    this->cards.push_back(cs->cards.last());

    if(asStack) {
        cs->cards.last()->setLastPosition(
                    QRect(randPosition(pos()), size())
        );
    }
    else cs->cards.last()->setLastPosition(geometry());

    cs->cards.last()->setDragable(true);
    cs->cards.pop_back();

    if(!cs->cards.isEmpty()) cs->cards.last()->setDragable(true);
}

void CardSlot::operator<<(MainSlot *cs)  {
    Card* c = cs->getCard();
    c->setCardSlot(this);
    c->setLastPosition(geometry());

    if(!cards.isEmpty()) {
        cards.last()->setDragable(false);
        setViewAsStack(true);
    }
    else setViewAsStack(false);

    this->cards.push_back(c);
    cards.last()->showCard(cp);
    show();
}

/*void CardSlot::operator<<(Deck *cs)  {
    this->cards.push_back(cs->getCard());
    show();
}*/

void CardSlot::show() {
    if(asStack) {
        cards.last()->setGeometry(
                    QRect(randPosition(pos()), size()));
    }
    else cards.last()->setGeometry(QRect(pos(), size()));
}

void CardSlot::inArea() {
    Card* c = dynamic_cast<Card*>(parent->getDrag());

    *this << c->cardSlot();
    c->setCardSlot(this);
}

bool CardSlot::acceptDrop() {
    Card* c = dynamic_cast<Card*>(parent->getDrag());

    if(cards.isEmpty()) return true;
    else {
        return (c->getType() == lastcard()->getType() &&
                c->getValue() == (lastcard()->getValue()-1));
    }
}

void CardSlot::clean() {
    cards.clear();
}

bool CardSlot::isEmpty() {
    return cards.isEmpty();
}

bool CardSlot::isPossible(CardSlot *s) {
    if(cards.isEmpty()) return true;
    else if(s->isEmpty()) return true;
    else
        return (s->lastcard()->getType() == lastcard()->getType() &&
                s->lastcard()->getValue() == (lastcard()->getValue()-1));
}
