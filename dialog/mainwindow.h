#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* �������ࣨ��������������������Ľ������࣬���ݳ�Ա�������е��������ں�ϵͳ���̵�ָ�� */

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
	explicit MainWindow(QWidget *parent = 0);		//���캯��
	~MainWindow();									//��������
	static MainWindow *getInstance();				//��ȡ�����Ψһ����

	void toggleShow();								//������ʾ/���ظ���������

	void mousePressEvent(QMouseEvent *event);		//����������¼�ʵ�������ק����������
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

	SettingDialog *settingDialog;					//���öԻ���
	StylerWindow *stylerWindow;						//CStylerС���ߴ���
	Tray *tray;										//ϵͳ����

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
