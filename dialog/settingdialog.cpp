#include <QPushButton>

#include "dialog/settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::SettingDialog)
{
	ui->setupUi(this);

	connect(this, SIGNAL(accepted()), this, SLOT(saveSetting()));

	ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("OK"));
	ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
	ui->buttonBox->button(QDialogButtonBox::Apply)->setText(tr("Apply"));
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

SettingDialog *SettingDialog::getInstance(QWidget *parent){
	static SettingDialog *instance = new SettingDialog(parent);
	return instance;
}

void SettingDialog::loadSetting(QSettings *setting){
	this->setting = setting;

	ui->syntax_bioperator->setChecked(setting->value("syntax_bioperator", true).toBool());
	ui->syntax_alwaysQuoteBlocks->setChecked(setting->value("syntax_alwaysQuoteBlocks", true).toBool());
	ui->syntax_leftBraceNewLine->setChecked(setting->value("syntax_leftBraceNewLine", false).toBool());
	ui->syntax_noComments->setChecked(setting->value("syntax_noComents", false).toBool());
	ui->syntax_spaceAfterComma->setChecked(setting->value("syntax_commaBlank", true).toBool());
	ui->syntax_splitFunctions->setChecked(setting->value("syntax_functionsSplitted", true).toBool());

	ui->syntax_nomenclature->setId(ui->nomenclature_camelCase, 0);
	ui->syntax_nomenclature->setId(ui->nomenclature_underline, 1);
	ui->syntax_nomenclature->setId(ui->nomenclature_pascal, 2);
	ui->syntax_nomenclature->setId(ui->nomenclature_hungary, 3);
	int nomenclature_id = setting->value("syntax_nomenclature", 0).toInt();
	switch(nomenclature_id){
	case 0:
		ui->nomenclature_camelCase->setChecked(true);
		break;
	case 1:
		ui->nomenclature_underline->setChecked(true);
		break;
	case 2:
		ui->nomenclature_pascal->setChecked(true);
		break;
	case 3:
		ui->nomenclature_hungary->setChecked(true);
		break;
	default:;
	}
	ui->nomenclature_skipUpperCase->setChecked(setting->value("nomenclature_skipUpperCase", true).toBool());

	ui->displayToolBarOnStart->setChecked(setting->value("displayToolBarOnStart", false).toBool());

	QString displayLanguage = setting->value("displayLanguage", "en_US").toString();
	if(displayLanguage == "en_US"){
		ui->displayLanguage->setCurrentIndex(0);
	}else if(displayLanguage == "zh_CN"){
		ui->displayLanguage->setCurrentIndex(1);
	}else if(displayLanguage == "ja_JP"){
		ui->displayLanguage->setCurrentIndex(2);
	}
}

void SettingDialog::saveSetting(){
	setting->setValue("syntax_bioperator", ui->syntax_bioperator->isChecked());
	setting->setValue("syntax_alwaysQuoteBlocks", ui->syntax_alwaysQuoteBlocks->isChecked());
	setting->setValue("syntax_leftBraceNewLine", ui->syntax_leftBraceNewLine->isChecked());
	setting->setValue("syntax_noComents", ui->syntax_noComments->isChecked());
	setting->setValue("syntax_commaBlank", ui->syntax_spaceAfterComma->isChecked());
	setting->setValue("syntax_functionsSplitted", ui->syntax_splitFunctions->isChecked());

	setting->setValue("syntax_nomenclature", ui->syntax_nomenclature->checkedId());
	setting->setValue("nomenclature_skipUpperCase", ui->nomenclature_skipUpperCase->isChecked());

	setting->setValue("displayToolBarOnStart", ui->displayToolBarOnStart->isChecked());

	switch(ui->displayLanguage->currentIndex()){
	case 0:
		setting->setValue("displayLanguage", QString("en_US"));
		break;
	case 1:
		setting->setValue("displayLanguage", QString("zh_CN"));
		break;
	case 2:
		setting->setValue("displayLanguage", QString("ja_JP"));
		break;
	}
}

void SettingDialog::closeEvent(QCloseEvent *event){
	this->hide();
	event->ignore();
}

void SettingDialog::on_buttonBox_clicked(QAbstractButton* button){
	/*if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply){
		this->saveSetting();
	}*/
}
