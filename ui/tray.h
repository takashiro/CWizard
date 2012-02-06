#ifndef TRAY_H
#define TRAY_H

/* ϵͳ������ */

#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>

#include "core/cwizard.h"

class Tray: public QSystemTrayIcon
{
	Q_OBJECT										//���ϴ˱�Ǻ������Ӧ�źźͲ�

private:
	QAction *powerOnAction;							//������/�رո�д���˵���

public:
	Tray(QWidget *parent = 0);						//���캯��
	static Tray *getInstance(QWidget *parent = 0);	//���ظ����Ψһ����

	void setPowerOnText(bool on = true);			//���á�����/�رո�д���˵��������
};

#endif // TRAY_H
