#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T22:07:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    client.cpp \
    server.cpp \
    hostchatdialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    client.h \
    server.h \
    hostchatdialog.h \
    server.h

FORMS    += mainwindow.ui \
    dialog.ui
