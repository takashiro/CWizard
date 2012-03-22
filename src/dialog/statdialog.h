#ifndef STATDIALOG_H
#define STATDIALOG_H

#include <QDialog>

#include "ui/statgraphics.h"

namespace Ui {
    class StatDialog;
}

class StatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatDialog(QWidget *parent = 0);
    ~StatDialog();

private:
    Ui::StatDialog *ui;
	StatGraphics graph;
};

#endif // STATDIALOG_H
