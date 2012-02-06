#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

/* CStylerС���ߵĴ����� */

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
	Styler *styler;

public:
	explicit StylerWindow(QWidget *parent = 0);
	~StylerWindow();
	static StylerWindow *getInstance(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	Ui::StylerWindow *ui;
	QFile *file;											//��ǰ�򿪵��ļ�


private slots:
	void on_actionOpen_triggered();		//��
	void on_actionCompress_triggered(); //ѹ��
	void on_actionFormat_triggered();	//�淶��
};

#endif // STYLERWINDOW_H
