TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
QMAKE_LFLAGS += -lboost_system -lboost_thread -lpthread

HEADERS += \
    compute.h
