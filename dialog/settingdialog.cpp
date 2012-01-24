#include "dialog/settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::SettingDialog)
{
	ui->setupUi(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_buttonBox_accepted(){
	setting->setValue("syntax_bioperator",
					  QVariant::fromValue(ui->syntax_bioperator->isChecked()));
	setting->setValue("syntax_alwaysQuoteBlocks",
					  QVariant::fromValue(ui->syntax_alwaysQuoteBlocks->isChecked()));
	setting->setValue("syntax_leftBraceNewLine",
					  QVariant::fromValue(ui->syntax_leftBraceNewLine->isChecked()));
	setting->setValue("syntax_noComents",
					  QVariant::fromValue(ui->syntax_noComments->isChecked()));
	setting->setValue("syntax_skipUpperCase",
					  QVariant::fromValue(ui->syntax_skipUpperCase->isChecked()));
	setting->setValue("syntax_commaBlank",
					  QVariant::fromValue(ui->syntax_spaceAfterComma->isChecked()));
	setting->setValue("syntax_functionsSplitted",
					  QVariant::fromValue(ui->syntax_splitFunctions->isChecked()));
}
