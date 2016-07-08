#ifndef CARD_H
#define CARD_H

#include <QtGui>
#include "draglabel.h"
#include "cardpanel.h"
#include "cardviewer.h"

class CardSlot;

class Card : public DragLabel {
Q_OBJECT
Q_PROPERTY(int rot1 READ rot1 WRITE setRot1);               //do obracania karty na CardSlotInc
public:
    Card();
    Card(CardViewer*, int, int);

    void showCard(CardPanel*);          //rysowanie karty na CardPanelu
    void setCardSlot(CardSlot*);
    CardSlot* cardSlot();
    int getValue();
    int getType();
    QPixmap getImage();

    void animateRotation();
    int rot1() const { return m_rot1; }

public slots:
    void setRot1(int r1) { m_rot1 = r1; update(); }

private:
    CardViewer *cv;
    CardSlot *cs;

    int type;
    int value;
    bool rotateFlag = false;

    int m_rot1 = 0;                                //do obracania karty na CardSlotInc
    void paintEvent(QPaintEvent *);
};

#endif // CARD_H
