#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T18:02:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TSPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    managerwindow.cpp \
    admwindow.cpp \
    dllg.cpp \
    cashierwindow.cpp

HEADERS  += mainwindow.h \
    managerwindow.h \
    admwindow.h \
    dllg.h \
    cashierwindow.h

FORMS    += mainwindow.ui \
    managerwindow.ui \
    admwindow.ui \
    dllg.ui \
    cashierwindow.ui
