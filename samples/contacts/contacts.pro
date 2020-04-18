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
