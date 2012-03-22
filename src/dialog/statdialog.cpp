#include "statdialog.h"
#include "ui_statdialog.h"

#include "ui/statgraphics.h"

StatDialog::StatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatDialog)
{
	ui->setupUi(this);

	ui->graphicsView->resize(this->size());
	ui->graphicsView->setScene(&graph);
	ui->graphicsView->show();
}

StatDialog::~StatDialog()
{
    delete ui;
}
