#include "cwizard.h"
#include "styler.h"
#include "writer.h"
#include "stats.h"

#include <QApplication>

CWizard *CWizard::instance = NULL;
CWizard *Wizard = NULL;

const QString CWizard::appName = "CWizard";
const QString CWizard::appVersion = "Elf";
const QString CWizard::orgName = "Unicorz";

CWizard::CWizard()
{
	if(instance != NULL){
		qWarning("Multiple CWizard constructed");
	}

	styler = Styler::getInstance();
	setting = new QSettings("config.ini", QSettings::IniFormat);
	writer = Writer::getInstance();
	stats = Stats::getInstance();

	connect(writer, SIGNAL(styleWarning(HabitType)), stats, SLOT(updateTodayLog(HabitType)));

	Wizard = instance = this;

	setAutoStart();
}

CWizard::~CWizard(){
	setAutoStart();

	delete setting;
	delete styler;
	delete writer;
	delete stats;
}

CWizard *CWizard::getInstance(){
	return instance;
}

QSettings *CWizard::getSetting() const{
	return setting;
}

QVariant CWizard::getSetting(const QString &key, const QVariant &defaultValue) const{
	return this->setting->value(key, defaultValue);
}

void CWizard::setSetting(const QString &key, const QVariant &value){
	this->setting->setValue(key, value);
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

void CWizard::setAutoStart() const{
#ifdef Q_WS_WIN
	static const QString key = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";

	QSettings reg(key, QSettings::NativeFormat);
	if(getSetting("autoStart").toBool()){
		reg.setValue("CWizard", qApp->applicationFilePath().replace("/", "\\"));
	}else{	
		reg.remove("CWizard");
	}
#endif
}
