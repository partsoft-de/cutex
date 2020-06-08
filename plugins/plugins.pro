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
    plugins.h \
    qxdesignercustomwidgetcollectioninterface.h \
    qxdoubleeditplugin.h \
    qxhelpbrowserplugin.h \
    qxinteditplugin.h \
    qxresource.h \
    qxsqltableviewplugin.h \
    qxdateeditplugin.h \
    qxswipewidgetcontainerextension.h \
    qxswipewidgetextensionfactory.h \
    qxswipewidgetplugin.h \
    qxtexteditplugin.h \
    qxplaintexteditplugin.h

SOURCES += \
    qxdesignercustomwidgetcollectioninterface.cpp \
    qxdoubleeditplugin.cpp \
    qxhelpbrowserplugin.cpp \
    qxinteditplugin.cpp \
    qxsqltableviewplugin.cpp \
    qxdateeditplugin.cpp \
    qxswipewidgetcontainerextension.cpp \
    qxswipewidgetextensionfactory.cpp \
    qxswipewidgetplugin.cpp \
    qxtexteditplugin.cpp \
    qxplaintexteditplugin.cpp

RESOURCES += \
    plugins.qrc
