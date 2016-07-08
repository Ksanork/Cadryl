#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <ctime>
#include "deck.h"
#include "mainslot.h"
#include "imagebutton.h"
#include "scaledlabel.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

    static double perc_w;// = 0.9375;
    static double perc_h;// = 0.9;

private:
    CardPanel *cp = NULL;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    ImageButton *ng = NULL;
    ImageButton *q = NULL;
    //ImageButton *htp = NULL;
    ImageButton *sound = NULL;
    ImageButton *about = NULL;

    ScaledLabel *start = NULL;
    ScaledLabel *aboutDialog = NULL;
    void centerWindow(QWidget*);

    void playMusic();

    QGraphicsOpacityEffect *effect = NULL;

    void initWidth();
    void initHeight();

private slots:
    void newGame();
    void showCardPanel();
    void deleteEffect();
    void toggleMute();
    void quitAnimation();
    void quitApp();
    void showAbout();
    void hideAbout();
    void deleteAbout();
};

#endif // MAINWINDOW_H
