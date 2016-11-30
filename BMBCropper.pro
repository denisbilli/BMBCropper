#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T19:54:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BMBCropper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    framegenerator.cpp \
    weddingframegenerator.cpp \
    reportageframegenerator.cpp \
    frameoption.cpp \
    abstractoption.cpp

HEADERS  += mainwindow.h \
    framegenerator.h \
    weddingframegenerator.h \
    reportageframegenerator.h \
    frameoption.h \
    abstractoption.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
