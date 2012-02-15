#include "cwizard.h"
#include "styler.h"
#include "writer.h"

const QString CWizard::appName = "CWizard";
const QString CWizard::appVersion = "Elf";
const QString CWizard::orgName = "Unicorz";

CWizard::CWizard()
{
	styler = Styler::getInstance();
	setting = new QSettings("config.ini", QSettings::IniFormat);
	writer = Writer::getInstance();
}

CWizard::~CWizard(){
	if(setting){
		delete setting;
	}
	if(styler){
		delete styler;
	}
	if(writer){
		delete writer;
	}
}

CWizard *CWizard::getInstance(){
	static CWizard *instance = new CWizard();
	return instance;
}

QSettings *CWizard::getSetting() const{
	return setting;
}

QVariant CWizard::getSetting(const QString &key, const QVariant &defaultValue) const{
	return this->setting->value(key, defaultValue);
}

Styler *CWizard::getStyler() const{
	return styler;
}

Writer *CWizard::getWriter() const{
	return writer;
}

QString CWizard::getAppName() const{
	return appName;
}

QString CWizard::getAppVersion() const{
	return appVersion;
}

QString CWizard::getOrgName() const{
	return orgName;
}
