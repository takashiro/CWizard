#include "statdialog.h"
#include "ui_statdialog.h"

#include "core/stats.h"
#include "ui/statgraphics.h"

StatDialog::StatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatDialog)
{
	ui->setupUi(this);

	setLabels(QDate::currentDate());
	ui->graphicsView->resize(this->size());
	ui->graphicsView->setScene(&graph);	
	ui->graphicsView->show();

	ui->dateEdit->setDate(QDate::currentDate());

	connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setLabels(QDate)));
}

void StatDialog::setLabels(QDate date){
	QMap<QString, int> labels;

	WritingHabit habit = stats->getLog(date.toString(Qt::ISODate));
	labels[tr("bioperator")] = habit.bioperator;
	labels[tr("comma")] = habit.comma;
	labels[tr("brace")] = habit.brace;

	graph.setLabels(labels);
}

StatDialog::~StatDialog()
{
    delete ui;
}
