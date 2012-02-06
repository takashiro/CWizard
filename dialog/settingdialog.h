#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

/* ���ý���ĶԻ����� */

#include <QDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QAbstractButton>

namespace Ui{
	class SettingDialog;
}

class SettingDialog: public QDialog{
	Q_OBJECT

private:
	QSettings *setting;										//CWizard������

public:
	SettingDialog(QWidget *parent = 0);						//���캯��
	~SettingDialog();										//��������
	static SettingDialog *getInstance(QWidget *parent = 0);	//��ȡ�����Ψһ����

	void loadSetting(QSettings *setting);					//��������
	QSettings *getSettingFile();							//��ȡ����

	void closeEvent(QCloseEvent *event);	//���عر��¼�������رհ�ť��������

	Ui::SettingDialog *ui;

private slots:
	void on_buttonBox_clicked(QAbstractButton* button);		//��׼��ť���Ӧ�Ĳ�

	void saveSetting();						//�������ã��ò��Ѿ��뱾���accepted()�ź�����
};

#endif // SETTINGDIALOG_H
