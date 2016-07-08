#include "imagebutton.h"

ImageButton::ImageButton(QWidget *p) : QPushButton(p)
{}

ImageButton::ImageButton(QWidget *p, const QPixmap &_pix) :
    pix(_pix),
    QPushButton(p)
{}

void ImageButton::setPixmap(const QPixmap &p) {
    pix = p;
}

void ImageButton::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    if(!pix.isNull() || !hover.isNull()) {
        if(!hoverFlag || hover.isNull()) {
            QRect r = pix.rect();
            p.drawPixmap(r, pix);
        }
        else {
            QRect r = hover.rect();
            p.drawPixmap(r, hover);
        }
    }
}

void ImageButton::setHoverPixmap(const QPixmap &p) {
    hover = p;
}

void ImageButton::setTogglePixmap(const QPixmap &p) {
    toggle = p;
}

void ImageButton::mousePressEvent(QMouseEvent *e) {
    qp::mousePressEvent(e);

    if(e->button() == Qt::LeftButton && !toggle.isNull()) {
        QPixmap p = pix;
        pix = toggle;
        toggle = p;
    }
}

void ImageButton::enterEvent(QEvent *) {
    setCursor(Qt::PointingHandCursor);
    hoverFlag = true;
}

void ImageButton::leaveEvent(QEvent *) {
    hoverFlag = false;
}
