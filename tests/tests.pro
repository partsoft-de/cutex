QT += \
    core \
    widgets \
    network \
    xml \
    sql \
    help \
    testlib

CONFIG += c++11

INCLUDEPATH += \
    ../include

LIBS += \
    ../lib/libcutex_$${QT_ARCH}.a

SOURCES += \
    fixpoint.cpp
