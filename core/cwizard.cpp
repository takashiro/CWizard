#include "cwizard.h"

const QString CWizard::appName = "CWizard";
const QString CWizard::appVersion = "Elf";

CWizard::CWizard()
{
	styler = Styler::getInstance();
	setting = new QSettings("config.ini", QSettings::IniFormat);
	writer = Writer::getInstance();
}

CWizard::~CWizard(){
	delete setting;
	delete styler;
	delete writer;
}

CWizard *CWizard::getInstance(){
	static CWizard *instance = new CWizard();
	return instance;
}

QString CWizard::getAppName(){
	return appName;
}

QString CWizard::getAppVersion(){
	return appVersion;
}
