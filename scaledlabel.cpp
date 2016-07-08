#include "scaledlabel.h"
#include <QApplication>

ScaledLabel::ScaledLabel(QWidget *p) : QLabel(p)
{

}

void ScaledLabel::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width()/2, height()/2);
    if(!pixmap()->isNull()) {
        p.save();
        p.scale(m_scale, m_scale);
        /*QPixmap scaled  = pixmap()->scaled(
                       m_scale * pixmap()->width(), m_scale * pixmap()->height()

                  );*/
        QRect r = rect();
        r.moveCenter(QPoint(0,0));
        if(!pixmap()->isNull()) p.drawPixmap(r, *pixmap());
        //if(!text().isNull()) p.drawText(r, text());
        p.restore();
    }
}
