#-------------------------------------------------
#
# Project created by QtCreator 2018-12-09T17:45:36
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathPlanning
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    myagent.cpp \
    graph.cpp \
    PathFinder.cpp \
    obstacle.cpp \
    myscene.cpp

HEADERS  += dialog.h \
    myagent.h \
    graph.h \
    obstacle.h \
    myscene.h

FORMS    += dialog.ui

RESOURCES += \
    img.qrc

CONFIG += c++11
