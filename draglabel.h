#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPropertyAnimation>
#include <QEvent>

class CardPanel;

class DragLabel : public QLabel {
public:
    DragLabel();
    DragLabel(CardPanel*);

    void setLastPosition();                      //dokąd ma być animowany
    void setLastPosition(const QRect&);
    void animate();
    void show(CardPanel*);
    void setDragable(bool);

private:
    CardPanel *parent;
    bool dragable = true;
    QPoint offset;                              //potrzebne do przeciąganie
    QRect lastposition;

    void enterEvent(QEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

};

#endif // DRAGLABEL_H
