#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class ImageButton : public QPushButton {
public:
    ImageButton(QWidget*);
    ImageButton(QWidget*, const QPixmap&);
    void setPixmap(const QPixmap&);
    void setHoverPixmap(const QPixmap&);
    void setTogglePixmap(const QPixmap&);

private:
    typedef QPushButton qp;

    QPixmap pix;
    QPixmap hover;
    QPixmap toggle;
    bool hoverFlag = false;

    void mousePressEvent(QMouseEvent*);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void paintEvent(QPaintEvent*);
};

#endif // IMAGEBUTTON_H
