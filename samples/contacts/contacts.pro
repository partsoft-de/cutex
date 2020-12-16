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
    mainwindow.ui \
    contactdialog.ui

HEADERS += \
    mainwindow.h \
    contacts.h \
    contactsmodel.h \
    contact.h \
    contactdialog.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    contactsmodel.cpp \
    contact.cpp \
    contactdialog.cpp

RESOURCES += \
    contacts.qrc
