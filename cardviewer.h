#ifndef CARDVIEWER_H
#define CARDVIEWER_H

#include <QWidget>

class CardViewer {
public:
    CardViewer();

    QPixmap getCardImage(int, int);
    QPixmap getDeckImage();

};

#endif // CARDVIEWER_H
