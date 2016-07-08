#include "cardpanel.h"
#include "deck.h"
#include "mainslot.h"
#include "cardslot.h"
#include "cardslotinc.h"
#include "mainwindow.h"

CardPanel::CardPanel(){
    setGeometry(MainWindow::perc_w * 10, MainWindow::perc_h * 10, MainWindow::perc_w * 1000, MainWindow::perc_h * 900);

    cd = new CardViewer();

    cs[0] = new CardSlot(this);
    cs[0]->setGeometry(MainWindow::perc_w * 420, MainWindow::perc_h * 100, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    cs[1] = new CardSlot(this);
    cs[1]->setGeometry(MainWindow::perc_w * 670, MainWindow::perc_h * 100, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    cs[2] = new CardSlot(this);
    cs[2]->setGeometry(MainWindow::perc_w * 920, MainWindow::perc_h * 100, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    cs[3] = new CardSlot(this);
    cs[3]->setGeometry(MainWindow::perc_w * 420, MainWindow::perc_h * 350, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    cs[4] = new CardSlot(this);
    cs[4]->setGeometry(MainWindow::perc_w * 670, MainWindow::perc_h * 350, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    cs[5] = new CardSlot(this);
    cs[5]->setGeometry(MainWindow::perc_w * 920, MainWindow::perc_h * 350, MainWindow::perc_w * 150, MainWindow::perc_h * 206);


    //asy
    cs[10] = new CardSlotInc(1, this);
    cs[10]->setGeometry(MainWindow::perc_w * 120, MainWindow::perc_h * 50, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[11] = new CardSlotInc(1, this);
    cs[11]->setGeometry(MainWindow::perc_w * 120, MainWindow::perc_h * 250, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[12] = new CardSlotInc(1, this);
    cs[12]->setGeometry(MainWindow::perc_w * 120, MainWindow::perc_h * 450, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[13] = new CardSlotInc(1, this);
    cs[13]->setGeometry(MainWindow::perc_w * 120, MainWindow::perc_h * 650, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    //dwójki
    cs[6] = new CardSlotInc(2, this);
    cs[6]->setGeometry(MainWindow::perc_w * 1170, MainWindow::perc_h * 50, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[7] = new CardSlotInc(2, this);
    cs[7]->setGeometry(MainWindow::perc_w * 1170, MainWindow::perc_h * 250, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[8] = new CardSlotInc(2, this);
    cs[8]->setGeometry(MainWindow::perc_w * 1170, MainWindow::perc_h * 450, MainWindow::perc_w * 206, MainWindow::perc_h * 150);

    cs[9] = new CardSlotInc(2, this);
    cs[9]->setGeometry(MainWindow::perc_w * 1170, MainWindow::perc_h * 650, MainWindow::perc_w * 206, MainWindow::perc_h * 150);


    slotY = new CardSlot(this);
    slotY->setGeometry(MainWindow::perc_w * 600, MainWindow::perc_h * 630, MainWindow::perc_w * 150, MainWindow::perc_h * 206);

    ms = new MainSlot(this, cd, slotY);
    ms->setGeometry(MainWindow::perc_w * 800, MainWindow::perc_h * 620, MainWindow::perc_w * 170, MainWindow::perc_h * 230);
    ms->show();

    deck = new Deck(cd);
    condp = new QMediaPlayer;
    condp->setVolume(110);
}

CardPanel::~CardPanel() {
    ms->clean();
    delete ms;
    delete deck;
    //delete cd;
    delete slotY;
    delete cond;
    delete condp;
}

void CardPanel::newGame() {
    for(CardSlot* c : cs) c->clean();     //czyszczenie wektorów
    ms->clean();                          //usuwanie kart z ekranu i czyszczenie tablicy
    slotY->clean();                       //czyszczenie wektorów

    deck->shuffle();

    ms->setVisible(true);
    condFlag = false;

    //usuwanie wyniku
    if(cond != NULL) {
        delete cond;
        cond = NULL;
    }

    *deck >> ms;    //dodanie wszytskich kart z tali do MainSlot

    //początkowe 6 kart
    *cs[0] << ms;
    *cs[1] << ms;
    *cs[2] << ms;
    *cs[3] << ms;
    *cs[4] << ms;
    *cs[5] << ms;
}

void CardPanel::checkWin() {
    if(ms->isEmpty()) {
        if(slotY->isEmpty() &&
           cs[0]->isEmpty() &&
           cs[1]->isEmpty() &&
           cs[2]->isEmpty() &&
           cs[3]->isEmpty() &&
           cs[4]->isEmpty() &&
           cs[5]->isEmpty() &&
           ms->isEmpty()
          )
        {
            if(!condFlag) QTimer::singleShot(1000, this, SLOT(win()));
            condFlag = true;

        }
        else if(checkDefeat()) {
           if(!condFlag) QTimer::singleShot(1000, this, SLOT(defeat()));
           condFlag = true;
        }
    }
}

void CardPanel::win() {
    condp->setMedia(QUrl::fromLocalFile(QFileInfo("music/victory.xm").absoluteFilePath()));
    condp->play();

    cond = new QLabel(this);
    cond->setPixmap(QPixmap(":/general/victory.png").scaled(MainWindow::perc_w*QPixmap(":/general/victory.png").width(), MainWindow::perc_h*QPixmap(":/general/victory.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    cond->setGeometry(MainWindow::perc_w*130, MainWindow::perc_h*(0-cond->pixmap()->height()), cond->pixmap()->width(), cond->pixmap()->height());

    QPropertyAnimation *anim = new QPropertyAnimation(cond, "geometry");
    anim->setDuration(550);
    anim->setStartValue(QRect(MainWindow::perc_w * 130, MainWindow::perc_h * 0-cond->pixmap()->height(), MainWindow::perc_w * cond->pixmap()->width(), MainWindow::perc_h * cond->pixmap()->height()));
    anim->setEndValue(QRect(MainWindow::perc_w * 130, MainWindow::perc_h * 52, cond->pixmap()->width(), cond->pixmap()->height()));
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    cond->setVisible(true);
}

void CardPanel::defeat() {
    condp->setMedia(QUrl::fromLocalFile(QFileInfo("music/defeat.xm").absoluteFilePath()));
    condp->play();

    cond = new QLabel(this);
    cond->setPixmap(QPixmap(":/general/defeat.png").scaled(MainWindow::perc_w*QPixmap(":/general/defeat.png").width(), MainWindow::perc_h*QPixmap(":/general/defeat.png").height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    effect = new QGraphicsOpacityEffect(cond);
    cond->setGraphicsEffect(effect);

    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(3500);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    cond->setGeometry(MainWindow::perc_w * 222, MainWindow::perc_h * 15, cond->pixmap()->width(), cond->pixmap()->height());
    cond->setVisible(true);

    connect(anim, SIGNAL(finished()), this, SLOT(deleteEffect()));
}

bool CardPanel::checkDefeat() {
    //sprawdzanie slotów asów i dwójek ze slotami środkowymi i Y
    for(int i = 6; i < 14; i++) {
        for(int j = 0; j < 6; j++) {
            if(cs[i]->isPossible(cs[j]))
                return false;
        }
        if(cs[i]->isPossible(slotY)) return false;
    }

    //sprawdzanie slotów środkowych między sobą i Y
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(cs[i]->isPossible(cs[j]))
                return false;
        }
        if(cs[i]->isPossible(slotY)) return false;
    }

    return true;
}

void CardPanel::mouseReleaseEvent(QMouseEvent*) {
    if(drag != NULL) {
        for(CardSlot* c : cs) c->checkDropRelease();
        drag->animate();
        checkWin();
    }
}

void CardPanel::setDrag(DragLabel *d) {
    drag = d;
}

DragLabel* CardPanel::getDrag() {
    return drag;
}

void CardPanel::deleteEffect() {
    delete effect;
}
