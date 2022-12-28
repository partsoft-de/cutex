QT += \
    core \
    widgets \
    network \
    xml \
    sql \
    help

CONFIG += c++11

INCLUDEPATH += \
    ../../include

LIBS += \
    ../../lib/libcutex_$${QT_ARCH}.a

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    gantt.h

SOURCES += \
    mainwindow.cpp \
    main.cpp
