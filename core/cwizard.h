#ifndef CWIZARD_H
#define CWIZARD_H

#include <QSettings>

#include "core/styler.h"

#include "dialog/settingdialog.h"
#include "dialog/stylerwindow.h"
#include "dialog/mainwindow.h"

class CWizard{
private:
	QString version;

public:
    CWizard();
	~CWizard();

	QSettings *setting;
	Styler *styler;

	MainWindow *mainWindow;
	SettingDialog *settingDialog;
	StylerWindow *stylerWindow;

	void setMainWindow(MainWindow *mainWindow);

	QString getVersion();
};

#endif // CWIZARD_H
