#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

#include <QMainWindow>
#include <QEvent>

#include <QFileDialog>

#include "core/styler.h"

namespace Ui {
    class StylerWindow;
}

class StylerWindow : public QMainWindow
{
    Q_OBJECT

public:
	Styler *styler;

    explicit StylerWindow(QWidget *parent = 0);
    ~StylerWindow();

	void resizeEvent(QResizeEvent *);

private:
    Ui::StylerWindow *ui;
	QFile *file;

private slots:
	void on_actionOpen_triggered();
	void on_actionCompress_triggered();
	void on_actionFormat_triggered();
};

#endif // STYLERWINDOW_H
