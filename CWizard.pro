#-------------------------------------------------
#
# Project created by QtCreator 2011-12-23T12:24:53
#
#-------------------------------------------------

QT       += core gui

TARGET = CWizard
TEMPLATE = app


SOURCES += main.cpp \
	core/styler.cpp \
    core/cwizard.cpp \
	core/writer.cpp \
    dialog/stylerwindow.cpp \
	dialog/settingdialog.cpp \
	dialog/mainwindow.cpp \
    ui/tray.cpp

HEADERS  += core/styler.h \
	core/cwizard.h \
	core/writer.h \
	dialog/mainwindow.h \
    dialog/stylerwindow.h \
    dialog/settingdialog.h \
    ui/tray.h

FORMS    += dialog/settingdialog.ui \
    dialog/mainwindow.ui \
    dialog/stylerwindow.ui

TRANSLATIONS	+= lang/zh_CN.ts \
	lang/ja_JP.ts
