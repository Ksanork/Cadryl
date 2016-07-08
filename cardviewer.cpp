#include "cardviewer.h"
#include "mainwindow.h"

CardViewer::CardViewer() {

}

QPixmap CardViewer::getDeckImage() {
    return QPixmap(":/bg/back22.png").scaled(MainWindow::perc_w * 169, MainWindow::perc_h * 229,  Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //return QPixmap(":/cards/back.png").scaled(170, 236);
    //return QPixmap(":/cards/back.jpg").scaled(150, 206);
}

QPixmap CardViewer::getCardImage(int type, int value) {
    QString name(":/cards/" + QString::number(type) + "-" + QString::number(value)  + ".png");
    return QPixmap(name).scaled(MainWindow::perc_w * 150, MainWindow::perc_h * 206,  Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
