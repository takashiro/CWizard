#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSettings>

#include "core/styler.h"

namespace Ui{
	class SettingDialog;
}

class SettingDialog: public QDialog{
	Q_OBJECT

public:
	SettingDialog(QWidget *parent = 0);
	~SettingDialog();

	QSettings *setting;

	Ui::SettingDialog *ui;

private slots:
	void on_buttonBox_accepted();
};

#endif // SETTINGDIALOG_H
