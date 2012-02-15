#include "aboutusdialog.h"
#include "ui_aboutusdialog.h"

AboutusDialog::AboutusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutusDialog)
{
    ui->setupUi(this);
}

AboutusDialog::~AboutusDialog()
{
    delete ui;
}
