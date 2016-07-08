#include "dropablearea.h"


DropableArea::DropableArea(CardPanel *cp) : QWidget(cp) {
    parent = cp;
    std::srand(std::time(NULL));
}

void DropableArea::checkDropRelease() {
    if(acceptDrop()) {
        //if(this->rect().contains(mapFromGlobal(QCursor::pos()))) {
        if(QRect(pos(), size()).intersects(QRect(parent->getDrag()->pos(), parent->getDrag()->size()))) {
            if(asStack) {
                parent->getDrag()->setLastPosition(
                            QRect(randPosition(pos()), parent->getDrag()->size())
                        );
            }
            else {
                parent->getDrag()->setLastPosition(
                        QRect(pos(), parent->getDrag()->size())
                    );
            }
            inArea();
        }
    }
}

QPoint DropableArea::randPosition(const QPoint &p) {
    int x = (qrand() % 16) - 8;
    int y = (qrand() % 16) - 8;

    return QPoint(p.x() + x, p.y() + y);
    //return QPoint(p.x(), p.y());
}

void DropableArea::inArea() {}

bool DropableArea::acceptDrop() {
    return true;
}

void DropableArea::setViewAsStack(bool b) {
    asStack = b;
}
