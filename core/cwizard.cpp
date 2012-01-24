#include "cwizard.h"

CWizard::CWizard()
{
	styler = new Styler();
	setting = new QSettings("config.ini", QSettings::IniFormat);
	version = "Elf";

	settingDialog = new SettingDialog();

	stylerWindow = new StylerWindow();
	stylerWindow->styler = styler;
}

CWizard::~CWizard(){
	delete setting;
	delete styler;
}

QString CWizard::getVersion(){
	return version;
}

void CWizard::setMainWindow(MainWindow *mainWindow){
	this->mainWindow = mainWindow;
	mainWindow->settingDialog = this->settingDialog;
	mainWindow->stylerWindow = this->stylerWindow;
}
