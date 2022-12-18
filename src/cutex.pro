TEMPLATE = lib
TARGET = cutex_$${QT_ARCH}
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

equals(QT_MAJOR_VERSION, 6) {
    error(Qt $$QT_VERSION is not supported yet!)
}

android: ANDROID_ABIS = armeabi-v7a arm64-v8a

INCLUDEPATH += \
    ../include

HEADERS += \
    ../include/qxcalculatordialog.h \
    ../include/qxdoubleedit.h \
    ../include/qxexception.h \
    ../include/qxintedit.h \
    ../include/qxlogger.h \
    ../include/qxmousegripband.h \
    ../include/qxoptional.h \
    ../include/qxsingleton.h \
    ../include/qxsqlrecord.h \
    ../include/qxswipebar.h \
    ../include/qxswipebutton.h \
    ../include/qxswipewidget.h \
    ../include/qxtimeedit.h \
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
    qxcalculatordialog.cpp \
    qxdoubleedit.cpp \
    qxexception.cpp \
    qxintedit.cpp \
    qxlogger.cpp \
    qxmousegripband.cpp \
    qxoptional.cpp \
    qxsingleton.cpp \
    qxsqlrecord.cpp \
    qxswipebar.cpp \
    qxswipebutton.cpp \
    qxswipewidget.cpp \
    qxtimeedit.cpp \
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
    qxcalculatordialog.ui \
    qxmessagedialog.ui \
    qxhelpwindow.ui \
    qxfinddialog.ui

RESOURCES += \
    cutex.qrc

TRANSLATIONS += \
    cutex_en.ts

