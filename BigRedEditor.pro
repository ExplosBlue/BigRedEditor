#-------------------------------------------------
#
# Project created by QtCreator 2018-12-30T18:08:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigRedEditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    maineditorwidget.cpp \
    fileeditorwidget.cpp \
    worldeditorwidget.cpp \
    levelcompletionwidget.cpp \
    starcoinwidget.cpp \
    coinrushstagewidget.cpp \
    coinscorewidget.cpp

HEADERS += \
        mainwindow.h \
    maineditorwidget.h \
    fileeditorwidget.h \
    worldeditorwidget.h \
    levelcompletionwidget.h \
    starcoinwidget.h \
    coinrushstagewidget.h \
    coinscorewidget.h \
    bigredsave.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
