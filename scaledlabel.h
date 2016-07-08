#ifndef SCALEDLABEL_H
#define SCALEDLABEL_H

#include <QtGui>
#include <QWidget>
#include <QLabel>

class ScaledLabel : public QLabel {
Q_OBJECT
Q_PROPERTY(double scale READ scale WRITE setScale);
public:
    ScaledLabel(QWidget*);
    double scale() const { return m_scale; }
    void paintEvent(QPaintEvent*);

public slots:
    void setScale(double r1) { m_scale = r1; update(); }

private:
    double m_scale = 1.0;
    int pwidth = 0, pheight = 0;
};

#endif // SCALEDLABEL_H
