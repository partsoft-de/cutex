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

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    childform.cpp

FORMS += \
    mainwindow.ui \
    childform.ui

HEADERS += \
    mainwindow.h \
    mdidemo.h \
    childform.h

RESOURCES += \
    mdidemo.qrc
