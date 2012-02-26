#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

/* CStyler小工具的窗口类 */

#include <QMainWindow>
#include <QEvent>
#include <QFileDialog>
#include <QSettings>
#include <QWidgetAction>

class Styler;

namespace Ui {
    class StylerWindow;
}

class StylerWindow : public QMainWindow
{
    Q_OBJECT
private:
	Ui::StylerWindow *ui;
	QFile *file;						//当前打开的文件
    static const QString extFilters;	//可用扩展名
	QSettings *setting;					//配置信息

	Styler *styler;

public:
	explicit StylerWindow(QWidget *parent = 0);
	~StylerWindow();
	static StylerWindow *getInstance(QWidget *parent = 0);

public slots:
	void openFile(QString filePath = QString());		//打开文件
	void saveHistory();									//保存历史记录

private slots:
	void on_actionSettings_triggered();
	void on_actionOpen_triggered();						//打开文件
	void on_actionSave_triggered();						//保存文件
	void on_actionCompress_triggered();					//压缩
	void on_actionFormat_triggered();					//规范化
	void on_actionLockToolBar_triggered(bool checked);
	void on_actionFullScreen_triggered();
	void on_actionExit_triggered();
    void on_actionToHTML_triggered();
};

class Action: public QWidgetAction{
	Q_OBJECT

public:
	explicit Action(QWidget *parent = 0);
	Action(QString text, QWidget *parent = 0);

public slots:
	void triggerWithText();

signals:
	void triggered(QString text);
};

#endif // STYLERWINDOW_H
