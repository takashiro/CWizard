#ifndef TRAY_H
#define TRAY_H

/* ϵͳ������ */

#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>

class CWizard;

class Tray: public QSystemTrayIcon
{
	Q_OBJECT										//���ϴ˱�Ǻ������Ӧ�źźͲ�

private:
	QMenu *contextMenu;								//�Ҽ��˵�
	QAction *powerOnAction;							//[����/�رո�д]�˵���
	bool isFirstBoot;

public:
	Tray(QWidget *parent = 0);						//���캯��
	~Tray();
	static Tray *getInstance(QWidget *parent = 0);	//���ظ����Ψһ����

	void show();									//��ʾ����
	void setPowerOnText(bool on = true);			//���á�����/�رո�д���˵��������

public slots:
	void alertError(QString msg);
};

#endif // TRAY_H
