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
    $$PWD/../../lib/libcutex_$${QT_ARCH}.a

SOURCES += \
    addressesmodel.cpp \
    main.cpp \
    proxymodel.cpp

HEADERS += \
    addressesmodel.h \
    filterheader.h \
    proxymodel.h

RESOURCES += \
    filterheader.qrc
