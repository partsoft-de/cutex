QT += \
    core \
    widgets \
    network \
    xml \
    sql \
    help

INCLUDEPATH += \
    ../../include

LIBS += \
    ../../lib/libcutex.a

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
