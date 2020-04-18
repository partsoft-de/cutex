TEMPLATE = lib
TARGET = qxwidgets
DESTDIR = ../lib

QT += \
    core \
    widgets \
    network \
    xml \
    sql \
    help \
    designer \
    uiplugin

CONFIG += \
    shared \
    plugin

INCLUDEPATH += \
    ../include

LIBS += \
    ../lib/libcutex.a

HEADERS += \
    qxdesignercustomwidgetcollectioninterface.h \
    qxdoubleeditplugin.h \
    qxhelpbrowserplugin.h \
    qxinteditplugin.h \
    qxsqltableviewplugin.h \
    qxdateeditplugin.h \
    qxtexteditplugin.h \
    qxplaintexteditplugin.h

SOURCES += \
    qxdesignercustomwidgetcollectioninterface.cpp \
    qxdoubleeditplugin.cpp \
    qxhelpbrowserplugin.cpp \
    qxinteditplugin.cpp \
    qxsqltableviewplugin.cpp \
    qxdateeditplugin.cpp \
    qxtexteditplugin.cpp \
    qxplaintexteditplugin.cpp
