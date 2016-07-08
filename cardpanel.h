#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include "draglabel.h"
#include "cardviewer.h"


/*

  DragAndDrop:

  Wszystkie DropableArea znajdują sie w tablicy.
  Klasa w mouseReleaseEvent() sprawdza tablicę i wykonuje checkDropRelease()
  Odpowiada także za uruchomienie animacji (bez obrotu)

*/

class Deck;
class Card;
class CardSlot;
class CardSlotInc;
class MainSlot;

class CardPanel : public QWidget {
Q_OBJECT
public:
    CardPanel();
    virtual ~CardPanel();
    void checkWin();
    void newGame();

    void setDrag(DragLabel*);
    DragLabel* getDrag();

private:
    DragLabel *drag = NULL;              //przeciągany element

    MainSlot *ms = NULL;
    CardSlot *cs[14];
    CardSlot *slotY = NULL;
    Deck *deck = NULL;
    CardViewer *cd;

    QLabel *cond = NULL;                //obraz wyniku
    bool condFlag = false;              //czy został pokazany wynik, potrzebne aby się nie dublowały na raz
    QMediaPlayer *condp = NULL;         //muzyka przy wyniku
    QGraphicsOpacityEffect *effect;     //fade-in przy przegranej

    bool checkDefeat();
    void mouseReleaseEvent(QMouseEvent*);

private slots:
    void win();
    void defeat();
    void deleteEffect();
};

#endif // CARDPANEL_H
