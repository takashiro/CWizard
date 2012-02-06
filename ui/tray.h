#ifndef TRAY_H
#define TRAY_H

/* 系统托盘类 */

#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>

#include "core/cwizard.h"

class Tray: public QSystemTrayIcon
{
	Q_OBJECT										//加上此标记后可以响应信号和槽

private:
	QAction *powerOnAction;							//【开启/关闭改写】菜单项

public:
	Tray(QWidget *parent = 0);						//构造函数
	static Tray *getInstance(QWidget *parent = 0);	//返回该类的唯一对象

	void setPowerOnText(bool on = true);			//设置【开启/关闭改写】菜单项的文字
};

#endif // TRAY_H
