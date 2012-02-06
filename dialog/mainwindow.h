#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* 主窗口类（浮动工具栏），本软件的界面主类，数据成员包含所有的其他窗口和系统托盘的指针 */

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <windows.h>

#include "dialog/settingdialog.h"
#include "dialog/stylerwindow.h"
#include "ui/tray.h"

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);		//构造函数
	~MainWindow();									//析构函数
	static MainWindow *getInstance();				//获取该类的唯一对象

	void toggleShow();								//交替显示/隐藏浮动工具栏

	void mousePressEvent(QMouseEvent *event);		//这三个鼠标事件实现完成拖拽工具栏功能
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

	SettingDialog *settingDialog;					//设置对话框
	StylerWindow *stylerWindow;						//CStyler小工具窗口
	Tray *tray;										//系统托盘

private:
    Ui::MainWindow *ui;

	QMenu *toolMenu;
	QPoint dragPosition;

private slots:
	void on_powerOn_clicked();
	void on_hide_clicked();
	void on_tool_clicked();
	void on_exit_clicked();
    void on_setting_clicked();

	void showStyler();
	void trayActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
