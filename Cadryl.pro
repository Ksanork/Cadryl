#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T12:01:21
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cadryl
TEMPLATE = app
RC_ICONS += cadryl.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    cardpanel.cpp \
    draglabel.cpp \
    dropablearea.cpp \
    card.cpp \
    deck.cpp \
    cardviewer.cpp \
    mainslot.cpp \
    cardslot.cpp \
    cardslotinc.cpp \
    imagebutton.cpp \
    scaledlabel.cpp \
    strokelabel.cpp

HEADERS  += mainwindow.h \
    cardpanel.h \
    dropablearea.h \
    draglabel.h \
    card.h \
    deck.h \
    cardviewer.h \
    mainslot.h \
    cardslot.h \
    cardslotinc.h \
    imagebutton.h \
    scaledlabel.h \
    strokelabel.h

RESOURCES += \
    media.qrc

QMAKE_CXXFLAGS += -std=c++11
QTPLUGIN += qsqloci qgif
