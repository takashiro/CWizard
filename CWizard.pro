#-------------------------------------------------
#
# Project created by QtCreator 2011-12-23T12:24:53
#
#-------------------------------------------------

QT       += core gui

TARGET = CWizard
TEMPLATE = app


SOURCES += src/main.cpp \
	src/core/styler.cpp \
	src/core/cwizard.cpp \
	src/core/writer.cpp \
	src/dialog/stylerwindow.cpp \
	src/dialog/settingdialog.cpp \
	src/dialog/mainwindow.cpp \
	src/ui/tray.cpp \
    src/dialog/aboutusdialog.cpp

HEADERS  += src/core/styler.h \
	src/core/cwizard.h \
	src/core/writer.h \
	src/dialog/mainwindow.h \
	src/dialog/stylerwindow.h \
	src/dialog/settingdialog.h \
	src/ui/tray.h \
    src/dialog/aboutusdialog.h

FORMS    += src/dialog/settingdialog.ui \
	src/dialog/mainwindow.ui \
	src/dialog/stylerwindow.ui \
    src/dialog/aboutusdialog.ui

TRANSLATIONS	+= lang/en_US.ts \
	lang/zh_CN.ts \
	lang/ja_JP.ts

RC_FILE  += CWizard.rc

INCLUDEPATH += src
