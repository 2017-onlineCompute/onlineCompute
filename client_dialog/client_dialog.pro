#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T09:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clientdialog
TEMPLATE = app


SOURCES += main.cpp \
    clientdialog.cpp

HEADERS  += \
    clientdialog.h

FORMS    += \
    clientdialog.ui
QMAKE_LFLAGS += -lboost_system -lboost_thread
