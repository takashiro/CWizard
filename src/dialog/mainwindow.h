#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* �������ࣨ��������������������Ľ������࣬���ݳ�Ա�������е��������ں�ϵͳ���̵�ָ�� */

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
	explicit MainWindow(QWidget *parent = 0);		//���캯��
	~MainWindow();									//��������
	static MainWindow *getInstance();

	void toggleShow();								//������ʾ/���ظ���������

	void mousePressEvent(QMouseEvent *event);		//����������¼�ʵ�������ק����������
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

	QMenu *toolMenu;
	QPoint dragPosition;

	SettingDialog *settingDialog;					//���öԻ���
	StylerWindow *stylerWindow;						//CStylerС���ߴ���
	QDialog *aboutusDialog;							//��������
	Tray *tray;										//ϵͳ����

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
