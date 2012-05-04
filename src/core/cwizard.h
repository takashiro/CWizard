#ifndef CWIZARD_H
#define CWIZARD_H

/* CWizard类，包含本软件的基本信息和基础功能 */

#include <QSettings>

class Styler;
class Writer;
class Stats;

class CWizard: public QObject{
	Q_OBJECT

private:
	static const QString appName;		//应用名称
	static const QString appVersion;	//应用版本
	static const QString orgName;		//开发组织名称

	QSettings *setting;					//设置
	Styler *styler;						//Styler类，代码规范化类
	Writer *writer;						//Writer类，代码改写类
	Stats *stats;						//统计类

	static CWizard *instance;

public:
	CWizard();							//构造函数
	~CWizard();							//析构函数
	static CWizard *getInstance();		//返回本类的唯一对象

	QSettings *getSetting() const;
	QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant()) const;
	void setSetting(const QString &key, const QVariant &value = QVariant());

	QString getAppName() const;			//返回应用名称
	QString getAppVersion() const;		//返回应用版本
	QString getOrgName() const;			//返回开发组织名称

	void setAutoStart() const;			//程序自启动
};

extern CWizard *Wizard;

#endif // CWIZARD_H
