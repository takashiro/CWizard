#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

/* 设置界面的对话框类 */

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
	QSettings *setting;										//CWizard的设置

public:
	SettingDialog(QWidget *parent = 0);						//构造函数
	~SettingDialog();										//析构函数
	static SettingDialog *getInstance(QWidget *parent = 0);	//获取该类的唯一对象

	void loadSetting(QSettings *setting);					//加载设置
	QSettings *getSettingFile();							//获取设置

	Ui::SettingDialog *ui;

public slots:
	void saveSetting();						//保存设置，该槽已经与本类的accepted()信号相连

private slots:
	void on_buttonBox_clicked(QAbstractButton* button);		//标准按钮组对应的槽
};

#endif // SETTINGDIALOG_H
