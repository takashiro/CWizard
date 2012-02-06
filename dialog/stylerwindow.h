#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

/* CStyler小工具的窗口类 */

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
	QFile *file;											//当前打开的文件


private slots:
	void on_actionOpen_triggered();		//打开
	void on_actionCompress_triggered(); //压缩
	void on_actionFormat_triggered();	//规范化
};

#endif // STYLERWINDOW_H
