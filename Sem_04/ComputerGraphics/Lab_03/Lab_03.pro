#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T03:31:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab_03
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    algoritms.cpp

HEADERS  += \
    mainwindow.hpp \
    algoritms.hpp \
    objectwrapper.hpp \
    timer.hpp

FORMS    += \
    mainwindow.ui
