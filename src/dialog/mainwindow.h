#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* 主窗口类（浮动工具栏），本软件的界面主类，数据成员包含所有的其他窗口和系统托盘的指针 */

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>

class SettingDialog;
class StylerWindow;
class Tray;

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);		//构造函数
	~MainWindow();									//析构函数
	static MainWindow *getInstance();

	void toggleShow();								//交替显示/隐藏浮动工具栏

	void mousePressEvent(QMouseEvent *event);		//这三个鼠标事件实现完成拖拽工具栏功能
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

	QMenu *toolMenu;
	QPoint dragPosition;

	SettingDialog *settingDialog;					//设置对话框
	StylerWindow *stylerWindow;						//CStyler小工具窗口
	QDialog *aboutusDialog;							//关于我们
	Tray *tray;										//系统托盘

	static MainWindow *instance;

private slots:
	void on_cstyler_clicked();
	void on_powerOn_clicked();
	void on_hide_clicked();
	void on_exit_clicked();
    void on_setting_clicked();

	void showStyler() const;
	void showAboutus();
	void trayActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
