#include "mainwindow.h"

double MainWindow::perc_w = 1.0;
double MainWindow::perc_h = 1.0;

MainWindow::MainWindow() {
    std::srand(std::time(NULL));

    initWidth();
    initHeight();

    setGeometry(1, 1, perc_w * 1800, perc_h * 900);
    setStyleSheet("QMainWindow { border-image: url(:/bg/bg22.jpg); }");
    //setStyleSheet("QMainWindow { opacity: 80%; }");
    //setStyleSheet("background:transparent;");
    //setAttribute(Qt::WA_TranslucentBackground);

    setWindowOpacity(0);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    centerWindow(this);

    QPropertyAnimation *fadein = new QPropertyAnimation(this, "windowOpacity");
    fadein->setDuration(1000);
    fadein->setStartValue(0.0);
    fadein->setEndValue(1.0);
    fadein->start(QAbstractAnimation::DeleteWhenStopped);

    cp = new CardPanel();

    start = new ScaledLabel(this);
    start->setPixmap(QPixmap(":/general/logo.png").scaled(perc_w * QPixmap(":/general/logo.png").width(), perc_h * QPixmap(":/general/logo.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    start->setGeometry(0, perc_h * 70, start->pixmap()->width(), start->pixmap()->height());

    ng = new ImageButton(this);
    ng->setPixmap(QPixmap(":/general/new_game.png").scaled(perc_w * QPixmap(":/general/new_game.png").width(), perc_h * QPixmap(":/general/new_game.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ng->setHoverPixmap(QPixmap(":/general/new_game-h.png").scaled(perc_w * QPixmap(":/general/new_game-h.png").width(), perc_h * QPixmap(":/general/new_game-h.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ng->setGeometry(perc_w * 1460, perc_h *674, 314, 89);                        //(1460, 584)

    /*htp = new ImageButton(this);
    htp->setPixmap(QPixmap(":/general/how.png"));
    htp->setHoverPixmap(QPixmap(":/general/how-h.png"));
    htp->setGeometry(1460, 674, 314, 89);*/

    q = new ImageButton(this);
    q->setPixmap(QPixmap(":/general/quit.png").scaled(perc_w * QPixmap(":/general/quit.png").width(), perc_h * QPixmap(":/general/quit.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    q->setHoverPixmap(QPixmap(":/general/quit-h.png").scaled(perc_w * QPixmap(":/general/quit-h.png").width(), perc_h * QPixmap(":/general/quit-h.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    q->setGeometry(perc_w *1460, perc_h *774, 314, 89);

    sound = new ImageButton(this, QPixmap(":/general/sound.png").scaled(perc_w * QPixmap(":/general/sound.png").width(), perc_h * QPixmap(":/general/sound.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sound->setTogglePixmap(QPixmap(":/general/no-sound.png").scaled(perc_w * QPixmap(":/general/no-sound.png").width(), perc_h * QPixmap(":/general/no-sound.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sound->setGeometry(perc_w *1686, perc_h *60, 49, 49);

    about = new ImageButton(this, QPixmap(":/general/about.png").scaled(perc_w * QPixmap(":/general/about.png").width(), perc_h * QPixmap(":/general/about.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    about->setGeometry(perc_w *1616, perc_h *60, 49, 49);

    connect(ng, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(q, SIGNAL(clicked()), this, SLOT(quitAnimation()));
    connect(sound, SIGNAL(clicked()), this, SLOT(toggleMute()));
    connect(about, SIGNAL(clicked()), this, SLOT(showAbout()));

    playMusic();
}

MainWindow::~MainWindow() {
    delete ng;
    delete q;
    //delete htp;
    delete start;
    delete about;
    delete aboutDialog;
    delete player;
    delete playlist;
}

void MainWindow::centerWindow(QWidget* qd) {
   QRect r = qd->geometry();
   r.moveCenter(QApplication::desktop()->availableGeometry().center());
   qd->setGeometry(r);
}

void MainWindow::playMusic() {
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;

    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setVolume(70);

    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/1.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/2.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/3.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/4.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/5.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/6.xm").absoluteFilePath()));
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo("music/7.xm").absoluteFilePath()));
    playlist->shuffle();

    player->setPlaylist(playlist);
    player->play();
}

void MainWindow::newGame() {
    if(start != NULL) {
        QPropertyAnimation *anim = new QPropertyAnimation(start, "scale");
        anim->setDuration(200);
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        connect(anim, SIGNAL(finished()), this, SLOT(showCardPanel()));

        if(aboutDialog != NULL) hideAbout();
    }
    else showCardPanel();
}

void MainWindow::showCardPanel() {
    delete start;
    start = NULL;

    cp->setFixedSize(perc_w * 1800, perc_h * 900);
    setCentralWidget(cp);

    ng->setParent(cp);
    //htp->setParent(cp);
    q->setParent(cp);
    sound->setParent(cp);
    about->setParent(cp);

    effect = new QGraphicsOpacityEffect(cp);
    cp->setGraphicsEffect(effect);

    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(250);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, SIGNAL(finished()), this, SLOT(deleteEffect()));

    cp->newGame();
}

void MainWindow::showAbout() {
    if(aboutDialog == NULL) {
        aboutDialog = new ScaledLabel(this);
        aboutDialog->setScaledContents(true);
        aboutDialog->setPixmap(QPixmap(":/general/ad.png").scaled(perc_w * QPixmap(":/general/ad.png").width(), perc_h * QPixmap(":/general/ad.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        aboutDialog->setGeometry(400 * perc_w, perc_h * 150, aboutDialog->pixmap()->width(), aboutDialog->pixmap()->height());
        aboutDialog->setVisible(true);

        QLabel *a1 = new QLabel(aboutDialog);
        a1->setText("<a style=\"color: rgba(0, 0, 0, 0); font-size: " + QString::number(perc_h * 23) + "px; font-weight: bold; text-decoration: none\" href=\"http://antiqcool.co.uk\">www.antiqcool.co.uk</a>");
        a1->setTextFormat(Qt::RichText);
        a1->setTextInteractionFlags(Qt::TextBrowserInteraction);
        a1->setOpenExternalLinks(true);
        a1->setGeometry(perc_w * 429, perc_h * 254, perc_w * 250, perc_h * 70);
        a1->setVisible(true);

        QLabel *a2 = new QLabel(aboutDialog);
        a2->setText("<a style=\" color: rgba(0, 0, 0, 0); font-size: " + QString::number(perc_h * 23) + "px; font-weight: bold; text-decoration: none\" href=\"http://siliadityr.deviantart.com\">siliadityr.deviantart.com</a>");
        a2->setTextFormat(Qt::RichText);
        a2->setTextInteractionFlags(Qt::TextBrowserInteraction);
        a2->setOpenExternalLinks(true);
        a2->setGeometry(perc_w * 289, perc_h * 338, perc_w * 280, perc_h * 70);
        a2->setVisible(true);

        ImageButton *x = new ImageButton(aboutDialog);
        x->setHoverPixmap(QPixmap(":/general/xa.png").scaled(perc_w * QPixmap(":/general/xa.png").width(), perc_h * QPixmap(":/general/xa.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        x->setGeometry(perc_w * 750, perc_h * 395, perc_w * 85, perc_h * 84);
        x->setVisible(true);

        QPropertyAnimation *anim = new QPropertyAnimation(aboutDialog, "scale");
        anim->setDuration(200);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        connect(x, SIGNAL(clicked()), this, SLOT(hideAbout()));
    }
}

void MainWindow::hideAbout() {
    QPropertyAnimation *anim = new QPropertyAnimation(aboutDialog, "scale");
    anim->setDuration(200);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, SIGNAL(finished()), this, SLOT(deleteAbout()));
}

void MainWindow::deleteAbout() {
    delete aboutDialog;
    aboutDialog = NULL;
}

void MainWindow::deleteEffect() {
    delete effect;
}

void MainWindow::toggleMute() {
    if(player->volume() > 0) player->setVolume(0);
    else player->setVolume(70);
}

void MainWindow::quitAnimation() {
    QPropertyAnimation *fadeout = new QPropertyAnimation(this, "windowOpacity");
    fadeout->setDuration(300);
    fadeout->setStartValue(1.0);
    fadeout->setEndValue(0.0);
    fadeout->start(QAbstractAnimation::DeleteWhenStopped);

    connect(fadeout, SIGNAL(finished()), this, SLOT(quitApp()));
}

void MainWindow::initWidth() {
    perc_w = (100 * QApplication::desktop()->availableGeometry().width()) / 192000.0;
}

void MainWindow::initHeight() {
    perc_h = (100 * QApplication::desktop()->availableGeometry().height()) / 105000.0;
}

void MainWindow::quitApp() {
    QApplication::quit();
}
