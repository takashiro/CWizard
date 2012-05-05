#include "statdialog.h"
#include "ui_statdialog.h"

#include "core/stats.h"

StatDialog::StatDialog(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::StatDialog)
{
	ui->setupUi(this);

	setLabels(QDate::currentDate());
	ui->graphicsView->setScene(&graph);
	ui->graphicsView->show();

	ui->dateEdit->setDate(QDate::currentDate());

	connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setLabels(QDate)));
	connect(ui->week, SIGNAL(clicked()), this, SLOT(showLastWeek()));
	connect(ui->month, SIGNAL(clicked()), this, SLOT(showLastMonth()));
}

void StatDialog::setLabels(QDate date){
	QMap<QString, int> labels;

	WritingHabit habit = stats->getLog(date.toString(Qt::ISODate));
	labels[tr("bioperator")] = habit.bioperator;
	labels[tr("comma")] = habit.comma;
	labels[tr("brace")] = habit.brace;

	graph.setLabels(labels);
}

void StatDialog::showLastNDays(int days){
	QMap<QString, int> labels;

	labels[tr("bioperator")] = labels[tr("comma")] = labels[tr("brace")] = 0;

	QDate cur = QDate::currentDate();
	WritingHabit habit;
	for(int i = 0; i < days; i++){
		habit = stats->getLog(cur.toString(Qt::ISODate));

		labels[tr("bioperator")] += habit.bioperator;
		labels[tr("comma")] += habit.comma;
		labels[tr("brace")] += habit.brace;

		cur = cur.addDays(-1);
	}

	graph.setLabels(labels);
}

void StatDialog::showLastWeek(){
	showLastNDays(7);
}

void StatDialog::showLastMonth(){
	showLastNDays(30);
}

StatDialog::~StatDialog()
{
    delete ui;
}
