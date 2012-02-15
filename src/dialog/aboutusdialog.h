#ifndef ABOUTUSDIALOG_H
#define ABOUTUSDIALOG_H

#include <QDialog>

namespace Ui {
    class AboutusDialog;
}

class AboutusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutusDialog(QWidget *parent = 0);
    ~AboutusDialog();

private:
    Ui::AboutusDialog *ui;
};

#endif // ABOUTUSDIALOG_H
