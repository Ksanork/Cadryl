#include "mainslot.h"
#include "card.h"
#include "mainwindow.h"

MainSlot::MainSlot(CardPanel *cp, CardViewer *_cd, CardSlot *_slotY) :
    cd(_cd),
    slotY(_slotY),
    QLabel(cp)
{
    std::srand(std::time(NULL));

    amount = new StrokeLabel(this);
    amount->setGeometry((MainWindow::perc_w * this->width())/2-(MainWindow::perc_w * 35), (MainWindow::perc_h * this->height())/2+(MainWindow::perc_h * 65), 150, 80);
    amount->setVisible(true);
    amount->setText("45");

    int fontSize =  MainWindow::perc_h * 50;

    amount->setStyleSheet("color: white; font-size: " + QString::number(fontSize) + "px; font-weight: 500;");
    amount->setAlignment(Qt::AlignCenter);
}

Card* MainSlot::getCard() {
    amount->setText(QString::number(current));
    return cards[current--];
}

void MainSlot::addCards(Card *c[52]) {
    for(int i = 0; i < 52; i++)
        cards[i] = c[i];
}

void MainSlot::show() {
    setPixmap(cd->getDeckImage());
}

QPoint MainSlot::randPosition() {
    int x = (qrand() % 16) - 8 + 8;
    int y = (qrand() % 16) - 8 + 8;

    return QPoint(x, y);
}

void MainSlot::setSlotY(CardSlot *cs) {
    slotY = cs;
}

void MainSlot::mouseReleaseEvent(QMouseEvent *qe) {
    if(qe->button() == Qt::LeftButton) {
        *slotY << this;

        if(current < 0) setVisible(false);

        CardPanel *cp = dynamic_cast<CardPanel*>(parent());
        cp->checkWin();
    } 
}


void MainSlot::enterEvent(QEvent*) {
    setCursor(Qt::PointingHandCursor);
}

void MainSlot::clean() {
    if(current < 51) {
        for(int i = 0; i < 52; i++) {
            cards[i]->deleteLater();
            cards[i] = NULL;
        }
        current = 51;
    }
}

bool MainSlot::isEmpty() {
    return (current < 0);
}
