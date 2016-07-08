#include "card.h"

Card::Card() {}

Card::Card(CardViewer *_cd, int _type, int _value) :
    cv(_cd),
    type(_type),
    value(_value)
{}

void Card::showCard(CardPanel *cp) {
    setPixmap(cv->getCardImage(type, value));
    setAlignment(Qt::AlignCenter);
    show(cp);
    setVisible(true);
}

void Card::setCardSlot(CardSlot *_cs) {
    cs = _cs;
}

void Card::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width()/2, height()/2);             //ustwaienie karty na środku
    if(!pixmap()->isNull()) {
        p.save();
        p.rotate(m_rot1);                           //obrót
        QRect r = pixmap()->rect();
        r.moveCenter(QPoint(0,0));
        p.drawPixmap(r, *pixmap());
        p.restore();
    }
}

void Card::animateRotation() {
    QPropertyAnimation *anim1 = new QPropertyAnimation(this, "rot1");
    anim1->setStartValue(0);
    anim1->setEndValue(-90);
    anim1->setDuration(500);

    anim1->setEasingCurve(QEasingCurve::InOutQuad);

    anim1->start(QAbstractAnimation::DeleteWhenStopped);

}

CardSlot* Card::cardSlot() {
    return cs;
}

int Card::getValue() {
    return value;
}

int Card::getType() {
    return type;
}

QPixmap Card::getImage() {
    return cv->getCardImage(type, value);
}
