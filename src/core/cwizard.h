#ifndef CWIZARD_H
#define CWIZARD_H

/* CWizard�࣬����������Ļ�����Ϣ�ͻ������� */

#include <QSettings>

class Styler;
class Writer;
class Stats;

class CWizard: public QObject{
	Q_OBJECT

private:
	static const QString appName;		//Ӧ������
	static const QString appVersion;	//Ӧ�ð汾
	static const QString orgName;		//������֯����

	QSettings *setting;					//����
	Styler *styler;						//Styler�࣬����淶����
	Writer *writer;						//Writer�࣬�����д��
	Stats *stats;						//ͳ����

	static CWizard *instance;

public:
	CWizard();							//���캯��
	~CWizard();							//��������
	static CWizard *getInstance();		//���ر����Ψһ����

	QSettings *getSetting() const;
	QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant()) const;
	void setSetting(const QString &key, const QVariant &value = QVariant());

	QString getAppName() const;			//����Ӧ������
	QString getAppVersion() const;		//����Ӧ�ð汾
	QString getOrgName() const;			//���ؿ�����֯����

	void setAutoStart() const;			//����������
};

extern CWizard *Wizard;

#endif // CWIZARD_H
