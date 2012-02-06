#ifndef CWIZARD_H
#define CWIZARD_H

/* CWizard类，包含本软件的基本信息和各类基础功能 */

#include <QSettings>

#include "core/styler.h"
#include "core/writer.h"

class CWizard{
public:
	CWizard();							//构造函数
	~CWizard();							//析构函数
	static CWizard *getInstance();		//返回本类的唯一对象

	QSettings *setting;					//设置
	Styler *styler;						//Styler类，代码规范化类
	Writer *writer;						//Writer类，代码改写类

	QString getAppName();				//返回应用名称
	QString getAppVersion();			//返回应用版本

private:
	static const QString appName;		//应用名称
	static const QString appVersion;	//应用版本
};

#endif // CWIZARD_H
