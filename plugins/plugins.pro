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
    c++11 \
    shared \
    plugin

INCLUDEPATH += \
    ../include

LIBS += \
    ../lib/libcutex_$${QT_ARCH}.a

HEADERS += \
    plugins.h \
    qxdesignercustomwidgetcollectioninterface.h \
    qxdoubleeditplugin.h \
    qxganttchartplugin.h \
    qxhelpbrowserplugin.h \
    qxinteditplugin.h \
    qxresource.h \
    qxsqltableviewplugin.h \
    qxdateeditplugin.h \
    qxswipewidgetcontainerextension.h \
    qxswipewidgetextensionfactory.h \
    qxswipewidgetplugin.h \
    qxtexteditplugin.h \
    qxplaintexteditplugin.h \
    qxtimeeditplugin.h

SOURCES += \
    qxdesignercustomwidgetcollectioninterface.cpp \
    qxdoubleeditplugin.cpp \
    qxganttchartplugin.cpp \
    qxhelpbrowserplugin.cpp \
    qxinteditplugin.cpp \
    qxsqltableviewplugin.cpp \
    qxdateeditplugin.cpp \
    qxswipewidgetcontainerextension.cpp \
    qxswipewidgetextensionfactory.cpp \
    qxswipewidgetplugin.cpp \
    qxtexteditplugin.cpp \
    qxplaintexteditplugin.cpp \
    qxtimeeditplugin.cpp

RESOURCES += \
    plugins.qrc
