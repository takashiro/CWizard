#include "statdialog.h"
#include "ui_statdialog.h"

#include "core/stats.h"
#include "ui/statgraphics.h"

StatDialog::StatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatDialog)
{
	ui->setupUi(this);

	QMap<QString, int> labels;
	WritingHabit habit = stats->getTodayLog();
	labels[tr("bioperator")] = habit.bioperator;
	labels[tr("comma")] = habit.comma;
	labels[tr("brace")] = habit.brace;
	graph.setLabels(labels);

	ui->graphicsView->resize(this->size());
	ui->graphicsView->setScene(&graph);	
	ui->graphicsView->show();
}

StatDialog::~StatDialog()
{
    delete ui;
}
