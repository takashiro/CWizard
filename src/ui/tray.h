#ifndef TRAY_H
#define TRAY_H

/* 系统托盘类 */

#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>

class CWizard;

class Tray: public QSystemTrayIcon
{
	Q_OBJECT										//加上此标记后可以响应信号和槽

private:
	QMenu *contextMenu;								//右键菜单
	QAction *powerOnAction;							//[开启/关闭改写]菜单项
	bool isFirstBoot;

public:
	Tray(QWidget *parent = 0);						//构造函数
	~Tray();
	static Tray *getInstance(QWidget *parent = 0);	//返回该类的唯一对象

	void show();									//显示托盘
	void setPowerOnText(bool on = true);			//设置【开启/关闭改写】菜单项的文字

public slots:
	void alertError(QString msg);
};

#endif // TRAY_H
