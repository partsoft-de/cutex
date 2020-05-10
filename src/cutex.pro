TEMPLATE = lib
TARGET = cutex
DESTDIR = ../lib

mkpath(../lib)

QT += \
    core \
    widgets \
    network \
    xml \
    sql \
    help

# optionale Module (nicht in allen Qt-Versionen verfügbar)
#QT += webkitwidgets

CONFIG += \
    c++11 \
    staticlib \

INCLUDEPATH += \
    ../include

HEADERS += \
    ../include/qxdoubleedit.h \
    ../include/qxexception.h \
    ../include/qxintedit.h \
    ../include/qxsingleton.h \
    ../include/qxwizard.h \
    ../include/qxwaitcursor.h \
    ../include/qxuifield.h \
    ../include/qxrandom.h \
    ../include/qxmessagedialog.h \
    ../include/qxmessage.h \
    ../include/qxmainwindow.h \
    ../include/qxform.h \
    ../include/qxfixpoint.h \
    ../include/qxdialog.h \
    ../include/cutex.h \
    ../include/qxapplication.h \
    ../include/qxcrypt.h \
    ../include/qxrecentfiles.h \
    ../include/qxhelpbrowser.h \
    ../include/qxhelpwindow.h \
    ../include/qxresource.h \
    ../include/qxtreeitem.h \
    ../include/qxtreeitemmodel.h \
    ../include/qxfinddialog.h \
    ../include/qxfindoptions.h \
    ../include/qxhtmlcursor.h \
    ../include/qxhyperlink.h \
    ../include/qxtextedit.h \
    ../include/qxtextdocument.h \
    ../include/qxhelpmanager.h \
    ../include/qxhelpreply.h \
    ../include/qxspellchecker.h \
    ../include/qxdashboard.h \
    ../include/qxsqlscript.h \
    ../include/qxsqldatabase.h \
    ../include/qxsqlquerymodel.h \
    ../include/qxsqltableview.h \
    ../include/qxdateedit.h \
    ../include/qxmath.h \
    ../include/qxstyleditemdelegate.h \
    ../include/qxdatevalidator.h \
    ../include/qxtimevalidator.h \
    ../include/qxplaintextedit.h \
    ../include/qxlinenumberarea.h \
    ../include/qxxmldocument.h \
    ../include/qxxmlnode.h

SOURCES += \
    qxdoubleedit.cpp \
    qxexception.cpp \
    qxintedit.cpp \
    qxsingleton.cpp \
    qxwizard.cpp \
    qxuifield.cpp \
    qxrandom.cpp \
    qxmainwindow.cpp \
    qxform.cpp \
    qxfixpoint.cpp \
    qxdialog.cpp \
    qxwaitcursor.cpp \
    qxmessage.cpp \
    qxmessagedialog.cpp \
    qxapplication.cpp \
    qxcrypt.cpp \
    qxrecentfiles.cpp \
    qxhelpbrowser.cpp \
    qxhelpwindow.cpp \
    qxtreeitem.cpp \
    qxtreeitemmodel.cpp \
    qxfinddialog.cpp \
    qxfindoptions.cpp \
    qxhtmlcursor.cpp \
    qxhyperlink.cpp \
    qxtextedit.cpp \
    qxtextdocument.cpp \
    qxhelpmanager.cpp \
    qxhelpreply.cpp \
    qxspellchecker.cpp \
    qxdashboard.cpp \
    qxsqlscript.cpp \
    qxsqldatabase.cpp \
    qxsqlquerymodel.cpp \
    qxsqltableview.cpp \
    qxdateedit.cpp \
    qxmath.cpp \
    qxstyleditemdelegate.cpp \
    qxdatevalidator.cpp \
    qxtimevalidator.cpp \
    qxplaintextedit.cpp \
    qxlinenumberarea.cpp \
    qxxmldocument.cpp \
    qxxmlnode.cpp

FORMS += \
    qxmessagedialog.ui \
    qxhelpwindow.ui \
    qxfinddialog.ui

RESOURCES += \
    cutex.qrc

TRANSLATIONS += \
    cutex_en.ts
