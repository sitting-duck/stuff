#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T07:43:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tree_view_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    simpletreemodel.qrc
