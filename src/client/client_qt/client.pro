#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T11:33:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        connectionthread.cpp\
        ../../common/common.cpp \


HEADERS  += mainwindow.h\
        connectionthread.h\

INCLUDEPATH += ../../common/

LIBS += -lboost_system -lboost_thread


FORMS    += mainwindow.ui
