#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T22:57:06
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Axolotl
TEMPLATE = app
CONFIG += c++11
LIBS += /usr/lib/libcryptopp.so
LIBS += /usr/lib/aarch64-linux-gnu/libboost_system.so


SOURCES += main.cpp\
        mainwindow.cpp \
    musicpage.cpp \
    data.cpp \
    viewer.cpp

HEADERS  += mainwindow.h \
    musicpage.h \
    data.h \
    viewer.h

FORMS    += mainwindow.ui \
    musicpage.ui \
    data.ui \
    viewer.ui
