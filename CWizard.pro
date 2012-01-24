#-------------------------------------------------
#
# Project created by QtCreator 2011-12-23T12:24:53
#
#-------------------------------------------------

QT       += core gui

TARGET = CWizard
TEMPLATE = app


SOURCES += main.cpp\
    dialog/settingdialog.cpp \
    dialog/mainwindow.cpp \
	core/styler.cpp \
    core/cwizard.cpp \
    core/tray.cpp \
    dialog/stylerwindow.cpp

HEADERS  += \
    dialog/mainwindow.h \
	core/styler.h \
    core/cwizard.h \
    core/tray.h \
    dialog/stylerwindow.h \
    dialog/settingdialog.h

FORMS    += dialog/settingdialog.ui \
    dialog/mainwindow.ui \
    dialog/stylerwindow.ui
