#ifndef STROKELABEL_H
#define STROKELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QPen>

class StrokeLabel : public QLabel {
public:
    StrokeLabel(QWidget*);
    void paintEvent(QPaintEvent*);

private:
    typedef QLabel ql;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // STROKELABEL_H
