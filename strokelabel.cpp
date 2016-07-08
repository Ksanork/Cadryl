#include "strokelabel.h"
#include "mainwindow.h"

StrokeLabel::StrokeLabel(QWidget *w) : QLabel(w)
{
}

void StrokeLabel::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    //do obrysu
    QPen pen(QColor("#000000"));
    p.setPen(pen);
    pen.setWidth(10);
    pen.setStyle(Qt::SolidLine);

    //utworzenie ścieżki z tekstu
    QPainterPath path;

    path.addText(MainWindow::perc_w * 75, MainWindow::perc_h * 50, QFont("Calibri", font().pixelSize(), QFont::Bold), text());
    path.translate(-0.1*path.length(), 0);

    //dodanie i rysowanie obrysu ścieżki
    QPainterPathStroker qps;
    p.setBrush(QBrush(Qt::black));
    qps.setWidth(6);
    p.drawPath(qps.createStroke(path));

    //ryswoanie ścieżki
    p.setBrush(QBrush(Qt::white));
    p.drawPath(path);
}

void StrokeLabel::mouseReleaseEvent(QMouseEvent *e) {
    e->ignore();
}
