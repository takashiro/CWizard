#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>

#include <dialog/settingdialog.h>
#include <dialog/stylerwindow.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *);

	SettingDialog *settingDialog;
	StylerWindow *stylerWindow;

private:
    Ui::MainWindow *ui;

	QMenu *toolMenu;
	QPoint dragPosition;

private slots:
	void on_tool_clicked();
	void on_exit_clicked();
    void on_setting_clicked();

	void showStyler();
};

#endif // MAINWINDOW_H
