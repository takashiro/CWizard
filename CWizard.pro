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
    src/dialog/aboutusdialog.cpp \
    src/core/stats.cpp \
    src/ui/highlighter.cpp \
    src/ui/codeeditor.cpp \
    src/ui/unicornstyle.cpp \
    src/ui/statgraphics.cpp \
    src/dialog/statdialog.cpp

HEADERS  += src/core/styler.h \
	src/core/cwizard.h \
	src/core/writer.h \
	src/dialog/mainwindow.h \
	src/dialog/stylerwindow.h \
	src/dialog/settingdialog.h \
	src/ui/tray.h \
    src/dialog/aboutusdialog.h \
    src/core/stats.h \
    src/ui/highlighter.h \
    src/ui/codeeditor.h \
    src/ui/unicornstyle.h \
    src/ui/statgraphics.h \
	src/core/structs.h \
    src/dialog/statdialog.h

FORMS    += src/dialog/settingdialog.ui \
	src/dialog/mainwindow.ui \
	src/dialog/stylerwindow.ui \
    src/dialog/aboutusdialog.ui \
    src/dialog/statdialog.ui

TRANSLATIONS	+= lang/en_US.ts \
	lang/zh_CN.ts \
	lang/ja_JP.ts

RC_FILE  += CWizard.rc

INCLUDEPATH += src
