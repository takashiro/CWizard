#ifndef CWIZARD_H
#define CWIZARD_H

/* CWizard�࣬����������Ļ�����Ϣ�͸���������� */

#include <QSettings>

#include "core/styler.h"
#include "core/writer.h"

class CWizard{
public:
	CWizard();							//���캯��
	~CWizard();							//��������
	static CWizard *getInstance();		//���ر����Ψһ����

	QSettings *setting;					//����
	Styler *styler;						//Styler�࣬����淶����
	Writer *writer;						//Writer�࣬�����д��

	QString getAppName();				//����Ӧ������
	QString getAppVersion();			//����Ӧ�ð汾

private:
	static const QString appName;		//Ӧ������
	static const QString appVersion;	//Ӧ�ð汾
};

#endif // CWIZARD_H
