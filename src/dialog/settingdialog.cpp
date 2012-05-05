
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

	setting->beginGroup("syntax");
	ui->syntax_bioperator->setChecked(setting->value("bioperator", true).toBool());
	ui->syntax_alwaysQuoteBlocks->setChecked(setting->value("alwaysQuoteBlocks", true).toBool());
	ui->syntax_leftBraceNewLine->setChecked(setting->value("leftBraceNewLine", false).toBool());
	ui->syntax_noComments->setChecked(setting->value("noComents", false).toBool());
	ui->syntax_spaceAfterComma->setChecked(setting->value("commaBlank", true).toBool());
	ui->syntax_splitFunctions->setChecked(setting->value("functionsSplitted", true).toBool());

	ui->syntax_nomenclature->setId(ui->nomenclature_camelCase, 0);
	ui->syntax_nomenclature->setId(ui->nomenclature_underline, 1);
	ui->syntax_nomenclature->setId(ui->nomenclature_pascal, 2);
	ui->syntax_nomenclature->setId(ui->nomenclature_hungary, 3);
	int nomenclature_id = setting->value("nomenclature", 0).toInt();
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
	setting->endGroup();

	ui->nomenclature_skipUpperCase->setChecked(setting->value("nomenclature/skipUpperCase", true).toBool());

	ui->displayToolBarOnStart->setChecked(setting->value("displayToolBarOnStart", false).toBool());
    ui->showStylerOnStart->setChecked(setting->value("showStylerOnStart", false).toBool());

	QString displayLanguage = setting->value("displayLanguage", "en_US").toString();
	if(displayLanguage == "en_US"){
		ui->displayLanguage->setCurrentIndex(0);
	}else if(displayLanguage == "zh_CN"){
		ui->displayLanguage->setCurrentIndex(1);
	}else if(displayLanguage == "ja_JP"){
		ui->displayLanguage->setCurrentIndex(2);
	}

	ui->autoStart->setChecked(setting->value("autoStart").toBool());
	ui->autoUpdate->setChecked(setting->value("autoUpdate").toBool());

	ui->silentMode->setChecked(setting->value("rewrite/silentMode").toBool());
}

void SettingDialog::saveSetting(){
	setting->beginGroup("syntax");
	setting->setValue("bioperator", ui->syntax_bioperator->isChecked());
	setting->setValue("alwaysQuoteBlocks", ui->syntax_alwaysQuoteBlocks->isChecked());
	setting->setValue("leftBraceNewLine", ui->syntax_leftBraceNewLine->isChecked());
	setting->setValue("noComents", ui->syntax_noComments->isChecked());
	setting->setValue("commaBlank", ui->syntax_spaceAfterComma->isChecked());
	setting->setValue("functionsSplitted", ui->syntax_splitFunctions->isChecked());
	setting->setValue("nomenclature", ui->syntax_nomenclature->checkedId());
	setting->endGroup();

	setting->setValue("nomenclature/skipUpperCase", ui->nomenclature_skipUpperCase->isChecked());

	setting->setValue("displayToolBarOnStart", ui->displayToolBarOnStart->isChecked());
    setting->setValue("showStylerOnStart", ui->showStylerOnStart->isChecked());

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

	setting->setValue("autoStart", ui->autoStart->isChecked());
	setting->setValue("autoUpdate", ui->autoUpdate->isChecked());

	setting->setValue("rewrite/silentMode", ui->silentMode->isChecked());
}

void SettingDialog::on_buttonBox_clicked(QAbstractButton* button){
	if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply){
		saveSetting();
	}
}
