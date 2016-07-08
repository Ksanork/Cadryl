#include "draglabel.h"
#include "cardpanel.h"

DragLabel::DragLabel() {}

DragLabel::DragLabel(CardPanel *qw) : QLabel(qw) {
    parent = qw;
}


void DragLabel::setDragable(bool drag) {
    dragable = drag;
}

void DragLabel::enterEvent(QEvent*) {
    if(dragable)
        setCursor(Qt::OpenHandCursor);
    else setCursor(Qt::ArrowCursor);
}

void DragLabel::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons() == Qt::LeftButton && dragable) {
        this->move(mapToParent(e->pos() - offset));

    }
}

void DragLabel::mousePressEvent(QMouseEvent *e) {
    if(dragable) {
        parent->setDrag(this);

        setCursor(Qt::ClosedHandCursor);
        this->offset = e->pos();
        //lastposition = geometry();
        this->raise();
    }
}

void DragLabel::mouseReleaseEvent(QMouseEvent *e) {
    if(dragable) {
        setCursor(Qt::OpenHandCursor);
        e->ignore();
    }
}

void DragLabel::animate() {
    parent->setDrag(NULL);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(geometry());
    animation->setEndValue(lastposition);

    animation->setEasingCurve(QEasingCurve::InOutQuad);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DragLabel::setLastPosition(const QRect &qp) {
    lastposition = qp;
}

void DragLabel::setLastPosition() {
    setLastPosition(lastposition);
}

void DragLabel::show(CardPanel *cp) {
    setParent(cp);
    parent = cp;
}
